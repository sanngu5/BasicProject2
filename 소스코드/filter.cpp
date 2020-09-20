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

	char* ptr = strtok(input_string, " ");  // " " ���� ���ڸ� �������� ���ڿ��� �ڸ�

	while (ptr != NULL)
	{
		if (i > 4) {                           // ����) ���鹮�ڰ� 5�� �̻�
			set_error_flag(OVERSPACE);
			return 1;
		}
		div_input[i] = ptr;                    //�ڸ� ���ڿ��� ���������� �迭�� ����.
		ptr = strtok(NULL, " ");				//���� ���ڿ� Ž��.

		if (ptr != NULL)
			i++;
	}

	if (i < 4) {                               // ����) ���� ���ڰ� 3�� ����
		set_error_flag(UNDERSPACE);
		return 1;
	}

	for (int j = 0; j < 5; j++) { //��� ���ڵ��� Ű���� ���ͼ����� ���
		check_reservation_input_type(div_input[j]);
	}

	//��� ������ �ǹ� ��Ģ�� ���Ҵµ� ������ �ȵǾ� �ִ°��� �Է��� ���� ���ڶ�� ��
	//���� ��Ģ������ ����Ѵ�.
	if (get_check_parameter().BUILDING == NULL) {
		set_error_flag(ERROR_GRAMMAR_BUILDING);
		real_set_error_flag(FALSE);
		
		if (get_check_parameter().ROOM_NUMBER == NULL) {
			set_error_flag(ERROR_GRAMMAR_ROOM_NUMBER);
			real_set_error_flag(FALSE);

		}
		else if (!strcmp(get_check_parameter().ROOM_NUMBER, "ERROR")) { //�ǹ̿������.
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
	else { //�ǹ����� �¾�����.
		if (get_check_parameter().ROOM_NUMBER == NULL) { //ȣ�� ���� ����
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
		else if (!check_hosil(get_check_parameter().BUILDING, get_check_parameter().ROOM_NUMBER, 0)) { // ȣ�� �ǹ̿���
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
		else { //ȣ�� ����

			if (get_check_parameter().PEOPLE_NUMBER == NULL) {
				set_error_flag(ERROR_GRAMMAR_PEOPLE_NUMBER);
				real_set_error_flag(FALSE);

			}
			else if (!strcmp(get_check_parameter().PEOPLE_NUMBER, "ERROR")) {
				real_set_error_flag(FALSE);
			}
		}
	}
	
	//��¥ üũ
	if (get_check_parameter().DATE == NULL ) {
		set_error_flag(ERROR_GRAMMAR_DATE);
		real_set_error_flag(FALSE);
	}
	else if (!strcmp(get_check_parameter().DATE, "ERROR")) {
		real_set_error_flag(FALSE);
	}
	//�ð� üũ
	if (get_check_parameter().ACCURATE_TIME == NULL ) {
		set_error_flag(ERROR_GRAMMAR_ACCURATE_TIME);
		real_set_error_flag(FALSE);
	}
	else if (!strcmp(get_check_parameter().ACCURATE_TIME, "ERROR")) {
		real_set_error_flag(FALSE);
	}


	if (get_error_flag() == NOERROR) {
		//������ ������ ���ٸ�
		//�ش� �ǹ��� ȣ���� �ִ��� üũ
		if (!check_hosil(get_check_parameter().BUILDING, get_check_parameter().ROOM_NUMBER, 0)) { // �ش� ȣ���� ���ٸ�
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

//�� ���ڸ� Ű���� üũ�ϰ� �� ���� Ÿ�Կ� �´� ����üũ�� ������.
int check_reservation_input_type(char* str) {

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
	else if (strstr(str, "��") != NULL) {
		if (check_GRAMMAR_PEOPLE_NUMBER(str)) {  //���� ���� ����� �� ��ȯ
			if (check_MEANING_PEOPLE_NUMBER(str)) //�ǹ� ��Ģ���� ���̵Ǹ�
				set_check_parameter_people_number(str); //��Ʈ���� ����.
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


//�´����� üũ �ϴ� �Լ��̹Ƿ� �������� �����̸� �� 1 �ƴϸ� ���� 0 ��ȯ

int check_GRAMMAR_ROOM_NUMBER(char* str) { //2ȣ��, ���ڸ� �ڿ���
	char* hosil = strstr(str, "ȣ��");
	if (strlen(str) != 5 || !isdigit(str[0]) || strcmp(hosil, "ȣ��") != 0 || str[0] == '0')                   //5����Ʈ¥�� ���ڿ����� �˻�
		return 0;

	return 1;
}
int check_GRAMMAR_DATE(char* str) { // 10/12

	for (int i = 0; i<strlen(str); i++) {

		if (str[i]&	0x80) //�ѱ���
			return 0;

		else //�ѱ۾ƴ�
			continue;
	}

	if (strlen(str) != 5 || !isdigit(str[0]) || !isdigit(str[1]) || !isdigit(str[3]) || !isdigit(str[4]) || (str[2] != '/')) {
		return 0;
	}

	return 1;
}

int check_GRAMMAR_ACCURATE_TIME(char* str) {
	int checker_acutime = 0;

	if (strlen(str) != 5)                   //5����Ʈ¥�� ���ڿ����� �˻�
		return 0;							//�ƴϸ� 0����

	if (str[0] == '0') checker_acutime = 1;        //ù°�ڸ� �ڿ������� �˻�
	else if (str[0] == '1') checker_acutime = 1;   //�ƴϸ� 0����
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
		if (str[1] == '0') checker_acutime = 2;       //��°�ڸ� �ڿ������� �˻�
		else if (str[1] == '1') checker_acutime = 2;  //�ƴϸ� 0����
		else if (str[1] == '2') checker_acutime = 2;
		else if (str[1] == '3') checker_acutime = 2;
		else if (str[1] == '4') checker_acutime = 2;
		else if (str[1] == '5') checker_acutime = 2;
		else if (str[1] == '6') checker_acutime = 2;
		else if (str[1] == '7') checker_acutime = 2;
		else if (str[1] == '8') checker_acutime = 2;
		else if (str[1] == '9') checker_acutime = 2;
		else return 0;//�ƴϸ� 0����
	}
	if (checker_acutime == 2) {					//��°�ڸ� '~'���� �˻�
		if (str[2] == '~') checker_acutime = 3;		//�ƴϸ� 0����
		else return 0;
	}
	if (checker_acutime == 3) {
		if (str[3] == '0') checker_acutime = 4;		   //��°¥�� �ڿ������� �˻�
		else if (str[3] == '1') checker_acutime = 4;   //�ƴϸ� 0����
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
		if (str[4] == '0') return 1;		   //�ټ�°¥�� �ڿ������� �˻�
		else if (str[4] == '1') return 1;      //������ 1���� �ƴϸ� 0����
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
	if (str[0] & 0x80) //�ѱ���
		return 0;

	char* sigan = strstr(str, "�ð�");
	if (strlen(str) == 5 && isdigit(str[0]) && strcmp(sigan, "�ð�") == 0) {
		return 1;
	}
	else return 0;
}
int check_GRAMMAR_PEOPLE_NUMBER(char* str) {
	int checker_num = 0;					//ù�ڸ� �˻� ����� �����Ѱ� �����ϴ� ����
	
	if (strlen(str) != 4) 					//4¥�� ���ڿ����� �ƴ��� �˻�(�ѱ��� 2����Ʈ�ϱ�)
		return 0;							//�ƴϸ� 0����

	if (str[0] == '0') checker_num = 1;
	else if (str[0] == '1') checker_num = 1;	//ù°�ڸ��� �ڿ������� �˻�
	else if (str[0] == '2') checker_num = 1;	//�ƴϸ� 0����
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
		else if (str[1] == '1') checker_num = 2;	//��°�ڸ��� �ڿ������� �˻�
		else if (str[1] == '2') checker_num = 2;	//�ƴϸ� 0����
		else if (str[1] == '3') checker_num = 2;
		else if (str[1] == '4') checker_num = 2;
		else if (str[1] == '5') checker_num = 2;
		else if (str[1] == '6') checker_num = 2;
		else if (str[1] == '7') checker_num = 2;
		else if (str[1] == '8') checker_num = 2;
		else if (str[1] == '9') checker_num = 2;
		else return 0;
	}
	if (strstr(str, "��") != NULL)	return 1;	//���� ��ĭ �˻��� ���̶�� ���ڰ� �ִ��� �˻�
	else return 0;								//������ 1���� �ƴϸ� 0����
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
	if (!strcmp(str, "09~10")) return 1;			//������ �ð� ���� �˻�
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
	if (!strcmp(str, "02��")) return 1;				//������ ���� 02�� ���� 10�� ���̹Ƿ� �� �ܿ��� �ǹ̿���
	else if (!strcmp(str, "03��")) return 1;			//������ 1���� �ƴϸ� 0����
	else if (!strcmp(str, "04��")) return 1;
	else if (!strcmp(str, "05��")) return 1;
	else if (!strcmp(str, "06��")) return 1;
	else if (!strcmp(str, "07��")) return 1;
	else if (!strcmp(str, "08��")) return 1;
	else if (!strcmp(str, "09��")) return 1;
	else if (!strcmp(str, "10��")) return 1;
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

	if (!strcmp(str,"00")) return 1;					//���� �ð� Ȯ���ؼ� �����̸� ����1
	else if (!strcmp(str, "01")) return 1;		//00���� 23���� 24�� �ۿ� �����ϱ� ���� ��
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
	else return 0;							//�� �ܿ��� ���� �����̹Ƿ� ����0 
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
		printf("������ �����ϴ�.\n");
		break;
	case 1:
		printf("������ �ֽ��ϴ�.\n");
		break;
	case 2:
		printf("�Է°����� ������ ������ �ʰ��Ͽ����ϴ�.\n");
		break;
	case 3:
		printf("�Է��� ������ ������ �����մϴ�.\n");
		break;
	case 5:
		printf("�ǹ����� ������Ģ�� �ùٸ��� �ʽ��ϴ�.\n");
		break;
	case 6:
		printf("ȣ���� ������Ģ�� �ùٸ��� �ʽ��ϴ�.\n");
		break;
	case 7:
		printf("��¥�� ������Ģ�� �ùٸ��� �ʽ��ϴ�.\n");
		break;
	case 8:
		printf("�ð��� ������Ģ�� �ùٸ��� �ʽ��ϴ�.\n");
		break;
	case 9:
		printf("�ð��� ������Ģ�� �ùٸ��� �ʽ��ϴ�.\n");
		break;
	case 10:
		printf("�ο��� ������Ģ�� �ùٸ��� �ʽ��ϴ�.\n");
		break;
	case 11:
		printf("���� �ð��� �ùٸ��� �ʽ��ϴ�.\n");
		break;
	case 12:
		printf("��¥�� �ùٸ��� �ʽ��ϴ�.\n"); //���糯¥ ������
		break;
	case 13:
		printf("ȣ���� �ṉ̀�Ģ�� �ùٸ��� �ʽ��ϴ�.\n");
		break;
	case 14:
		printf("��¥�� �ṉ̀�Ģ�� �ùٸ��� �ʽ��ϴ�.\n");
		break;
	case 15:
		printf("�ð��� �ṉ̀�Ģ�� �ùٸ��� �ʽ��ϴ�.\n");
		break;
	case 16:
		printf("�ð��� �ṉ̀�Ģ�� �ùٸ��� �ʽ��ϴ�.\n");
		break;
	case 17:
		printf("�ο��� �ṉ̀�Ģ�� �ùٸ��� �ʽ��ϴ�.\n");
		break;
	case 18:
		printf("���Ž������δ� ������ �� �����ϴ�.\n");
		break;
	case 19:
		printf("�ش� �ð����� �̹� ������ �Ǿ��ֽ��ϴ�.\n");
		break;
	case 20:
		printf("�ʼ� ���ڰ� �����մϴ�.\n");
		break;
	case 21:
		printf("������ �ʴ� �����Դϴ�.\n");
		break;
	case 22:
		printf("���ڸ� �ߺ� �Է��Ͽ����ϴ�.\n");
		break;
	case 23:
		printf("�ð��� �ð��� ���ÿ� �Է��� �� �����ϴ�.\n");
		break;
	case 24:
		printf("���� ���뿡 ������ �ֽ��ϴ�.\n");
		break;
	case 25:
		printf("�й��� ������Ģ�� �ùٸ��� �ʽ��ϴ�.\n");
		break;
	default:
		break;
	}
}