#include "filter2.h"

int inquery_main(char* input_string) {
	char* div_input[4];
	int div_input_2[4] = {0,0,0,0};

	int check_type[6] = {0,0,0,0,0,0}; // 0 : ���ڿ���, 1 : �ð�, 2 : �ð�, 3 : ��¥, 4: �ο�, 5: �ǹ���

	int i = 0;
	int tmp;

	real_set_error_flag(NOERROR);

	char* ptr = strtok(input_string, " ");  // " " ���� ���ڸ� �������� ���ڿ��� �ڸ�

	while (ptr != NULL)
	{
		if (i > 3) {                           // ����) ���鹮�ڰ� 4�� �̻�
			set_error_flag(OVERSPACE);
			return 1;
		}
		div_input[i] = ptr;                    //�ڸ� ���ڿ��� ���������� �迭�� ����.
		ptr = strtok(NULL, " ");				//���� ���ڿ� Ž��.

		if (ptr != NULL)
			i++;
	}

	if (i < 1) {                               // ����) ���� ���ڰ� 1�� ����
		set_error_flag(UNDERSPACE);
		return 1;
	}
	
	for (int j = 0; j < i + 1; j++) {
		tmp = inquery_check_type(div_input[j]);
		check_type[tmp]++;
		div_input_2[j] = tmp;
	}

	if (!keyword_filter(check_type)) { //������ �߻��ϸ�
		return 1;
	}

	int res = 0;
	for (int j = 0; j < i + 1; j++) {
		res += check_keywork_main(div_input[j]);
	}

	if (res != i + 1) {
		return 1;
	}

	if (check_type[1] && check_type[3]) { //��¥�� �ð�
		if (read_inquery_date_during_time()) //1�̸� �� �Ȱ���.
			return 0;
		else
			return 1;
	}
	else if (check_type[2] && check_type[3]) { //��¥�� �ð�
		if (read_inquery_date_acuurate_time())
			return 0;
		else
			return 1;
	}

	//����üũ

	return 0;
}

int keyword_filter(int list[]) {
	
	//1���� �ʼ� ����üũ
	if (!((list[1] && list[3]) || (list[2] && list[3]))) {
		set_error_flag(ERROR_NEED_INPUT);
		return 0;
	}
	//2���� ������ ���� ����.
	//Ű���尡 ���� �Ǿ� �����ʰų� �ΰ� �̻��� Ű���尡 ���Ե� ����.
	if (list[0] > 0) {
		set_error_flag(ERROR_DENY_INPUT);
		return 0;
	}
	//3���� �ߺ� ����.
	if ((list[1] > 1) || (list[2] > 1) || (list[3] > 1) || (list[4] > 1) || (list[5] > 1)) {
		set_error_flag(ERROR_OVERLAP_INPUT);
		return 0;
	}
	//4���� �ð� �ð� ���� �Է�
	if (list[1] && list[2]) {
		set_error_flag(ERROR_NO_TWO_TIME);
		return 0;
	}

	return 1;
}

int inquery_check_type(char* str) {

	int check = 0;

	if (strstr(str, "�ð�") != NULL) {
		check = 1;
	}
	if (strstr(str, "~") != NULL) {
		if (!check) { // üũ�� 0 �̶��
			check = 2;
		}
		else //�ߺ� üũ�� �� ��� �̴� �������� �ʴ� ���ڷ� �Ǹ�.
			return 0;
	}
	if (strstr(str, "/") != NULL) {
		if (!check) {
			check = 3;
		}
		else
			return 0;
	}

	if (!strcmp(str, "���а�") || !strcmp(str, "������а�") || !strcmp(str, "���㿬����") || !strcmp(str, "�����䵵����") || !strcmp(str, "����������а�")) {

		if (!check) {
			check = 5;
			return check;
		}
		else
			return 0;
	}
	if (strstr(str, "��") != NULL) {
		if (!check) {
			check = 4;
		}
		else
			return 0;
	}

	return check;

}


int check_keywork_main(char* str) { //1�� ���� ���� 0 �� ���� ����


	if (strstr(str, "�ð�") != NULL) {
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
	else if (strstr(str, "��") != NULL) {
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
	else if (!strcmp(str, "���а�") || !strcmp(str, "������а�") || !strcmp(str, "���㿬����") || !strcmp(str, "�����䵵����") || !strcmp(str, "����������а�")) {
		set_check_parameter_building(str);
		return 1;
	}

	return 0;
}
