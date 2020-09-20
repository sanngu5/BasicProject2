#include <stdio.h>
#include "filter.h"
#include "data.h"
#include "file.h"
#include <string.h>
#include "filter2.h"
#include "filter3.h"

void clearBuffer(void) {
	//�Է¹��ۿ� ���ڰ� ���������,
	//���ڸ� ��� �Ҹ��Ͽ� ���۸� �������
	//�ܼ��� ��븸�ϰ� �������� ������ ������� �Ǵ� ���� �̿�
	while (getchar() != '\n');
}

int main() {
	char menu_input[100] = "no"; // �޴�Ű �Է�
	char c; // ���� �����
	char input_string[1000];
	char input_string2[1000];
	char date[1000];
	char time[1000];

	/*FILE* fd = fopen("reservation_date_time_list.txt", "r");
	if (fd == NULL)
		printf("����");
	printf("%d",check_file_date_time_list(fd));
	fclose(fd);*/
	
	printf("Kcube ���� �ý��ۿ� ���Ű� ȯ���մϴ�.\n");

	//������ ��¥�� �ð� �Է¹ޱ�a
	printf("���� ��¥�� �Է����ּ���. : ");
	while (true) {
		for (int t = 0; t < 100; t++) {
			scanf("%c", &date[t]);
			if (date[t] == '\n') {
				date[t] = '\0';
				break;
			}
			if (t == 99) {
				date[t] = '\0';
				clearBuffer();
			}
		}
		if (check_CURRENT_DATE(date)) //��¥ ��Ģ�� ���� �� ���
			break;
		else
			printf("���� ��¥�� �Է����ּ���. : ");
	}

	printf("���� �ð��� �Է����ּ���. : ");
	while (true) {
		for (int t = 0; t < 100; t++) {
			scanf("%c", &time[t]);
			if (time[t] == '\n') {
				time[t] = '\0';
				break;
			}
			if (t == 99) {
				time[t] = '\0';
				clearBuffer();
			}
		}
		//gets_s(time, 100);
		//current_info.CURRENT_TIME = time;
		if (check_CURRENT_TIME(time)) //�ð� ��Ģ�� ���� �� ���
			break;
		else
			printf("���� �ð��� �Է����ּ���. : ");
	}


	while (true) {

		strcpy(menu_input, "no");

		//�޴� ǥ��
		printf("����ð� : %s, ���糯¥ : %s", time, date);
		printf("\n1) ��ȸ\n2) ����\n3) ���� ���� ��ȸ\n4) �������\n5) ����\n: ");

		for (int t = 0; t < 100; t++) {
			scanf("%c", &menu_input[t]);
			if (menu_input[t] == '\n') {
				menu_input[t] = '\0';
				break;
			}
			if (t == 99) {
				time[t] = '\0';
				clearBuffer();
			}
		}
		//gets_s(menu_input, 100);

		if (!strcmp(menu_input, "1")) { //case1, ��ȸ
			while (1) {
				reset_reserve_parameter();
		
				printf("��ȸ ������ �Է����ּ���. �ʼ� : ��¥ �ð� �ð�, �ɼ� : �ǹ���, �ο� \n");
				for (int t = 0; t < 100; t++) {
					scanf("%c", &input_string[t]);
					if (input_string[t] == '\n') {
						input_string[t] = '\0';
						break;
					}
					if (t == 99) {
						time[t] = '\0';
						clearBuffer();
					}
				}
				//gets_s(input_string, 100);
				FILE* fd = fopen("reservation_date_time_list.txt", "r");
				if (fd == NULL) {
					printf("reservation_date_time_list.txt ������ ���ų� �ջ�Ǿ����ϴ�.\n");
					break;
				}
				if (!check_file_date_time_list(fd)) { //���� �����̸�
					fclose(fd);
					break;
				}
				FILE* fd2 = fopen("reservation_list.txt", "r");
				if (fd2 == NULL) {
					printf("reservation_list.txt ������ ���ų� �ջ�Ǿ����ϴ�.\n");
					break;
				}
				if (!check_file_list(fd2)) { //���� �����̸�
					fclose(fd);
					break;
				}
				if (!strcmp(input_string, "q") || !strcmp(input_string, "Q")) {
					break;
				}
				else if (inquery_main(input_string)) {
					//����
					continue;
				}
				else { //0�̸� �ߵȰ���.
					break;
				}
			}

		}
		else if (!strcmp(menu_input, "2")) { //case2, ����
			while (true) {
				int check = 0;
				reset_reserve_parameter();
				printf("���� ������ �Է����ּ���. �Է� �ʿ� ����) �ǹ��̸� ȣ�� ��¥ �ð� �ο�\n");
				for (int t = 0; t < 100; t++) {
					scanf("%c", &input_string[t]);
					if (input_string[t] == '\n') {
						input_string[t] = '\0';
						break;
					}
					if (t == 99) {
						time[t] = '\0';
						clearBuffer();
					}
				}
				FILE* fd = fopen("reservation_date_time_list.txt", "r");
				if (fd == NULL) {
					printf("reservation_date_time_list.txt ������ ���ų� �ջ�Ǿ����ϴ�.\n");
					break;
				}
				if (!check_file_date_time_list(fd)) { //���� �����̸�
					fclose(fd);
					break;
				}
				FILE* fd2 = fopen("reservation_list.txt", "r");
				if (fd2 == NULL) {
					printf("reservation_list.txt ������ ���ų� �ջ�Ǿ����ϴ�.\n");
					break;
				}
				if (!check_file_list(fd2)) { //���� �����̸�
					fclose(fd2);
					break;
				}
				//gets_s(input_string, 100);
				if (!strcmp(input_string, "q") || !strcmp(input_string, "Q")) {
					break;
				}
				else if (reservation_main(input_string)) //������ ���� ��� Ʈ��
					continue;               //�ݺ�
				else {
					if (check_date_and_time(date, time)) {
						while (1) {
							int flag1 = read_reservation_time_check();
							if (flag1 == 1) {
								printf("�й��� �Է����ּ���.\n");
								for (int t = 0; t < 100; t++) {
									scanf("%c", &input_string2[t]);
									if (input_string2[t] == '\n') {
										input_string2[t] = '\0';
										break;
									}
									if (t == 99) {
										time[t] = '\0';
										clearBuffer();
									}
								}
								//gets_s(input_string2, 100);
								if (check_student_id(input_string2)) {
									set_check_parameter_student_id(input_string2);
									
									if (write_reservation() && write_reservation_time()) {
										printf("������ �Ϸ�Ǿ����ϴ�.\n");
										check = 1;
										break;
									}
									else {
										//printf("�� ������ ���̸� �ȵǴµ�\n");
										continue;
									}
								}
								
							}
							else if (flag1 == -1) {
								check = 1;
								break;
							}
							else {
								set_error_flag(ERROR_RESERVATION_ALREADY);
								break;
							}
						}
					}
					else {
						set_error_flag(ERROR_RESERVATION_NO_PAST);
						break;
					}

				}
				if (check) {
					break;
				}

			}
		}
		else if (!strcmp(menu_input, "3")) { //case3, �� ���� ��ȸ
			while (true)
			{
				printf("�й��� �Է����ּ���\n");
				for (int t = 0; t < 100; t++) {
					scanf("%c", &input_string2[t]);
					if (input_string2[t] == '\n') {
						input_string2[t] = '\0';
						break;
					}
					if (t == 99) {
						time[t] = '\0';
						clearBuffer();
					}
				}
				FILE* fd = fopen("reservation_date_time_list.txt", "r");
				if (fd == NULL) {
					printf("reservation_date_time_list.txt ������ ���ų� �ջ�Ǿ����ϴ�.\n");
					break;
				}
				if (!check_file_date_time_list(fd)) { //���� �����̸�
					fclose(fd);
					break;
				}
				FILE* fd2 = fopen("reservation_list.txt", "r");
				if (fd2 == NULL) {
					printf("reservation_list.txt ������ ���ų� �ջ�Ǿ����ϴ�.\n");
					break;
				}
				if (!check_file_list(fd2)) { //���� �����̸�
					fclose(fd2);
					break;
				}
				//gets_s(input_string2, 100);
				if (check_student_id(input_string2)) {
					int aa = read_my_reservaton(input_string2);
					if (aa==1) {
						break;
					}
					else if (aa == -1) {
						break;
					}
					else {
						printf("���೻���� �����ϴ�.\n");
						break;
					}
				}
				else if (!strcmp(input_string2, "Q") || !strcmp(input_string2, "q")) {
					break;
				}
				else {
					printf("�й��� ���������� �߻��߽��ϴ�.");
					continue;
				}
			}
		}
		else if (!strcmp(menu_input, "4")) { //case5, �������
			while (true) {
				reset_reserve_parameter();
				printf("��� ������ �Է����ּ���\n");
				for (int t = 0; t < 100; t++) {
					scanf("%c", &input_string2[t]);
					if (input_string2[t] == '\n') {
						input_string2[t] = '\0';
						break;
					}
					if (t == 99) {
						time[t] = '\0';
						clearBuffer();
					}
				}
				FILE* fd = fopen("reservation_date_time_list.txt", "r");
				if (fd == NULL) {
					printf("reservation_date_time_list.txt ������ ���ų� �ջ�Ǿ����ϴ�.\n");
					break;
				}
				if (!check_file_date_time_list(fd)) { //���� �����̸�
					fclose(fd);
					break;
				}
				FILE* fd2 = fopen("reservation_list.txt", "r");
				if (fd2 == NULL) {
					printf("reservation_list.txt ������ ���ų� �ջ�Ǿ����ϴ�.\n");
					break;
				}
				if (!check_file_list(fd2)) { //���� �����̸�
					fclose(fd2);
					break;
				}
				if(!strcmp(input_string2, "Q") || !strcmp(input_string2, "q")) 
					break;
				if (cancel_main(input_string2)) { //���� ����
					if (check_date_and_time(date, time)) { //�ð� �̷���
						cancel_list();
						cancel_time();
						printf("���� ��Ұ� �Ϸ�Ǿ����ϴ�.\n");
						break;
					}
					else {
							printf("������ ������ ��� �� �� �����ϴ�.\n");
					}
					
				}
				else { //���� ����
				}
			}
		
		}
		else if (!strcmp(menu_input, "5")) { //case5, ��������
			break;
		}
		else {
			printf("�޴� ������ �ٽ����ּ���.\n");
		}

	}
}