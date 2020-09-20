#include "filter.h"
#include <string.h>
#include <ctype.h>

int people_number_error_flag = 0;
int hosil_error_flag = 0;

int reservation_main(char* input_string) {
	char* div_input[5];
	int i = 0;

	real_set_error_flag(NOERROR);

	//set_error_flag(NOERROR);

	char* ptr = strtok(input_string, " ");  // " " 공백 문자를 기준으로 문자열을 자름

	while (ptr != NULL)
	{
		if (i > 4) {                           // 예외) 공백문자가 5개 이상
			set_error_flag(OVERSPACE);
			return 1;
		}
		div_input[i] = ptr;                    //자른 문자열은 순차적으로 배열에 저장.
		ptr = strtok(NULL, " ");				//다음 문자열 탐색.

		if (ptr != NULL)
			i++;
	}

	if (i < 4) {                               // 예외) 공백 문자가 3개 이하
		set_error_flag(UNDERSPACE);
		return 1;
	}

	for (int j = 0; j < 5; j++) { //모든 인자들이 키워드 필터속으로 쏘옥
		check_reservation_input_type(div_input[j]);
	}

	//모든 문법과 의미 규칙을 돌았는데 저장이 안되어 있는것은 입력이 없는 인자라는 뜻
	//문법 규칙에러를 출력한다.
	if (get_check_parameter().BUILDING == NULL) {
		set_error_flag(ERROR_GRAMMAR_BUILDING);
		real_set_error_flag(FALSE);
		
		if (get_check_parameter().ROOM_NUMBER == NULL) {
			set_error_flag(ERROR_GRAMMAR_ROOM_NUMBER);
			real_set_error_flag(FALSE);

		}
		else if (!strcmp(get_check_parameter().ROOM_NUMBER, "ERROR")) { //의미오류라면.
		}
		else {
			set_error_flag(ERROR_MEANING_ROOM_NUMBER);
			real_set_error_flag(FALSE);
		}

		if (get_check_parameter().PEOPLE_NUMBER == NULL) {
			set_error_flag(ERROR_GRAMMAR_PEOPLE_NUMBER);
			real_set_error_flag(FALSE);
		}
		else if (!strcmp(get_check_parameter().PEOPLE_NUMBER, "ERROR")) {
		}
		else {
			set_error_flag(ERROR_MEANING_PEOPLE_NUMBER);
			real_set_error_flag(FALSE);
		}
	}
	else { //건물명이 맞았을때.
		if (get_check_parameter().ROOM_NUMBER == NULL) { //호실 문법 오류
			set_error_flag(ERROR_GRAMMAR_ROOM_NUMBER);
			real_set_error_flag(FALSE);

			if (get_check_parameter().PEOPLE_NUMBER == NULL) {
				set_error_flag(ERROR_GRAMMAR_PEOPLE_NUMBER);
				real_set_error_flag(FALSE);
				
			}
			else if (!strcmp(get_check_parameter().PEOPLE_NUMBER, "ERROR")) {
			}
			else {
				set_error_flag(ERROR_MEANING_PEOPLE_NUMBER);
				real_set_error_flag(FALSE);
			}

		}
		else if (!check_hosil(get_check_parameter().BUILDING, get_check_parameter().ROOM_NUMBER, 0)) { // 호실 의미오류
			set_error_flag(ERROR_MEANING_ROOM_NUMBER);
			real_set_error_flag(FALSE);

			if (get_check_parameter().PEOPLE_NUMBER == NULL) {
				set_error_flag(ERROR_GRAMMAR_PEOPLE_NUMBER);
				real_set_error_flag(FALSE);

			}
			else if (!strcmp(get_check_parameter().PEOPLE_NUMBER, "ERROR")) {
				real_set_error_flag(FALSE);
			}
			else {
				set_error_flag(ERROR_MEANING_PEOPLE_NUMBER);
				real_set_error_flag(FALSE);
			}
		}
		else { //호실 정상

			if (get_check_parameter().PEOPLE_NUMBER == NULL) {
				set_error_flag(ERROR_GRAMMAR_PEOPLE_NUMBER);
				real_set_error_flag(FALSE);

			}
			else if (!strcmp(get_check_parameter().PEOPLE_NUMBER, "ERROR")) {
				real_set_error_flag(FALSE);
			}
		}
	}
	
	//날짜 체크
	if (get_check_parameter().DATE == NULL ) {
		set_error_flag(ERROR_GRAMMAR_DATE);
		real_set_error_flag(FALSE);
	}
	else if (!strcmp(get_check_parameter().DATE, "ERROR")) {
		real_set_error_flag(FALSE);
	}
	//시각 체크
	if (get_check_parameter().ACCURATE_TIME == NULL ) {
		set_error_flag(ERROR_GRAMMAR_ACCURATE_TIME);
		real_set_error_flag(FALSE);
	}
	else if (!strcmp(get_check_parameter().ACCURATE_TIME, "ERROR")) {
		real_set_error_flag(FALSE);
	}


	if (get_error_flag() == NOERROR) {
		//문법에 오류가 없다면
		//해당 건물에 호실이 있는지 체크
		if (!check_hosil(get_check_parameter().BUILDING, get_check_parameter().ROOM_NUMBER, 0)) { // 해당 호실이 없다면
			set_error_flag(ERROR_MEANING_ROOM_NUMBER);
			set_error_flag(ERROR_MEANING_PEOPLE_NUMBER);
			real_set_error_flag(FALSE);
		}
		else {
			if (check_max_people(get_check_parameter().BUILDING, get_check_parameter().ROOM_NUMBER, get_check_parameter().PEOPLE_NUMBER)) {

			}
			else {
				set_error_flag(ERROR_MEANING_PEOPLE_NUMBER);
				real_set_error_flag(FALSE);
			}
		}

	}
	return get_error_flag();

}

