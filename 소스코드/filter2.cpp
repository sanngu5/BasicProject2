#include "filter2.h"

int inquery_main(char* input_string) {
	char* div_input[4];
	int div_input_2[4] = {0,0,0,0};

	int check_type[6] = {0,0,0,0,0,0}; // 0 : 인자오류, 1 : 시간, 2 : 시각, 3 : 날짜, 4: 인원, 5: 건물명

	int i = 0;
	int tmp;

	real_set_error_flag(NOERROR);

	char* ptr = strtok(input_string, " ");  // " " 공백 문자를 기준으로 문자열을 자름

	while (ptr != NULL)
	{
		if (i > 3) {                           // 예외) 공백문자가 4개 이상
			set_error_flag(OVERSPACE);
			return 1;
		}
		div_input[i] = ptr;                    //자른 문자열은 순차적으로 배열에 저장.
		ptr = strtok(NULL, " ");				//다음 문자열 탐색.

		if (ptr != NULL)
			i++;
	}

	if (i < 1) {                               // 예외) 공백 문자가 1개 이하
		set_error_flag(UNDERSPACE);
		return 1;
	}
	
	for (int j = 0; j < i + 1; j++) {
		tmp = inquery_check_type(div_input[j]);
		check_type[tmp]++;
		div_input_2[j] = tmp;
	}

	if (!keyword_filter(check_type)) { //에러가 발생하면
		return 1;
	}

	int res = 0;
	for (int j = 0; j < i + 1; j++) {
		res += check_keywork_main(div_input[j]);
	}

	if (res != i + 1) {
		return 1;
	}

	if (check_type[1] && check_type[3]) { //날짜와 시간
		if (read_inquery_date_during_time()) //1이면 잘 된거임.
			return 0;
		else
			return 1;
	}
	else if (check_type[2] && check_type[3]) { //날짜와 시각
		if (read_inquery_date_acuurate_time())
			return 0;
		else
			return 1;
	}

	//문법체크

	return 0;
}

int keyword_filter(int list[]) {
	
	//1순위 필수 인자체크
	if (!((list[1] && list[3]) || (list[2] && list[3]))) {
		set_error_flag(ERROR_NEED_INPUT);
		return 0;
	}
	//2순위 허용되지 않은 인자.
	//키워드가 포함 되어 있지않거나 두개 이상의 키워드가 포함된 인자.
	if (list[0] > 0) {
		set_error_flag(ERROR_DENY_INPUT);
		return 0;
	}
	//3순위 중복 인자.
	if ((list[1] > 1) || (list[2] > 1) || (list[3] > 1) || (list[4] > 1) || (list[5] > 1)) {
		set_error_flag(ERROR_OVERLAP_INPUT);
		return 0;
	}
	//4순위 시각 시간 동시 입력
	if (list[1] && list[2]) {
		set_error_flag(ERROR_NO_TWO_TIME);
		return 0;
	}

	return 1;
}

int inquery_check_type(char* str) {

	int check = 0;

	if (strstr(str, "시간") != NULL) {
		check = 1;
	}
	if (strstr(str, "~") != NULL) {
		if (!check) { // 체크가 0 이라면
			check = 2;
		}
		else //중복 체크가 될 경우 이는 존재하지 않는 인자로 판명.
			return 0;
	}
	if (strstr(str, "/") != NULL) {
		if (!check) {
			check = 3;
		}
		else
			return 0;
	}

	if (!strcmp(str, "공학관") || !strcmp(str, "생명과학관") || !strcmp(str, "상허연구관") || !strcmp(str, "상허기념도서관") || !strcmp(str, "동물생명과학관")) {

		if (!check) {
			check = 5;
			return check;
		}
		else
			return 0;
	}
	if (strstr(str, "명") != NULL) {
		if (!check) {
			check = 4;
		}
		else
			return 0;
	}

	return check;

}


int check_keywork_main(char* str) { //1은 정상 문법 0 은 오류 문법


	if (strstr(str, "시간") != NULL) {
		if (check_GRAMMAR_DURING_TIME(str)) {
			if (check_MEANING_DURING_TIME(str)) {
				set_check_parameter_during_time(str);
				return 1;
			}
			else {
				set_error_flag(ERROR_MEANING_DURING_TIME);
				return 0;
			}
		}
		else {
			set_error_flag(ERROR_GRAMMAR_DURING_TIME);
			return 0;
		}
		
	}
	else if (strstr(str, "~") != NULL) {
		if (check_GRAMMAR_ACCURATE_TIME(str)) {
			if (check_MEANING_ACCURATE_TIME(str)) {
				set_check_parameter_accurate_time(str);
				return 1;
			}
			else {
				set_error_flag(ERROR_MEANING_ACCURATE_TIME);
				return 0;
			}
		}
		else {
			set_error_flag(ERROR_GRAMMAR_ACCURATE_TIME);
			return 0;
		}
	}
	else if (strstr(str, "/") != NULL) {
		if (check_GRAMMAR_DATE(str)) {
			if (check_MEANING_DATE(str)) {
				set_check_parameter_date(str);
				return 1;
			}
			else {
				set_error_flag(ERROR_MEANING_DATE);
				return 0;
			}
		}
		else {
			set_error_flag(ERROR_GRAMMAR_DATE);
			return 0;
		}
	}
	else if (strstr(str, "명") != NULL) {
		if (check_GRAMMAR_PEOPLE_NUMBER(str)) {
			if (check_MEANING_PEOPLE_NUMBER(str)) {
				set_check_parameter_people_number(str);
				return 1;
			}
			else {
				set_error_flag(ERROR_MEANING_PEOPLE_NUMBER);
				return 0;
			}
		}
		else {
			set_error_flag(ERROR_GRAMMAR_PEOPLE_NUMBER);
			return 0;
		}
	}
	else if (!strcmp(str, "공학관") || !strcmp(str, "생명과학관") || !strcmp(str, "상허연구관") || !strcmp(str, "상허기념도서관") || !strcmp(str, "동물생명과학관")) {
		set_check_parameter_building(str);
		return 1;
	}

	return 0;
}
