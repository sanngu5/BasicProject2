#include <stdio.h>
#include "filter.h"
#include "data.h"
#include "file.h"
#include <string.h>
#include "filter2.h"
#include "filter3.h"

void clearBuffer(void) {
	//입력버퍼에 문자가 들어있으면,
	//문자를 모두 소모하여 버퍼를 비워버림
	//단순히 사용만하고 저장하지 않으면 비워지게 되는 원리 이용
	while (getchar() != '\n');
}

int main() {
	char menu_input[100] = "no"; // 메뉴키 입력
	char c; // 버퍼 지우기
	char input_string[1000];
	char input_string2[1000];
	char date[1000];
	char time[1000];

	/*FILE* fd = fopen("reservation_date_time_list.txt", "r");
	if (fd == NULL)
		printf("에러");
	printf("%d",check_file_date_time_list(fd));
	fclose(fd);*/
	
	printf("Kcube 예약 시스템에 오신걸 환영합니다.\n");

	//현재의 날짜와 시간 입력받기a
	printf("현재 날짜를 입력해주세요. : ");
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
		if (check_CURRENT_DATE(date)) //날짜 규칙에 만족 할 경우
			break;
		else
			printf("현재 날짜를 입력해주세요. : ");
	}

	printf("현재 시각을 입력해주세요. : ");
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
		if (check_CURRENT_TIME(time)) //시간 규칙에 만족 할 경우
			break;
		else
			printf("현재 시각을 입력해주세요. : ");
	}


	while (true) {

		strcpy(menu_input, "no");

		//메뉴 표시
		printf("현재시간 : %s, 현재날짜 : %s", time, date);
		printf("\n1) 조회\n2) 예약\n3) 나의 예약 조회\n4) 예약취소\n5) 종료\n: ");

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

		if (!strcmp(menu_input, "1")) { //case1, 조회
			while (1) {
				reset_reserve_parameter();
		
				printf("조회 정보를 입력해주세요. 필수 : 날짜 시간 시각, 옵션 : 건물명, 인원 \n");
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
					printf("reservation_date_time_list.txt 파일이 없거나 손상되었습니다.\n");
					break;
				}
				if (!check_file_date_time_list(fd)) { //파일 오류이면
					fclose(fd);
					break;
				}
				FILE* fd2 = fopen("reservation_list.txt", "r");
				if (fd2 == NULL) {
					printf("reservation_list.txt 파일이 없거나 손상되었습니다.\n");
					break;
				}
				if (!check_file_list(fd2)) { //파일 오류이면
					fclose(fd);
					break;
				}
				if (!strcmp(input_string, "q") || !strcmp(input_string, "Q")) {
					break;
				}
				else if (inquery_main(input_string)) {
					//에러
					continue;
				}
				else { //0이면 잘된거임.
					break;
				}
			}

		}
		else if (!strcmp(menu_input, "2")) { //case2, 예약
			while (true) {
				int check = 0;
				reset_reserve_parameter();
				printf("예약 정보를 입력해주세요. 입력 필요 조건) 건물이름 호실 날짜 시각 인원\n");
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
					printf("reservation_date_time_list.txt 파일이 없거나 손상되었습니다.\n");
					break;
				}
				if (!check_file_date_time_list(fd)) { //파일 오류이면
					fclose(fd);
					break;
				}
				FILE* fd2 = fopen("reservation_list.txt", "r");
				if (fd2 == NULL) {
					printf("reservation_list.txt 파일이 없거나 손상되었습니다.\n");
					break;
				}
				if (!check_file_list(fd2)) { //파일 오류이면
					fclose(fd2);
					break;
				}
				//gets_s(input_string, 100);
				if (!strcmp(input_string, "q") || !strcmp(input_string, "Q")) {
					break;
				}
				else if (reservation_main(input_string)) //에러가 있을 경우 트루
					continue;               //반복
				else {
					if (check_date_and_time(date, time)) {
						while (1) {
							int flag1 = read_reservation_time_check();
							if (flag1 == 1) {
								printf("학번을 입력해주세요.\n");
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
										printf("예약이 완료되었습니다.\n");
										check = 1;
										break;
									}
									else {
										//printf("이 오류는 보이면 안되는데\n");
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
		else if (!strcmp(menu_input, "3")) { //case3, 내 예약 조회
			while (true)
			{
				printf("학번을 입력해주세요\n");
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
					printf("reservation_date_time_list.txt 파일이 없거나 손상되었습니다.\n");
					break;
				}
				if (!check_file_date_time_list(fd)) { //파일 오류이면
					fclose(fd);
					break;
				}
				FILE* fd2 = fopen("reservation_list.txt", "r");
				if (fd2 == NULL) {
					printf("reservation_list.txt 파일이 없거나 손상되었습니다.\n");
					break;
				}
				if (!check_file_list(fd2)) { //파일 오류이면
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
						printf("예약내역이 없습니다.\n");
						break;
					}
				}
				else if (!strcmp(input_string2, "Q") || !strcmp(input_string2, "q")) {
					break;
				}
				else {
					printf("학번의 문법오류가 발생했습니다.");
					continue;
				}
			}
		}
		else if (!strcmp(menu_input, "4")) { //case5, 예약취소
			while (true) {
				reset_reserve_parameter();
				printf("취소 정보를 입력해주세요\n");
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
					printf("reservation_date_time_list.txt 파일이 없거나 손상되었습니다.\n");
					break;
				}
				if (!check_file_date_time_list(fd)) { //파일 오류이면
					fclose(fd);
					break;
				}
				FILE* fd2 = fopen("reservation_list.txt", "r");
				if (fd2 == NULL) {
					printf("reservation_list.txt 파일이 없거나 손상되었습니다.\n");
					break;
				}
				if (!check_file_list(fd2)) { //파일 오류이면
					fclose(fd2);
					break;
				}
				if(!strcmp(input_string2, "Q") || !strcmp(input_string2, "q")) 
					break;
				if (cancel_main(input_string2)) { //예약 성공
					if (check_date_and_time(date, time)) { //시간 미래임
						cancel_list();
						cancel_time();
						printf("예약 취소가 완료되었습니다.\n");
						break;
					}
					else {
							printf("과거의 예약은 취소 할 수 없습니다.\n");
					}
					
				}
				else { //예약 실패
				}
			}
		
		}
		else if (!strcmp(menu_input, "5")) { //case5, 예약종료
			break;
		}
		else {
			printf("메뉴 선택을 다시해주세요.\n");
		}

	}
}