//각 인자를 키워드 체크하고 각 인자 타입에 맞는 문법체크를 진행함.
int check_reservation_input_type(char* str) {

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
	else if (strstr(str, "명") != NULL) {
		if (check_GRAMMAR_PEOPLE_NUMBER(str)) {  //문법 필터 통과시 참 반환
			if (check_MEANING_PEOPLE_NUMBER(str)) //의미 규칙까지 참이되면
				set_check_parameter_people_number(str); //스트링값 저장.
			else {
				set_check_parameter_people_number(ch);
				set_error_flag(ERROR_MEANING_PEOPLE_NUMBER);
				real_set_error_flag(FALSE);
			}
		}
	}
	else
		return 0;
}


//맞는지를 체크 하는 함수이므로 정상적인 문법이면 참 1 아니면 거짓 0 반환

int check_GRAMMAR_ROOM_NUMBER(char* str) { //2호실, 한자리 자연수
	char* hosil = strstr(str, "호실");
	if (strlen(str) != 5 || !isdigit(str[0]) || strcmp(hosil, "호실") != 0 || str[0] == '0')                   //5바이트짜리 문자열인지 검사
		return 0;

	return 1;
}
int check_GRAMMAR_DATE(char* str) { // 10/12

	for (int i = 0; i<strlen(str); i++) {

		if (str[i]&	0x80) //한글임
			return 0;

		else //한글아님
			continue;
	}

	if (strlen(str) != 5 || !isdigit(str[0]) || !isdigit(str[1]) || !isdigit(str[3]) || !isdigit(str[4]) || (str[2] != '/')) {
		return 0;
	}

	return 1;
}

