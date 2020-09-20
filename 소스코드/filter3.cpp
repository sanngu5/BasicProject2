#include "filter3.h"

int cancel_main(char* input) {
	//���� 0�� ����
	//���� 1�� ����
	char* div_input[5];
	int i = 0;

	real_set_error_flag(NOERROR);

	//set_error_flag(NOERROR);

	char* ptr = strtok(input, " ");  // " " ���� ���ڸ� �������� ���ڿ��� �ڸ�

	while (ptr != NULL)
	{
		if (i > 4) {                           // ����) ���鹮�ڰ� 5�� �̻�
			set_error_flag(OVERSPACE);
			return 0;
		}
		div_input[i] = ptr;                    //�ڸ� ���ڿ��� ���������� �迭�� ����.
		ptr = strtok(NULL, " ");				//���� ���ڿ� Ž��.

		if (ptr != NULL)
			i++;
	}

	if (i < 4) {                               // ����) ���� ���ڰ� 3�� ����
		set_error_flag(UNDERSPACE);
		return 0;
	}

	for (int j = 0; j < 5; j++) { //��� ���ڵ��� Ű���� ���ͼ����� ���
		check_cancel_type(div_input[j]);
	}

	if (check_grammar()) { //����
		return 0;
	}

	int flag1 = 0; 
	flag1 = check_cancel_my_reservaton();
	int flag2 = 0; 
	flag2 = check_cancel_my_time();
	
	if (flag1 + flag2 == 1) { // ���೻���� �Ѱ��� ����.
		printf("���� ������ �߸� ����Ǿ� �ֽ��ϴ�.\n");
		return 0;
	}
	if (flag1 + flag2 == 0) { //�Ѵ� ���� ������ ����
		printf("���� ������ �����ϴ�.\n");
		return 0;
	}

	return 1;
}

int check_grammar() {

	if (get_check_parameter().BUILDING == NULL) { //�ǹ� ����
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
	else { // �ǹ� ����.
		if (get_check_parameter().ROOM_NUMBER == NULL) {
			set_error_flag(ERROR_GRAMMAR_ROOM_NUMBER);
			real_set_error_flag(FALSE);
		}
		else {
			if (!check_hosil(get_check_parameter().BUILDING, get_check_parameter().ROOM_NUMBER, 0)) { //ȣ�� �ǹ� ����
				set_error_flag(ERROR_MEANING_ROOM_NUMBER);
				real_set_error_flag(FALSE);
			}
		}
	}

	//��¥ üũ
	if (get_check_parameter().DATE == NULL) {
		set_error_flag(ERROR_GRAMMAR_DATE);
		real_set_error_flag(FALSE);
	}
	else if (!strcmp(get_check_parameter().DATE, "ERROR")) {
		real_set_error_flag(FALSE);
	}

	//�ð� üũ
	if (get_check_parameter().ACCURATE_TIME == NULL) {
		set_error_flag(ERROR_GRAMMAR_ACCURATE_TIME);
		real_set_error_flag(FALSE);
	}
	else if (!strcmp(get_check_parameter().ACCURATE_TIME, "ERROR")) {
		real_set_error_flag(FALSE);
	}

	//�й�üũ
	if (get_check_parameter().STUDENT_ID == NULL) {
		set_error_flag(ERROR_GRAMMAR_STUDENT_ID);
		real_set_error_flag(FALSE);
	}

	return get_error_flag();
}

int check_cancel_type(char* str) {

	char ch[] = "ERROR";

	if (!strcmp(str, "���а�") || !strcmp(str, "������а�") || !strcmp(str, "���㿬����") || !strcmp(str, "�����䵵����") || !strcmp(str, "����������а�")) {
		set_check_parameter_building(str);
		return 1;
	}
	else if (strstr(str, "ȣ��") != NULL) { //Ű���� ���͸� ���������
		if (check_GRAMMAR_ROOM_NUMBER(str)) {  //���� ���� ����� �� ��ȯ
			if (true) //�ǹ� ��Ģ���� ���̵Ǹ�
				set_check_parameter_room_number(str); //��Ʈ���� ����.
			else {
				set_check_parameter_room_number(ch);
				set_error_flag(ERROR_MEANING_ROOM_NUMBER);
				real_set_error_flag(FALSE);
			}
		}

	}
	else if (strstr(str, "~") != NULL) {
		if (check_GRAMMAR_ACCURATE_TIME(str)) {  // �ð�
			if (check_MEANING_ACCURATE_TIME(str)) //�ǹ� ��Ģ���� ���̵Ǹ�
				set_check_parameter_accurate_time(str); //��Ʈ���� ����.
			else {
				set_check_parameter_accurate_time(ch);
				set_error_flag(ERROR_MEANING_ACCURATE_TIME);
				real_set_error_flag(FALSE);
			}
		}
	}
	else if (strstr(str, "/") != NULL) {
		if (check_GRAMMAR_DATE(str)) {  //��¥ ��Ģ
			if (check_MEANING_DATE(str)) //�ǹ� ��Ģ���� ���̵Ǹ�
				set_check_parameter_date(str); //��Ʈ���� ����.
			else {
				set_check_parameter_date(ch);
				set_error_flag(ERROR_MEANING_DATE);
				real_set_error_flag(FALSE);
			}
		}
	}
	else {
		if (check_student_id(str)) {  //���� ���� ����� �� ��ȯ
				set_check_parameter_student_id(str); //��Ʈ���� ����.
		}
		else {

			real_set_error_flag(FALSE);
		}
	}
	
	return 1;
}