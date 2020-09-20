#include "filter3.h"

int cancel_main(char* input) {
	//리턴 0은 실패
	//리턴 1은 성공
	char* div_input[5];
	int i = 0;

	real_set_error_flag(NOERROR);

	//set_error_flag(NOERROR);

	char* ptr = strtok(input, " ");  // " " 공백 문자를 기준으로 문자열을 자름

	while (ptr != NULL)
	{
		if (i > 4) {                           // 예외) 공백문자가 5개 이상
			set_error_flag(OVERSPACE);
			return 0;
		}
		div_input[i] = ptr;                    //자른 문자열은 순차적으로 배열에 저장.
		ptr = strtok(NULL, " ");				//다음 문자열 탐색.

		if (ptr != NULL)
			i++;
	}

	if (i < 4) {                               // 예외) 공백 문자가 3개 이하
		set_error_flag(UNDERSPACE);
		return 0;
	}

	for (int j = 0; j < 5; j++) { //모든 인자들이 키워드 필터속으로 쏘옥
		check_cancel_type(div_input[j]);
	}

	if (check_grammar()) { //오류
		return 0;
	}

	int flag1 = 0; 
	flag1 = check_cancel_my_reservaton();
	int flag2 = 0; 
	flag2 = check_cancel_my_time();
	
	if (flag1 + flag2 == 1) { // 예약내역이 한개만 있음.
		printf("예약 내역이 잘못 저장되어 있습니다.\n");
		return 0;
	}
	if (flag1 + flag2 == 0) { //둘다 예약 내역이 없음
		printf("예약 내역이 없습니다.\n");
		return 0;
	}

	return 1;
}

int check_grammar() {

	if (get_check_parameter().BUILDING == NULL) { //건물 오류
		set_error_flag(ERROR_GRAMMAR_BUILDING);
		real_set_error_flag(FALSE);
		if (get_check_parameter().ROOM_NUMBER == NULL) {
			set_error_flag(ERROR_GRAMMAR_ROOM_NUMBER);
			real_set_error_flag(FALSE);
		}
		else {
			set_error_flag(ERROR_MEANING_ROOM_NUMBER);
			real_set_error_flag(FALSE);
		}
	}
	else { // 건물 정상.
		if (get_check_parameter().ROOM_NUMBER == NULL) {
			set_error_flag(ERROR_GRAMMAR_ROOM_NUMBER);
			real_set_error_flag(FALSE);
		}
		else {
			if (!check_hosil(get_check_parameter().BUILDING, get_check_parameter().ROOM_NUMBER, 0)) { //호실 의미 오류
				set_error_flag(ERROR_MEANING_ROOM_NUMBER);
				real_set_error_flag(FALSE);
			}
		}
	}

	//날짜 체크
	if (get_check_parameter().DATE == NULL) {
		set_error_flag(ERROR_GRAMMAR_DATE);
		real_set_error_flag(FALSE);
	}
	else if (!strcmp(get_check_parameter().DATE, "ERROR")) {
		real_set_error_flag(FALSE);
	}

	//시각 체크
	if (get_check_parameter().ACCURATE_TIME == NULL) {
		set_error_flag(ERROR_GRAMMAR_ACCURATE_TIME);
		real_set_error_flag(FALSE);
	}
	else if (!strcmp(get_check_parameter().ACCURATE_TIME, "ERROR")) {
		real_set_error_flag(FALSE);
	}

	//학번체크
	if (get_check_parameter().STUDENT_ID == NULL) {
		set_error_flag(ERROR_GRAMMAR_STUDENT_ID);
		real_set_error_flag(FALSE);
	}

	return get_error_flag();
}

int check_cancel_type(char* str) {

	char ch[] = "ERROR";

	if (!strcmp(str, "공학관") || !strcmp(str, "생명과학관") || !strcmp(str, "상허연구관") || !strcmp(str, "상허기념도서관") || !strcmp(str, "동물생명과학관")) {
		set_check_parameter_building(str);
		return 1;
	}
	else if (strstr(str, "호실") != NULL) { //키워드 필터를 통과했을때
		if (check_GRAMMAR_ROOM_NUMBER(str)) {  //문법 필터 통과시 참 반환
			if (true) //의미 규칙까지 참이되면
				set_check_parameter_room_number(str); //스트링값 저장.
			else {
				set_check_parameter_room_number(ch);
				set_error_flag(ERROR_MEANING_ROOM_NUMBER);
				real_set_error_flag(FALSE);
			}
		}

	}
	else if (strstr(str, "~") != NULL) {
		if (check_GRAMMAR_ACCURATE_TIME(str)) {  // 시각
			if (check_MEANING_ACCURATE_TIME(str)) //의미 규칙까지 참이되면
				set_check_parameter_accurate_time(str); //스트링값 저장.
			else {
				set_check_parameter_accurate_time(ch);
				set_error_flag(ERROR_MEANING_ACCURATE_TIME);
				real_set_error_flag(FALSE);
			}
		}
	}
	else if (strstr(str, "/") != NULL) {
		if (check_GRAMMAR_DATE(str)) {  //날짜 규칙
			if (check_MEANING_DATE(str)) //의미 규칙까지 참이되면
				set_check_parameter_date(str); //스트링값 저장.
			else {
				set_check_parameter_date(ch);
				set_error_flag(ERROR_MEANING_DATE);
				real_set_error_flag(FALSE);
			}
		}
	}
	else {
		if (check_student_id(str)) {  //문법 필터 통과시 참 반환
				set_check_parameter_student_id(str); //스트링값 저장.
		}
		else {

			real_set_error_flag(FALSE);
		}
	}
	
	return 1;
}