int check_GRAMMAR_ACCURATE_TIME(char* str) {
	int checker_acutime = 0;

	if (strlen(str) != 5)                   //5바이트짜리 문자열인지 검사
		return 0;							//아니면 0리턴

	if (str[0] == '0') checker_acutime = 1;        //첫째자리 자연수인지 검사
	else if (str[0] == '1') checker_acutime = 1;   //아니면 0리턴
	else if (str[0] == '2') checker_acutime = 1;
	else if (str[0] == '3') checker_acutime = 1;
	else if (str[0] == '4') checker_acutime = 1;
	else if (str[0] == '5') checker_acutime = 1;
	else if (str[0] == '6') checker_acutime = 1;
	else if (str[0] == '7') checker_acutime = 1;
	else if (str[0] == '8') checker_acutime = 1;
	else if (str[0] == '9') checker_acutime = 1;
	else return 0;

	if (checker_acutime) {
		if (str[1] == '0') checker_acutime = 2;       //둘째자리 자연수인지 검사
		else if (str[1] == '1') checker_acutime = 2;  //아니면 0리턴
		else if (str[1] == '2') checker_acutime = 2;
		else if (str[1] == '3') checker_acutime = 2;
		else if (str[1] == '4') checker_acutime = 2;
		else if (str[1] == '5') checker_acutime = 2;
		else if (str[1] == '6') checker_acutime = 2;
		else if (str[1] == '7') checker_acutime = 2;
		else if (str[1] == '8') checker_acutime = 2;
		else if (str[1] == '9') checker_acutime = 2;
		else return 0;//아니면 0리턴
	}
	if (checker_acutime == 2) {					//셋째자리 '~'인지 검사
		if (str[2] == '~') checker_acutime = 3;		//아니면 0리턴
		else return 0;
	}
	if (checker_acutime == 3) {
		if (str[3] == '0') checker_acutime = 4;		   //넷째짜리 자연수인지 검사
		else if (str[3] == '1') checker_acutime = 4;   //아니면 0리턴
		else if (str[3] == '2') checker_acutime = 4;
		else if (str[3] == '3') checker_acutime = 4;
		else if (str[3] == '4') checker_acutime = 4;
		else if (str[3] == '5') checker_acutime = 4;
		else if (str[3] == '6') checker_acutime = 4;
		else if (str[3] == '7') checker_acutime = 4;
		else if (str[3] == '8') checker_acutime = 4;
		else if (str[3] == '9') checker_acutime = 4;
		else return 0;
	}
	if (checker_acutime == 4) {
		if (str[4] == '0') return 1;		   //다섯째짜리 자연수인지 검사
		else if (str[4] == '1') return 1;      //맞으면 1리턴 아니면 0리턴
		else if (str[4] == '2') return 1;
		else if (str[4] == '3') return 1;
		else if (str[4] == '4') return 1;
		else if (str[4] == '5') return 1;
		else if (str[4] == '6') return 1;
		else if (str[4] == '7') return 1;
		else if (str[4] == '8') return 1;
		else if (str[4] == '9') return 1;
		else return 0;
	}
}
int check_GRAMMAR_DURING_TIME(char* str) {
	if (str[0] & 0x80) //한글임
		return 0;

	char* sigan = strstr(str, "시간");
	if (strlen(str) == 5 && isdigit(str[0]) && strcmp(sigan, "시간") == 0) {
		return 1;
	}
	else return 0;
}
int check_GRAMMAR_PEOPLE_NUMBER(char* str) {
	int checker_num = 0;					//첫자리 검사 결과가 적법한가 저장하는 인자
	
	if (strlen(str) != 4) 					//4짜리 문자열인지 아닌지 검사(한글은 2바이트니까)
		return 0;							//아니면 0리턴

	if (str[0] == '0') checker_num = 1;
	else if (str[0] == '1') checker_num = 1;	//첫째자리가 자연수인지 검사
	else if (str[0] == '2') checker_num = 1;	//아니면 0리턴
	else if (str[0] == '3') checker_num = 1;
	else if (str[0] == '4') checker_num = 1;
	else if (str[0] == '5') checker_num = 1;
	else if (str[0] == '6') checker_num = 1;
	else if (str[0] == '7') checker_num = 1;
	else if (str[0] == '8') checker_num = 1;
	else if (str[0] == '9') checker_num = 1;
	else return 0;

	if (checker_num) {
		if (str[1] == '0') checker_num = 2;
		else if (str[1] == '1') checker_num = 2;	//둘째자리가 자연수인지 검사
		else if (str[1] == '2') checker_num = 2;	//아니면 0리턴
		else if (str[1] == '3') checker_num = 2;
		else if (str[1] == '4') checker_num = 2;
		else if (str[1] == '5') checker_num = 2;
		else if (str[1] == '6') checker_num = 2;
		else if (str[1] == '7') checker_num = 2;
		else if (str[1] == '8') checker_num = 2;
		else if (str[1] == '9') checker_num = 2;
		else return 0;
	}
	if (strstr(str, "명") != NULL)	return 1;	//앞의 두칸 검사후 명이라는 글자가 있는지 검색
	else return 0;								//맞으면 1리턴 아니면 0리턴
}

int check_MEANING_ROOM_NUMBER(char* str) {
	return 1;
}
int check_MEANING_DATE(char* str) { // 10/12

	char tmp[100];
	char* month;
	char* day;
	
	//strcmp(s1,s2)
	// s1 == s2, 0
	// s1 > s2, 1
	// s1 < s2, -1
	strcpy(tmp, str);
	month = strtok(tmp, "/");

	if (!((strcmp(month, "00") == 1) && (strcmp(month, "13") == -1))) {
		return 0;
	}
	else {
		day = strtok(NULL, "/");
		if ( !strcmp(month,"04") || !strcmp(month, "06") || !strcmp(month, "09") || !strcmp(month, "11")) {
			if (strcmp(day,"00")==1 && strcmp(day,"31") == -1)
				return 1;
		}
		else if (!strcmp(month, "01") || !strcmp(month, "03") || !strcmp(month, "05") || !strcmp(month, "07") || !strcmp(month, "08") || !strcmp(month, "10") || !strcmp(month, "12")) {
			if (strcmp(day, "00") == 1 && strcmp(day, "32") == -1)
				return 1;
		}
		else {
			if (strcmp(day, "00") == 1 && strcmp(day, "29") == -1)
				return 1;
		}

	}

	return 0;
}
int check_MEANING_ACCURATE_TIME(char* str) {
	if (!strcmp(str, "09~10")) return 1;			//가능한 시각 조합 검사
	else if (!strcmp(str, "09~11")) return 1;
	else if (!strcmp(str, "09~12")) return 1;
	else if (!strcmp(str, "10~11")) return 1;
	else if (!strcmp(str, "10~12")) return 1;
	else if (!strcmp(str, "10~13")) return 1;
	else if (!strcmp(str, "11~12")) return 1;
	else if (!strcmp(str, "11~13")) return 1;
	else if (!strcmp(str, "11~14")) return 1;
	else if (!strcmp(str, "12~13")) return 1;
	else if (!strcmp(str, "12~14")) return 1;
	else if (!strcmp(str, "12~15")) return 1;
	else if (!strcmp(str, "13~14")) return 1;
	else if (!strcmp(str, "13~15")) return 1;
	else if (!strcmp(str, "13~16")) return 1;
	else if (!strcmp(str, "14~15")) return 1;
	else if (!strcmp(str, "14~16")) return 1;
	else if (!strcmp(str, "14~17")) return 1;
	else if (!strcmp(str, "15~16")) return 1;
	else if (!strcmp(str, "15~17")) return 1;
	else if (!strcmp(str, "15~18")) return 1;
	else if (!strcmp(str, "16~17")) return 1;
	else if (!strcmp(str, "16~18")) return 1;
	else if (!strcmp(str, "16~19")) return 1;
	else if (!strcmp(str, "17~18")) return 1;
	else if (!strcmp(str, "17~19")) return 1;
	else if (!strcmp(str, "17~20")) return 1;
	else if (!strcmp(str, "18~19")) return 1;
	else if (!strcmp(str, "18~20")) return 1;
	else if (!strcmp(str, "18~21")) return 1;
	else if (!strcmp(str, "19~20")) return 1;
	else if (!strcmp(str, "19~21")) return 1;
	else if (!strcmp(str, "19~22")) return 1;
	else if (!strcmp(str, "20~21")) return 1;
	else if (!strcmp(str, "20~22")) return 1;
	else if (!strcmp(str, "21~22")) return 1;
	else return 0;
}
int check_MEANING_DURING_TIME(char* str) {
	if (str[0] >= '1' && str[0] <='3'){
		return 1;
	} return 0;
}
int check_MEANING_PEOPLE_NUMBER(char* str) {
	if (!strcmp(str, "02명")) return 1;				//가능한 경우는 02명 부터 10명 뿐이므로 그 외에는 의미오류
	else if (!strcmp(str, "03명")) return 1;			//맞으면 1리턴 아니면 0리턴
	else if (!strcmp(str, "04명")) return 1;
	else if (!strcmp(str, "05명")) return 1;
	else if (!strcmp(str, "06명")) return 1;
	else if (!strcmp(str, "07명")) return 1;
	else if (!strcmp(str, "08명")) return 1;
	else if (!strcmp(str, "09명")) return 1;
	else if (!strcmp(str, "10명")) return 1;
	else return 0;
}

int check_CURRENT_DATE(char* str) {

	if (check_GRAMMAR_DATE(str) && check_MEANING_DATE(str)) {
		return 1;
	}
	else
		return 0;
}

int check_CURRENT_TIME(char* str) {

	if (!strcmp(str,"00")) return 1;					//현재 시간 확인해서 성공이면 리턴1
	else if (!strcmp(str, "01")) return 1;		//00부터 23까지 24개 밖에 없으니까 전부 비교
	else if (!strcmp(str, "02")) return 1;
	else if (!strcmp(str, "03")) return 1;
	else if (!strcmp(str, "04")) return 1;
	else if (!strcmp(str, "05")) return 1;
	else if (!strcmp(str, "06")) return 1;
	else if (!strcmp(str, "07")) return 1;
	else if (!strcmp(str, "08")) return 1;
	else if (!strcmp(str, "09")) return 1;
	else if (!strcmp(str, "10")) return 1;
	else if (!strcmp(str, "11")) return 1;
	else if (!strcmp(str, "12")) return 1;
	else if (!strcmp(str, "13")) return 1;
	else if (!strcmp(str, "14")) return 1;
	else if (!strcmp(str, "15")) return 1;
	else if (!strcmp(str, "16")) return 1;
	else if (!strcmp(str, "17")) return 1;
	else if (!strcmp(str, "18")) return 1;
	else if (!strcmp(str, "08")) return 1;
	else if (!strcmp(str, "19")) return 1;
	else if (!strcmp(str, "20")) return 1;
	else if (!strcmp(str, "21")) return 1;
	else if (!strcmp(str, "22")) return 1;
	else if (!strcmp(str, "23")) return 1;
	else return 0;							//그 외에는 전부 실패이므로 리턴0 
}

int check_student_id(char* str) {

	if (strlen(str) != 9)
		return 0;
	int a = atoi(str);
	int i = 1;
	if (a > 10)
	{
		for (a; a >= 10;)
		{
			a = a / 10;
			i++;
		}
	}
	if (i != 9)
		return 0;
	else return 1;
}

int check_date_and_time(char* current_date, char* current_time) {
	char* date = get_check_parameter().DATE;
	char* accurate_time = get_check_parameter().ACCURATE_TIME;

	char temp[20];

	strcpy(temp, accurate_time);

	//strcmp(s1,s2)
	// s1 == s2, 0
	// s1 > s2, 1
	// s1 < s2, -1
	if (strcmp(date, current_date) == -1) {
		return 0;
	}
	else if (strcmp(date, current_date) == 1)
		return 1;
	else {
		 char* tmp = strtok(temp, "~");
		 if (strcmp(tmp, current_time) == -1)
			 return 0;
		 else 
			 return 1;
	}
}

void show_error(int error_flag) {
	switch (error_flag)
	{
	case 0:
		printf("에러가 없습니다.\n");
		break;
	case 1:
		printf("에러가 있습니다.\n");
		break;
	case 2:
		printf("입력가능한 인자의 개수를 초과하였습니다.\n");
		break;
	case 3:
		printf("입력한 인자의 개수가 부족합니다.\n");
		break;
	case 5:
		printf("건물명의 문법규칙이 올바르지 않습니다.\n");
		break;
	case 6:
		printf("호실의 문법규칙이 올바르지 않습니다.\n");
		break;
	case 7:
		printf("날짜의 문법규칙이 올바르지 않습니다.\n");
		break;
	case 8:
		printf("시각의 문법규칙이 올바르지 않습니다.\n");
		break;
	case 9:
		printf("시간의 문법규칙이 올바르지 않습니다.\n");
		break;
	case 10:
		printf("인원의 문법규칙이 올바르지 않습니다.\n");
		break;
	case 11:
		printf("현재 시각이 올바르지 않습니다.\n");
		break;
	case 12:
		printf("날짜가 올바르지 않습니다.\n"); //현재날짜 오류용
		break;
	case 13:
		printf("호실의 의미규칙이 올바르지 않습니다.\n");
		break;
	case 14:
		printf("날짜의 의미규칙이 올바르지 않습니다.\n");
		break;
	case 15:
		printf("시각의 의미규칙이 올바르지 않습니다.\n");
		break;
	case 16:
		printf("시간의 의미규칙이 올바르지 않습니다.\n");
		break;
	case 17:
		printf("인원의 의미규칙이 올바르지 않습니다.\n");
		break;
	case 18:
		printf("과거시점으로는 예약할 수 없습니다.\n");
		break;
	case 19:
		printf("해당 시간에는 이미 예약이 되어있습니다.\n");
		break;
	case 20:
		printf("필수 인자가 부족합니다.\n");
		break;
	case 21:
		printf("허용되지 않는 인자입니다.\n");
		break;
	case 22:
		printf("인자를 중복 입력하였습니다.\n");
		break;
	case 23:
		printf("시간과 시각은 동시에 입력할 수 없습니다.\n");
		break;
	case 24:
		printf("파일 내용에 문제가 있습니다.\n");
		break;
	case 25:
		printf("학번의 문법규칙이 올바르지 않습니다.\n");
		break;
	default:
		break;
	}
}