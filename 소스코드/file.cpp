#include "file.h"

int write_reservation() {

	_wsetlocale(LC_ALL, L"korean");

	char* student_id = get_check_parameter().STUDENT_ID;
	char* building = get_check_parameter().BUILDING;
	char* date = get_check_parameter().DATE;
	char accurate_time_tmp[100];
	char* people_num = get_check_parameter().PEOPLE_NUMBER;
	char* room_num = get_check_parameter().ROOM_NUMBER;

	strcpy(accurate_time_tmp, get_check_parameter().ACCURATE_TIME);

	char* start_time = strtok(accurate_time_tmp, "~");
	char* end_time = strtok(NULL, "~");
	char str[1000];
	char str2[1000];
	int count = 0;
	int max_count = 200;

	FILE* file_pointer;

	/*file_pointer = fopen("reservation_list.txt", "r");
	if (file_pointer == NULL) {
		printf("reservation_list.txt 파일이 없거나 손상되었습니다.\n");
		return 0;
	}
	if (!check_file_list(file_pointer)) {
		fclose(file_pointer);
		return 0;
	}
	fclose(file_pointer);*/

	file_pointer = fopen("reservation_list.txt", "a");
	if (file_pointer == NULL) {
		printf("reservation_list.txt 파일이 없거나 손상되었습니다.\n");
		return 0;
	}
	

	fprintf(file_pointer, "%s %s,%s,%s,%s,%s,%s\n", student_id, building, date, start_time, end_time, people_num, room_num);


	fclose(file_pointer);
	return 1;
}

int read_reservation_time_check() {

	char* building = get_check_parameter().BUILDING;
	char* date = get_check_parameter().DATE;
	char* accurate_time = get_check_parameter().ACCURATE_TIME;
	char* hosil = get_check_parameter().ROOM_NUMBER;

	char temp[20];
	char* temp_start;
	char* temp_end;
	char str[1000];
	char* list[20];
	int return_flag = 1;
	
	strcpy(temp, accurate_time);

	temp_start = strtok(temp, "~");
	temp_end = strtok(NULL, "~");

	FILE* file_pointer;

	/*file_pointer = fopen("reservation_date_time_list.txt", "r");

	if (file_pointer == NULL) {
		printf("reservation_date_time_list.txt 파일이 없거나 손상되었습니다.\n");
		return -1;
	}

	if (!check_file_date_time_list(file_pointer)) {
		fclose(file_pointer);
		return -1;
	}
	fclose(file_pointer);*/
	file_pointer = fopen("reservation_date_time_list.txt", "r");

	if (file_pointer == NULL) {
		printf("reservation_date_time_list.txt 파일이 없거나 손상되었습니다.\n");
		return -1;
	}
	while (fgets(str,1000,file_pointer) != NULL) {
		//printf("%s", str);
		int i = 0;
		list[i] = strtok(str, " ");
		//	printf("%s", list[i]);
		for (i = 1; i < 16; i++) {
			list[i] = strtok(NULL, " ");
			//printf("%s", list[i]);
}
		if (!strcmp(list[0], building) && !strcmp(list[1], hosil) && !strcmp(list[2], date)) {
			for (int j = 0; j < atoi(temp_end) - atoi(temp_start); j++) {
				if (!strcmp(list[atoi(temp_start) + j - 6], "x") || !strcmp(list[atoi(temp_start) + j - 6], "x\n")) {
					fclose(file_pointer);
					return 0;
				}

		//printf("%s", list[atoi(temp_start) + j - 6]);
	}

}
	}
	fclose(file_pointer);
	return return_flag;

}

int write_reservation_time() {

	char* building = get_check_parameter().BUILDING;
	char* date = get_check_parameter().DATE;
	char* accurate_time = get_check_parameter().ACCURATE_TIME;
	char* hosil = get_check_parameter().ROOM_NUMBER;

	char temp[20];
	char* temp_start;
	char* temp_end;
	char str[1000];
	char* list[20];

	char x[] = "x";
	char x_2[] = "x\n";
	char o[] = "o";
	char o_2[] = "o\n";

	int count = 0;
	int max_count = 200;

	strcpy(temp, accurate_time);

	temp_start = strtok(temp, "~");
	temp_end = strtok(NULL, "~");

	FILE* file_pointer;

	/*file_pointer = fopen("reservation_date_time_list.txt", "r");
	if (file_pointer == NULL) {
		printf("reservation_date_time_list.txt 파일이 없거나 손상되었습니다.\n");
		return 0;
	}
	if (!check_file_date_time_list(file_pointer)) {
		fclose(file_pointer);
		return 0;
	}
	fclose(file_pointer);*/

	file_pointer = fopen("reservation_date_time_list.txt", "r");
	if (file_pointer == NULL) {
		printf("reservation_date_time_list.txt 파일이 없거나 손상되었습니다.\n");
		return 0;
	}

	while (fgets(str, 1000, file_pointer) != NULL) {
		count++;
	}

	char** arr_str = (char**)malloc(sizeof(char*) * count);

	for (int i = 0; i < count; i++) {
		arr_str[i] = (char*)malloc(sizeof(char) * max_count);
	}
	fseek(file_pointer, 0, SEEK_SET);

	int j = 0;
	int k = 0;
	while (fgets(str, 1000, file_pointer) != NULL) {
		//printf("%s", str);

		strcpy(arr_str[j], str);
		j++;
	}
	fclose(file_pointer);

	char* tmp_list[16];
	char tmp_str[200];
	int flag = 0;

	for (int i = 0; i < count; i++) {

		strcpy(tmp_str, arr_str[i]);
		tmp_list[0] = strtok(tmp_str, " ");
		tmp_list[1] = strtok(NULL, " ");
		tmp_list[2] = strtok(NULL, " ");

		if (!strcmp(tmp_list[0], building) && !strcmp(tmp_list[1], hosil) && !strcmp(tmp_list[2], date)) {
			flag = i;
			for (int i = 3; i < 16; i++) {
				tmp_list[i] = strtok(NULL, " ");
			}
		
				for (int i = atoi(temp_start) - 6; i < (atoi(temp_end) - 6); i++) {
					if (i == 15)
						strcpy(tmp_list[i], "x\n");
					else
						strcpy(tmp_list[i], "x");
				}
				break;
		}

	}

	file_pointer = fopen("reservation_date_time_list.txt", "w");
	if (file_pointer == NULL) {
		printf("reservation_date_time_list.txt 파일이 없거나 손상되었습니다.\n");
		return 0;
	}
	if (!flag) { //기존에 방이 없을때.
		tmp_list[0] = building;
		tmp_list[1] = hosil;
		tmp_list[2] = date;

		for (int i = 3; i < 16; i++) {
			if (i >= (atoi(temp_start) - 6) && i < (atoi(temp_end) - 6)) {
				if (i == 15)
					tmp_list[i] = x_2;
				else
					tmp_list[i] = x;
			}
			else if (i == 15)
				tmp_list[i] = o_2;
			else
				tmp_list[i] = o;
		}
		for (int i = 0; i < count; i++) {
			fprintf(file_pointer, "%s", arr_str[i]);
		}
		for (int i = 0; i < 16; i++) {
			if(i==15)
				fprintf(file_pointer, "%s", tmp_list[i]);
			else
				fprintf(file_pointer, "%s ", tmp_list[i]);
		}

	}
	else { //방이 있을때.
		for (int j = 0; j < 16; j++) {
			//strcpy(arr_str[flag], "");
			if (j == 15)
				strcat(arr_str[flag], tmp_list[j]);
			else if (j == 0) {
				strcpy(arr_str[flag], tmp_list[j]);
				strcat(arr_str[flag], " ");
			}
			else {
				strcat(arr_str[flag], tmp_list[j]);
				strcat(arr_str[flag], " ");
			}
		}

		for (int i = 0; i < count; i++) {
			fprintf(file_pointer, "%s", arr_str[i]);
		}

	}

	for (int i = 0; i < count; i++) {
		free(arr_str[i]);
	}
	free(arr_str);

	fclose(file_pointer);
	return 1;
}

int read_my_reservaton(char* s_id) {

	char str[1000];
	char* str2;
	int return_flag = 0;
	FILE* file_pointer;
	char* s_id_tmp;
	int count = 0;
	int max_count = 200;
	//char array[][]

	file_pointer = fopen("reservation_list.txt", "r");

/*	if (file_pointer == NULL) {
		printf("reservation_list.txt 파일이 없거나 손상되었습니다.\n");
		return -1;
	}

	if (!check_file_list(file_pointer)) {
		fclose(file_pointer);
		return -1;
	}
	fclose(file_pointer);*/

	file_pointer = fopen("reservation_list.txt", "r");

	if (file_pointer == NULL) {
		printf("reservation_list.txt 파일이 없거나 손상되었습니다.\n");
		return -1;
	}

	while (fgets(str, 1000, file_pointer) != NULL) {
		count++;
	}
	char **arr_str = (char**)malloc(sizeof(char*) * count);
	
	for (int i = 0; i < count; i++) {
		arr_str[i] = (char*)malloc(sizeof(char) * max_count);
	}

	fseek(file_pointer, 0, SEEK_SET);

	int j = 0;
	int k = 0;
	while (fgets(str, 1000, file_pointer) != NULL) {
		//printf("%s", str);
		
		strcpy(arr_str[j], str);
		j++;
	}

	for (int j = count-1; j >= 0; j--) {
		s_id_tmp = strtok(arr_str[j], " ");
		str2 = strtok(NULL, " ");

		if (!strcmp(s_id_tmp, s_id)) {
			printf("%s", str2);
			if (str2[strlen(str2) - 1] != '\n')
				printf("\n");
			return_flag = 1;
		}
		//printf("%s", arr_str[j]);
	}

	for (int i = 0; i < count; i++) {
		free(arr_str[i]);
	}
	free(arr_str);

	return return_flag;
}

//날짜와 시각이 입력된 함수.
int read_inquery_date_acuurate_time() {

	int building_gonghak[10] = { 0,1,1,1,1,1,1,1,1,0 };
	int building_life[10] = { 0,1,1,1,1,1,1,1,0,0 };
	int building_sangheo[10] = { 0,1,1,1,1,1,1,1,1,0 };
	int building_library[10] = { 0,1,1,1,1,1,1,0,0,0 };
	int building_animal[10] = { 0,1,1,1,1,1,0,0,0,0 };

	char* date = get_check_parameter().DATE;
	char* accurate_time = get_check_parameter().ACCURATE_TIME;
	char temp[100];
	char* temp_start;
	char* temp_end;
	char* list[16];

	strcpy(temp, accurate_time);

	temp_start = strtok(temp, "~");
	temp_end = strtok(NULL, "~");
	
	int output_flag = 0;
	char str[1000];
	int flag = 0;
	/*FILE* file_pointer = fopen("reservation_date_time_list.txt", "r");

	if (file_pointer == NULL) {
		printf("reservation_date_time_list.txt 파일이 없거나 손상되었습니다.\n");
		return 0;
	}
	if (!check_file_date_time_list(file_pointer)) {
		fclose(file_pointer);
		return 0;
	}
	fclose(file_pointer);*/
	FILE* file_pointer = fopen("reservation_date_time_list.txt", "r");
	if (file_pointer == NULL) {
		printf("reservation_date_time_list.txt 파일이 없거나 손상되었습니다.\n");
		return 0;
	}

	//건물명과 인원이 옵션으로 입력.
	if (get_check_parameter().BUILDING != NULL && get_check_parameter().PEOPLE_NUMBER != NULL) {
		char* people_number = get_check_parameter().PEOPLE_NUMBER;
		char a[100];
		int num;
		strcpy(a, people_number);
		num = atoi(strtok(a, "명"));

		//공학관, 생명과학관, 상허연구관, 상허기념도서관, 동물생명과학관
		char buld_1[100];
		strcpy(buld_1, "공학관");
		char buld_2[100];
		strcpy(buld_2, "생명과학관");
		char buld_3[100];
		strcpy(buld_3, "상허연구관");
		char buld_4[100];
		strcpy(buld_4, "상허기념도서관");
		char buld_5[100];
		strcpy(buld_5, "동물생명과학관");


		while (fgets(str, 1000, file_pointer) != NULL) {

			int i = 0;
			list[i] = strtok(str, " ");
			for (i = 1; i < 16; i++) {
				list[i] = strtok(NULL, " ");
			}


			if (!strcmp(list[2], date)) { //일치하는 날짜가 있을때.
				for (int j = 0; j < atoi(temp_end) - atoi(temp_start); j++) {
					if (!strcmp(list[atoi(temp_start) + j - 6], "x") || !strcmp(list[atoi(temp_start) + j - 6], "x\n")) {
						flag = 1;
						break;
					}
				}
				if (flag) {
					char* a;
					int num;
					a = strtok(list[1], "호실");
					num = atoi(a);
					//공학관, 생명과학관, 상허연구관, 상허기념도서관, 동물생명과학관
					if (!strcmp(list[0], "공학관")) {
						building_gonghak[num] = 0;
					}
					else if (!strcmp(list[0], "생명과학관")) {
						building_life[num] = 0;
					}
					else if (!strcmp(list[0], "상허연구관")) {
						building_sangheo[num] = 0;
					}
					else if (!strcmp(list[0], "상허기념도서관")) {
						building_library[num] = 0;
					}
					else if (!strcmp(list[0], "동물생명과학관")) {
						building_animal[num] = 0;
					}
					else {
						printf("이 에러가 출력될리가 없어\n");
					}
				}
				flag = 0;
			}
		}
		for (int i = 1; i < 10; i++) {
			char hosil[100];
			_itoa(i, hosil, 10);
			strcat(hosil, "호실");
			if (check_max_people(buld_1, hosil, people_number) == 0) {
				building_gonghak[i] = 0;
			}
			if (check_max_people(buld_2, hosil, people_number) == 0) {
				building_life[i] = 0;
			}
			if (check_max_people(buld_3, hosil, people_number) == 0) {
				building_sangheo[i] = 0;
			}
			if (check_max_people(buld_4, hosil, people_number) == 0) {
				building_library[i] = 0;
			}
			if (check_max_people(buld_5, hosil, people_number) == 0) {
				building_animal[i] = 0;
			}
		}
		if (!strcmp(get_check_parameter().BUILDING, "공학관")) {
			printf("건물명             호실\n");
			printf("공학관             ");
			for (int i = 0; i < 10; i++) {
				if (building_gonghak[i] == 1) {
					printf("%d호실 ", i);
				}
			}
			printf("\n");
		}
		if (!strcmp(get_check_parameter().BUILDING, "생명과학관")) {
			printf("생명과학관         ");
			for (int i = 0; i < 10; i++) {
				if (building_life[i] == 1) {
					printf("%d호실 ", i);

				}
			}

			printf("\n");
		}
		if (!strcmp(get_check_parameter().BUILDING, "상허연구관")) {
			printf("상허연구관         ");
			for (int i = 0; i < 10; i++) {
				if (building_sangheo[i] == 1) {
					printf("%d호실 ", i);

				}
			}

			printf("\n");
		}
		if (!strcmp(get_check_parameter().BUILDING, "상허기념도서관")) {
			printf("상허기념도서관     ");
			for (int i = 0; i < 10; i++) {
				if (building_library[i] == 1) {
					printf("%d호실 ", i);
				}
			}
			printf("\n");
		}
		if (!strcmp(get_check_parameter().BUILDING, "동물생명과학관")) {
			printf("동물생명과학관     ");
			for (int i = 0; i < 10; i++) {
				if (building_animal[i] == 1) {
					printf("%d호실 ", i);
				}
			}
			printf("\n");
		}

	}
	//건물만 입력 되었을때.
	else if (get_check_parameter().BUILDING != NULL) {


		while (fgets(str, 1000, file_pointer) != NULL) {
			int i = 0;
			list[i] = strtok(str, " ");
			for (i = 1; i < 16; i++) {
				list[i] = strtok(NULL, " ");
			}


			if (!strcmp(list[2], date)) { //일치하는 날짜가 있을때.
				for (int j = 0; j < atoi(temp_end) - atoi(temp_start); j++) {
					if (!strcmp(list[atoi(temp_start) + j - 6], "x") || !strcmp(list[atoi(temp_start) + j - 6], "x\n")) {
						flag = 1;
						break;
					}
				}
				if (flag) {
					char* a;
					int num;
					a = strtok(list[1], "호실");
					num = atoi(a);
					//공학관, 생명과학관, 상허연구관, 상허기념도서관, 동물생명과학관
					if (!strcmp(list[0], "공학관")) {
						building_gonghak[num] = 0;
					}
					else if (!strcmp(list[0], "생명과학관")) {
						building_life[num] = 0;
					}
					else if (!strcmp(list[0], "상허연구관")) {
						building_sangheo[num] = 0;
					}
					else if (!strcmp(list[0], "상허기념도서관")) {
						building_library[num] = 0;
					}
					else if (!strcmp(list[0], "동물생명과학관")) {
						building_animal[num] = 0;
					}
					else {
						printf("이 에러가 출력될리가 없어\n");
					}
				}
				flag = 0;
			}
		}

		if (!strcmp(get_check_parameter().BUILDING, "공학관")) {
			printf("건물명             호실\n");
			printf("공학관             ");
			for (int i = 0; i < 10; i++) {
				if (building_gonghak[i] == 1) {
					printf("%d호실 ", i);
				}
			}
			printf("\n");
		}
		if (!strcmp(get_check_parameter().BUILDING, "생명과학관")) {
			printf("생명과학관         ");
			for (int i = 0; i < 10; i++) {
				if (building_life[i] == 1) {
					printf("%d호실 ", i);

				}
			}

			printf("\n");
		}
		if (!strcmp(get_check_parameter().BUILDING, "상허연구관")) {
			printf("상허연구관         ");
			for (int i = 0; i < 10; i++) {
				if (building_sangheo[i] == 1) {
					printf("%d호실 ", i);

				}
			}

			printf("\n");
		}
		if (!strcmp(get_check_parameter().BUILDING, "상허기념도서관")) {
			printf("상허기념도서관     ");
			for (int i = 0; i < 10; i++) {
				if (building_library[i] == 1) {
					printf("%d호실 ", i);
				}
			}
			printf("\n");
		}
		if (!strcmp(get_check_parameter().BUILDING, "동물생명과학관")) {
			printf("동물생명과학관     ");
			for (int i = 0; i < 10; i++) {
				if (building_animal[i] == 1) {
					printf("%d호실 ", i);
				}
			}
			printf("\n");
		}
	
	}
	//인원만 입력 되었을때.
	else if (get_check_parameter().PEOPLE_NUMBER != NULL) {
		char* people_number = get_check_parameter().PEOPLE_NUMBER;
		char a[100];
		int num;
		strcpy(a, people_number);
		num = atoi(strtok(a, "명"));

		//공학관, 생명과학관, 상허연구관, 상허기념도서관, 동물생명과학관
		char buld_1[100];
		strcpy(buld_1, "공학관");
		char buld_2[100];
		strcpy(buld_2, "생명과학관");
		char buld_3[100];
		strcpy(buld_3, "상허연구관");
		char buld_4[100];
		strcpy(buld_4, "상허기념도서관");
		char buld_5[100];
		strcpy(buld_5, "동물생명과학관");
		

		while (fgets(str, 1000, file_pointer) != NULL) {

			int i = 0;
			list[i] = strtok(str, " ");
			for (i = 1; i < 16; i++) {
				list[i] = strtok(NULL, " ");
			}


			if (!strcmp(list[2], date)) { //일치하는 날짜가 있을때.
				for (int j = 0; j < atoi(temp_end) - atoi(temp_start); j++) {
					if (!strcmp(list[atoi(temp_start) + j - 6], "x") || !strcmp(list[atoi(temp_start) + j - 6], "x\n")) {
						flag = 1;
						break;
					}
				}
				if (flag) {
					char* a;
					int num;
					a = strtok(list[1], "호실");
					num = atoi(a);
					//공학관, 생명과학관, 상허연구관, 상허기념도서관, 동물생명과학관
					if (!strcmp(list[0], "공학관")) {
						building_gonghak[num] = 0;
					}
					else if (!strcmp(list[0], "생명과학관")) {
						building_life[num] = 0;
					}
					else if (!strcmp(list[0], "상허연구관")) {
						building_sangheo[num] = 0;
					}
					else if (!strcmp(list[0], "상허기념도서관")) {
						building_library[num] = 0;
					}
					else if (!strcmp(list[0], "동물생명과학관")) {
						building_animal[num] = 0;
					}
					else {
						printf("이 에러가 출력될리가 없어\n");
					}
				}
				flag = 0;
			}
		}

		for (int i = 1; i < 10; i++) {
			char hosil[100];
			_itoa(i, hosil, 10);
			strcat(hosil, "호실");
			if (check_max_people(buld_1, hosil, people_number) == 0) {
				building_gonghak[i] = 0;
			}
			if (check_max_people(buld_2, hosil, people_number) == 0) {
				building_life[i] = 0;
			}
			if (check_max_people(buld_3, hosil, people_number) == 0) {
				building_sangheo[i] = 0;
			}
			if (check_max_people(buld_4, hosil, people_number) == 0) {
				building_library[i] = 0;
			}
			if (check_max_people(buld_5, hosil, people_number) == 0) {
				building_animal[i] = 0;
			}
		}
		printf("건물명             호실\n");
		printf("공학관             ");
		for (int i = 0; i < 10; i++) {
			if (building_gonghak[i] == 1) {
				printf("%d호실 ", i);
			}
		}
		printf("\n");
		printf("생명과학관         ");
		for (int i = 0; i < 10; i++) {
			if (building_life[i] == 1) {
				printf("%d호실 ", i);

			}
		}
		printf("\n");
		printf("상허연구관         ");
		for (int i = 0; i < 10; i++) {
			if (building_sangheo[i] == 1) {
				printf("%d호실 ", i);

			}
		}
		printf("\n");
		printf("상허기념도서관     ");
		for (int i = 0; i < 10; i++) {
			if (building_library[i] == 1) {
				printf("%d호실 ", i);
			}
		}
		printf("\n");
		printf("동물생명과학관     ");
		for (int i = 0; i < 10; i++) {
			if (building_animal[i] == 1) {
				printf("%d호실 ", i);
			}
		}
		printf("\n");
	
	}
	//옵션이 입력되지 않았을때.
	else {

		while (fgets(str, 1000, file_pointer) != NULL) {

			int i = 0;
			list[i] = strtok(str, " ");
			for (i = 1; i < 16; i++) {
				list[i] = strtok(NULL, " ");
			}


			if (!strcmp(list[2], date)) { //일치하는 날짜가 있을때.
				for (int j = 0; j < atoi(temp_end) - atoi(temp_start); j++) {
					if (!strcmp(list[atoi(temp_start) + j - 6], "x") || !strcmp(list[atoi(temp_start) + j - 6], "x\n")) {
						flag = 1;
						break;
					}
				}
				if(flag) {
					char* a;
					int num;
					a = strtok(list[1], "호실");
					num = atoi(a);
					//공학관, 생명과학관, 상허연구관, 상허기념도서관, 동물생명과학관
					if (!strcmp(list[0], "공학관")) {
						building_gonghak[num] = 0;
					}
					else if (!strcmp(list[0], "생명과학관")) {
						building_life[num] = 0;
					}
					else if (!strcmp(list[0], "상허연구관")) {
						building_sangheo[num] = 0;
					}
					else if (!strcmp(list[0], "상허기념도서관")) {
						building_library[num] = 0;
					}
					else if (!strcmp(list[0], "동물생명과학관")) {
						building_animal[num] = 0;
					}
					else {
						printf("이 에러가 출력될리가 없어\n");
					}
				}
				flag = 0;
			}
		}

		printf("건물명             호실\n");
		printf("공학관             ");
		for (int i = 0; i < 10; i++) {
			if (building_gonghak[i] == 1) {
				printf("%d호실 ", i);
			}
		}
		printf("\n");
		printf("생명과학관         ");
		for (int i = 0; i < 10; i++) {
			if (building_life[i] == 1) {
				printf("%d호실 ", i);
	
			}
		}
		printf("\n");
		printf("상허연구관         ");
		for (int i = 0; i < 10; i++) {
			if (building_sangheo[i] == 1) {
				printf("%d호실 ", i);
		
			}
		}
		printf("\n");
		printf("상허기념도서관     ");
		for (int i = 0; i < 10; i++) {
			if (building_library[i] == 1) {
				printf("%d호실 ", i);
			}
		}
		printf("\n");
		printf("동물생명과학관     ");
		for (int i = 0; i < 10; i++) {
			if (building_animal[i] == 1) {
				printf("%d호실 ", i);
			}
		}
		printf("\n");
	}
	fclose(file_pointer);
	return 1;
}

//날짜와 시간이 입력된 함수.
int read_inquery_date_during_time() {

	// 건물명[0][] : 방 존재 여부, 건물명[1][] 각 시간별 가능 여부.
	int building_gonghak[9][13] = { {0,1,1,1,1,1,1,1,1,0,0,0,0 }, {1,1,1,1,1,1,1,1,1,1,1,1,1}, {1,1,1,1,1,1,1,1,1,1,1,1,1} , {1,1,1,1,1,1,1,1,1,1,1,1,1} , {1,1,1,1,1,1,1,1,1,1,1,1,1} , {1,1,1,1,1,1,1,1,1,1,1,1,1} , {1,1,1,1,1,1,1,1,1,1,1,1,1} , {1,1,1,1,1,1,1,1,1,1,1,1,1} , {1,1,1,1,1,1,1,1,1,1,1,1,1} };
	int building_life[9][13] = { { 0,1,1,1,1,1,1,1,0,0,0,0,0 }, {1,1,1,1,1,1,1,1,1,1,1,1,1}, {1,1,1,1,1,1,1,1,1,1,1,1,1}, {1,1,1,1,1,1,1,1,1,1,1,1,1}, {1,1,1,1,1,1,1,1,1,1,1,1,1}, {1,1,1,1,1,1,1,1,1,1,1,1,1}, {1,1,1,1,1,1,1,1,1,1,1,1,1}, {1,1,1,1,1,1,1,1,1,1,1,1,1}, {1,1,1,1,1,1,1,1,1,1,1,1,1} };
	int building_sangheo[9][13] = { { 0,1,1,1,1,1,1,1,1,0,0,0,0 }, {1,1,1,1,1,1,1,1,1,1,1,1,1} , {1,1,1,1,1,1,1,1,1,1,1,1,1} , {1,1,1,1,1,1,1,1,1,1,1,1,1} , {1,1,1,1,1,1,1,1,1,1,1,1,1} , {1,1,1,1,1,1,1,1,1,1,1,1,1} , {1,1,1,1,1,1,1,1,1,1,1,1,1} , {1,1,1,1,1,1,1,1,1,1,1,1,1} , {1,1,1,1,1,1,1,1,1,1,1,1,1} };
	int building_library[9][13] = { { 0,1,1,1,1,1,1,0,0,0,0,0,0 }, {1,1,1,1,1,1,1,1,1,1,1,1,1}, {1,1,1,1,1,1,1,1,1,1,1,1,1}, {1,1,1,1,1,1,1,1,1,1,1,1,1}, {1,1,1,1,1,1,1,1,1,1,1,1,1}, {1,1,1,1,1,1,1,1,1,1,1,1,1}, {1,1,1,1,1,1,1,1,1,1,1,1,1}, {1,1,1,1,1,1,1,1,1,1,1,1,1}, {1,1,1,1,1,1,1,1,1,1,1,1,1} };
	int building_animal[9][13] = { {0,1,1,1,1,1,0,0,0,0,0,0,0 }, {1,1,1,1,1,1,1,1,1,1,1,1,1}, {1,1,1,1,1,1,1,1,1,1,1,1,1}, {1,1,1,1,1,1,1,1,1,1,1,1,1}, {1,1,1,1,1,1,1,1,1,1,1,1,1}, {1,1,1,1,1,1,1,1,1,1,1,1,1}, {1,1,1,1,1,1,1,1,1,1,1,1,1}, {1,1,1,1,1,1,1,1,1,1,1,1,1}, {1,1,1,1,1,1,1,1,1,1,1,1,1} };

	char* date = get_check_parameter().DATE;
	char* during_time = get_check_parameter().DURING_TIME;
	char temp[100];
	char* temp_during_num;
	char* temp_end;
	char* list[16];

	char build_1[100];
	strcpy(build_1, "공학관");
	char build_2[100];
	strcpy(build_2, "생명과학관");
	char build_3[100];
	strcpy(build_3, "상허연구관");
	char build_4[100];
	strcpy(build_4, "상허기념도서관");
	char build_5[100];
	strcpy(build_5, "동물생명과학관");

	strcpy(temp, during_time);

	temp_during_num = strtok(temp, "시간");

	int output_flag = 0;

	FILE* file_pointer = fopen("reservation_date_time_list.txt", "r");
	char str[1000];
	int flag = 0;

	if (file_pointer == NULL) {
		printf("reservation_date_time_list.txt 파일이 없거나 손상되었습니다.\n");
		return 0;
	}

	/*if (!check_file_date_time_list(file_pointer)) {
		fclose(file_pointer);
		return 0;
	}
	fclose(file_pointer);*/
	/*file_pointer = fopen("reservation_date_time_list.txt", "r");
	if (file_pointer == NULL) {
		printf("reservation_date_time_list.txt 파일이 없거나 손상되었습니다.\n");
		return 0;
	}*/

	//건물명과 인원이 옵션으로 입력.
	if (get_check_parameter().BUILDING != NULL && get_check_parameter().PEOPLE_NUMBER != NULL){
		char* people_number = get_check_parameter().PEOPLE_NUMBER;
		while (fgets(str, 1000, file_pointer) != NULL) {

			int i = 0;
			int count = 0;
			int flag = 0;
			list[i] = strtok(str, " ");
			for (i = 1; i < 16; i++) {
				list[i] = strtok(NULL, " ");
			}
			char* a;
			int num;
			a = strtok(list[1], "호실");
			if (a == NULL)
				continue;
			num = atoi(a);
			if (!strcmp(list[2], date)) {
				for (int j = 0; j < 13; j++) {
					if (!strcmp(list[j + 3], "o") || !strcmp(list[j + 3], "o\n")) {
						count++;
					}
					else {
						if (!strcmp(list[0], build_1)) {
							building_gonghak[num][j] = 0;
						}
						if (!strcmp(list[0], build_2)) {
							building_life[num][j] = 0;
						}
						if (!strcmp(list[0], build_3)) {
							building_sangheo[num][j] = 0;
						}
						if (!strcmp(list[0], build_4)) {
							building_library[num][j] = 0;
						}
						if (!strcmp(list[0], build_5)) {
							building_animal[num][j] = 0;
						}
						count = 0;
					}
					if (count >= atoi(temp_during_num)) {
						flag = 1;
					}
				}

				if (flag == 1) { //시간이 있으면, 시각 배열 정보를 변경

				}
				else { //시간이 없으면 호실 정보에서 지움.

					if (!strcmp(list[0], build_1)) {
						building_gonghak[0][num] = 0;
					}
					if (!strcmp(list[0], build_2)) {
						building_life[0][num] = 0;
					}
					if (!strcmp(list[0], build_3)) {
						building_sangheo[0][num] = 0;
					}
					if (!strcmp(list[0], build_4)) {
						building_library[0][num] = 0;
					}
					if (!strcmp(list[0], build_5)) {
						building_animal[0][num] = 0;
					}

				}
			}

		}
		printf("건물명          호실 09 10 11 12 13 14 15 16 17 18 19 20 21\n");
		if (!strcmp(get_check_parameter().BUILDING, "공학관")) {
			for (int i = 0; i < 8; i++) {
				char hosil[100];
				_itoa(i + 1, hosil, 10);
				strcat(hosil, "호실");
				if (!check_max_people(build_1, hosil, people_number))
					continue;
				if (building_gonghak[0][i + 1]) {
					for (int j = 0; j < 13; j++) {
						if (j == 0) {
							printf("공학관          ");
							printf("%d호실 ", i + 1);
						}
						if (building_gonghak[i + 1][j]) {
							printf("o ");
						}
						else
							printf("x ");
						if (j != 12)
							printf(" ");
					}
					printf("\n");
				}
			}
		}
		if (!strcmp(get_check_parameter().BUILDING, "생명과학관")) {
			for (int i = 0; i < 8; i++) {
				char hosil[100];
				_itoa(i + 1, hosil, 10);
				strcat(hosil, "호실");
				if (!check_max_people(build_2, hosil, people_number))
					continue;
				if (building_life[0][i + 1]) {
					for (int j = 0; j < 13; j++) {
						if (j == 0) {
							printf("생명과학관      ");
							printf("%d호실 ", i + 1);
						}
						if (building_life[i + 1][j]) {
							printf("o ");
						}
						else
							printf("x ");
						if (j != 12)
							printf(" ");
					}
					printf("\n");
				}
			}
		}
		if (!strcmp(get_check_parameter().BUILDING, "상허연구관")) {
			for (int i = 0; i < 8; i++) {
				char hosil[100];
				_itoa(i + 1, hosil, 10);
				strcat(hosil, "호실");
				if (!check_max_people(build_3, hosil, people_number))
					continue;
				if (building_library[0][i + 1]) {
					for (int j = 0; j < 13; j++) {
						if (j == 0) {
							printf("상허연구관      ");
							printf("%d호실 ", i + 1);
						}
						if (building_sangheo[i + 1][j]) {
							printf("o ");
						}
						else
							printf("x ");
						if (j != 12)
							printf(" ");
					}
					printf("\n");
				}
			}
		}

		if (!strcmp(get_check_parameter().BUILDING, "상허기념도서관")) {
			for (int i = 0; i < 8; i++) {
				char hosil[100];
				_itoa(i + 1, hosil, 10);
				strcat(hosil, "호실");
				if (!check_max_people(build_4, hosil, people_number))
					continue;
				if (building_library[0][i + 1]) {
					for (int j = 0; j < 13; j++) {
						if (j == 0) {
							printf("상허기념도서관  ");
							printf("%d호실 ", i + 1);
						}
						if (building_library[i + 1][j]) {
							printf("o ");
						}
						else
							printf("x ");
						if (j != 12)
							printf(" ");
					}
					printf("\n");
				}
			}
		}

		if (!strcmp(get_check_parameter().BUILDING, "동물생명과학관")) {
			for (int i = 0; i < 8; i++) {
				char hosil[100];
				_itoa(i + 1, hosil, 10);
				strcat(hosil, "호실");
				if (!check_max_people(build_5, hosil, people_number))
					continue;
				if (building_animal[0][i + 1]) {
					for (int j = 0; j < 13; j++) {
						if (j == 0) {
							printf("동물생명과학관  ");
							printf("%d호실 ", i + 1);
						}

						if (building_animal[i + 1][j]) {
							printf("o ");
						}
						else
							printf("x ");
						if (j != 12)
							printf(" ");
					}
					printf("\n");
				}
			}
		}

	}
	//건물만 입력 되었을때.
	else if (get_check_parameter().BUILDING != NULL) {
		while (fgets(str, 1000, file_pointer) != NULL) {

			int i = 0;
			int count = 0;
			int flag = 0;
			list[i] = strtok(str, " ");
			for (i = 1; i < 16; i++) {
				list[i] = strtok(NULL, " ");
			}
			char* a;
			int num;
			a = strtok(list[1], "호실");
			if (a == NULL)
				continue;
			num = atoi(a);
			if (!strcmp(list[2], date)) {
				for (int j = 0; j < 13; j++) {
					if (!strcmp(list[j + 3], "o") || !strcmp(list[j + 3], "o\n")) {
						count++;
					}
					else {
						if (!strcmp(list[0], build_1)) {
							building_gonghak[num][j] = 0;
						}
						if (!strcmp(list[0], build_2)) {
							building_life[num][j] = 0;
						}
						if (!strcmp(list[0], build_3)) {
							building_sangheo[num][j] = 0;
						}
						if (!strcmp(list[0], build_4)) {
							building_library[num][j] = 0;
						}
						if (!strcmp(list[0], build_5)) {
							building_animal[num][j] = 0;
						}
						count = 0;
					}
					if (count >= atoi(temp_during_num)) {
						flag = 1;
					}
				}

				if (flag == 1) { //시간이 있으면, 시각 배열 정보를 변경

				}
				else { //시간이 없으면 호실 정보에서 지움.

					if (!strcmp(list[0], build_1)) {
						building_gonghak[0][num] = 0;
					}
					if (!strcmp(list[0], build_2)) {
						building_life[0][num] = 0;
					}
					if (!strcmp(list[0], build_3)) {
						building_sangheo[0][num] = 0;
					}
					if (!strcmp(list[0], build_4)) {
						building_library[0][num] = 0;
					}
					if (!strcmp(list[0], build_5)) {
						building_animal[0][num] = 0;
					}

				}
			}

		}
		printf("건물명          호실 09 10 11 12 13 14 15 16 17 18 19 20 21\n");
		if (!strcmp(get_check_parameter().BUILDING, "공학관")) {
			for (int i = 0; i < 8; i++) {
				if (building_gonghak[0][i + 1]) {
					for (int j = 0; j < 13; j++) {
						if (j == 0) {
							printf("공학관          ");
							printf("%d호실 ", i + 1);
						}
						if (building_gonghak[i + 1][j]) {
							printf("o ");
						}
						else
							printf("x ");
						if (j != 12)
							printf(" ");
					}
					printf("\n");
				}
			}
		}
		if (!strcmp(get_check_parameter().BUILDING, "생명과학관")) {
			for (int i = 0; i < 8; i++) {
				if (building_life[0][i + 1]) {
					for (int j = 0; j < 13; j++) {
						if (j == 0) {
							printf("생명과학관      ");
							printf("%d호실 ", i + 1);
						}
						if (building_life[i + 1][j]) {
							printf("o ");
						}
						else
							printf("x ");
						if (j != 12)
							printf(" ");
					}
					printf("\n");
				}
			}
		}
		if (!strcmp(get_check_parameter().BUILDING, "상허연구관")) {
			for (int i = 0; i < 8; i++) {
				if (building_library[0][i + 1]) {
					for (int j = 0; j < 13; j++) {
						if (j == 0) {
							printf("상허연구관      ");
							printf("%d호실 ", i + 1);
						}
						if (building_sangheo[i + 1][j]) {
							printf("o ");
						}
						else
							printf("x ");
						if (j != 12)
							printf(" ");
					}
					printf("\n");
				}
			}
		}
		
		if (!strcmp(get_check_parameter().BUILDING, "상허기념도서관")) {
			for (int i = 0; i < 8; i++) {
				if (building_library[0][i + 1]) {
					for (int j = 0; j < 13; j++) {
						if (j == 0) {
							printf("상허기념도서관  ");
							printf("%d호실 ", i + 1);
						}
						if (building_library[i + 1][j]) {
							printf("o ");
						}
						else
							printf("x ");
						if (j != 12)
							printf(" ");
					}
					printf("\n");
				}
			}
		}
	
		if (!strcmp(get_check_parameter().BUILDING, "동물생명과학관")) {
			for (int i = 0; i < 8; i++) {
				if (building_animal[0][i + 1]) {
					for (int j = 0; j < 13; j++) {
						if (j == 0) {
							printf("동물생명과학관  ");
							printf("%d호실 ", i + 1);
						}

						if (building_animal[i + 1][j]) {
							printf("o ");
						}
						else
							printf("x ");
						if (j != 12)
							printf(" ");
					}
					printf("\n");
				}
			}
		}

	}
	//인원만 입력 되었을때.
	else if (get_check_parameter().PEOPLE_NUMBER != NULL) {

	char* people_number = get_check_parameter().PEOPLE_NUMBER;
	
	while (fgets(str, 1000, file_pointer) != NULL) {

		int i = 0;
		int count = 0;
		int flag = 0;
		list[i] = strtok(str, " ");
		for (i = 1; i < 16; i++) {
			list[i] = strtok(NULL, " ");
		}
		char* a;
		int num;
		a = strtok(list[1], "호실");
		if (a == NULL)
			continue;
		num = atoi(a);
		if (!strcmp(list[2], date)) {
			for (int j = 0; j < 13; j++) {
				if (!strcmp(list[j + 3], "o") || !strcmp(list[j + 3], "o\n")) {
					count++;
				}
				else {
					if (!strcmp(list[0], build_1)) {
						building_gonghak[num][j] = 0;
					}
					if (!strcmp(list[0], build_2)) {
						building_life[num][j] = 0;
					}
					if (!strcmp(list[0], build_3)) {
						building_sangheo[num][j] = 0;
					}
					if (!strcmp(list[0], build_4)) {
						building_library[num][j] = 0;
					}
					if (!strcmp(list[0], build_5)) {
						building_animal[num][j] = 0;
					}
					count = 0;
				}
				if (count >= atoi(temp_during_num)) {
					flag = 1;
				}
			}

			if (flag == 1) { //시간이 있으면, 시각 배열 정보를 변경

			}
			else { //시간이 없으면 호실 정보에서 지움.

				if (!strcmp(list[0], build_1)) {
					building_gonghak[0][num] = 0;
				}
				if (!strcmp(list[0], build_2)) {
					building_life[0][num] = 0;
				}
				if (!strcmp(list[0], build_3)) {
					building_sangheo[0][num] = 0;
				}
				if (!strcmp(list[0], build_4)) {
					building_library[0][num] = 0;
				}
				if (!strcmp(list[0], build_5)) {
					building_animal[0][num] = 0;
				}

			}
		}

	}
	printf("건물명          호실 09 10 11 12 13 14 15 16 17 18 19 20 21\n");
	for (int i = 0; i < 8; i++) {
		char hosil[100];
		_itoa(i+1, hosil, 10);
		strcat(hosil, "호실");
		if (check_max_people(build_1, hosil, people_number)==0)
			continue;
		if (building_gonghak[0][i + 1]) {
			for (int j = 0; j < 13; j++) {
				if (j == 0) {
					printf("공학관          ");
					printf("%d호실 ", i + 1);
				}
				if (building_gonghak[i + 1][j]) {
					printf("o ");
				}
				else
					printf("x ");
				if (j != 12)
					printf(" ");
			}
			printf("\n");
		}
	}
	for (int i = 0; i < 8; i++) {
		char hosil[100];
		_itoa(i + 1, hosil, 10);
		strcat(hosil, "호실");
		if (!check_max_people(build_2, hosil, people_number))
			continue;
		if (building_life[0][i + 1]) {
			for (int j = 0; j < 13; j++) {
				if (j == 0) {
					printf("생명과학관      ");
					printf("%d호실 ", i + 1);
				}
				if (building_life[i + 1][j]) {
					printf("o ");
				}
				else
					printf("x ");
				if (j != 12)
					printf(" ");
			}
			printf("\n");
		}
	}
	for (int i = 0; i < 8; i++) {
		char hosil[100];
		_itoa(i + 1, hosil, 10);
		strcat(hosil, "호실");
		if (!check_max_people(build_3, hosil, people_number))
			continue;
		if (building_library[0][i + 1]) {
			for (int j = 0; j < 13; j++) {
				if (j == 0) {
					printf("상허연구관      ");
					printf("%d호실 ", i + 1);
				}
				if (building_sangheo[i + 1][j]) {
					printf("o ");
				}
				else
					printf("x ");
				if (j != 12)
					printf(" ");
			}
			printf("\n");
		}
	}
	for (int i = 0; i < 8; i++) {
		char hosil[100];
		_itoa(i + 1, hosil, 10);
		strcat(hosil, "호실");
		if (!check_max_people(build_4, hosil, people_number))
			continue;
		if (building_library[0][i + 1]) {
			for (int j = 0; j < 13; j++) {
				if (j == 0) {
					printf("상허기념도서관  ");
					printf("%d호실 ", i + 1);
				}
				if (building_library[i + 1][j]) {
					printf("o ");
				}
				else
					printf("x ");
				if (j != 12)
					printf(" ");
			}
			printf("\n");
		}
	}
	for (int i = 0; i < 8; i++) {
		char hosil[100];
		_itoa(i + 1, hosil, 10);
		strcat(hosil, "호실");
		if (!check_max_people(build_5, hosil, people_number))
			continue;
		if (building_animal[0][i + 1]) {
			for (int j = 0; j < 13; j++) {
				if (j == 0) {
					printf("동물생명과학관  ");
					printf("%d호실 ", i + 1);
				}

				if (building_animal[i + 1][j]) {
					printf("o ");
				}
				else
					printf("x ");
				if (j != 12)
					printf(" ");
			}
			printf("\n");
		}
	}

	}
	//옵션이 입력되지 않았을때.
	else {
		//날짜와 시간.

		while (fgets(str, 1000, file_pointer) != NULL) {

			int i = 0;
			int count = 0;
			int flag = 0;
			list[i] = strtok(str, " ");
			for (i = 1; i < 16; i++) {
				list[i] = strtok(NULL, " ");
			}
			char* a;
			int num;
			a = strtok(list[1], "호실");
			if (a == NULL)
				continue;
			num = atoi(a);
			if (!strcmp(list[2], date)) {
				for (int j = 0; j < 13; j++) {
					if (!strcmp(list[j + 3], "o") || !strcmp(list[j + 3], "o\n")) {
						count++;
					}
					else {
						if (!strcmp(list[0], build_1)) {
							building_gonghak[num][j] = 0;
						}
						if (!strcmp(list[0], build_2)) {
							building_life[num][j] = 0;
						}
						if (!strcmp(list[0], build_3)) {
							building_sangheo[num][j] = 0;
						}
						if (!strcmp(list[0], build_4)) {
							building_library[num][j] = 0;
						}
						if (!strcmp(list[0], build_5)) {
							building_animal[num][j] = 0;
						}
						count = 0;
					}
					if (count >= atoi(temp_during_num)) {
						flag = 1;
					}
				}

				if (flag == 1) { //시간이 있으면, 시각 배열 정보를 변경

				}
				else { //시간이 없으면 호실 정보에서 지움.

					if (!strcmp(list[0], build_1)) {
						building_gonghak[0][num] = 0;
					}
					if (!strcmp(list[0], build_2)) {
						building_life[0][num] = 0;
					}
					if (!strcmp(list[0], build_3)) {
						building_sangheo[0][num] = 0;
					}
					if (!strcmp(list[0], build_4)) {
						building_library[0][num] = 0;
					}
					if (!strcmp(list[0], build_5)) {
						building_animal[0][num] = 0;
					}
					
				}
			}
			
		}       
		printf("건물명          호실 09 10 11 12 13 14 15 16 17 18 19 20 21\n");
		for (int i = 0; i < 8; i++) {
			if (building_gonghak[0][i + 1]) {
				for (int j = 0; j < 13; j++) {
					if (j == 0) {
						printf("공학관          ");
						printf("%d호실 ", i + 1);
					}
					if (building_gonghak[i+1][j]) {
						printf("o ");
					}
					else
						printf("x ");
					if (j != 12)
						printf(" ");
				}
				printf("\n");
			}
		}
		for (int i = 0; i < 8; i++) {
			if (building_life[0][i + 1]) {
				for (int j = 0; j < 13; j++) {
					if (j == 0) {
						printf("생명과학관      ");
						printf("%d호실 ", i + 1);
					}
					if (building_life[i+1][j]) {
						printf("o ");
					}
					else
						printf("x ");
					if (j != 12)
						printf(" ");
				}
				printf("\n");
			}
		}
		for (int i = 0; i < 8; i++) {
			if (building_library[0][i + 1]) {
				for (int j = 0; j < 13; j++) {
					if (j == 0) {
						printf("상허연구관      ");
						printf("%d호실 ", i + 1);
					}
					if (building_sangheo[i + 1][j]) {
						printf("o ");
					}
					else
						printf("x ");
					if (j != 12)
						printf(" ");
				}
				printf("\n");
			}
		}
		for (int i = 0; i < 8; i++) {
			if (building_library[0][i + 1]) {
				for (int j = 0; j < 13; j++) {
					if (j == 0) {
						printf("상허기념도서관  ");
						printf("%d호실 ", i + 1);
					}
					if (building_library[i+1][j]) {
						printf("o ");
					}
					else
						printf("x ");
					if (j != 12)
						printf(" ");
				}
				printf("\n");
			}
		}
		for (int i = 0; i < 8; i++) {
			if (building_animal[0][i + 1]) {
				for (int j = 0; j < 13; j++) {
					if (j == 0) {
						printf("동물생명과학관  ");
						printf("%d호실 ", i + 1);
					}

					if (building_animal[i+1][j]) {
						printf("o ");
					}
					else
						printf("x ");
					if (j != 12)
						printf(" ");
				}
				printf("\n");
			}
		}

	}
	fclose(file_pointer);
	return 1;
}

int check_file_list(FILE* fd) {

	char str[201];
	char str2[201];
	int count = 0;

	if (!check_two_file_line())
		return 0;

	while (fgets(str2, 200, fd) != NULL) {
		count++;
	}
	fseek(fd, 0, SEEK_SET);

	if (count == 0) //파일에 아무것도 입력 안되어있을때. 정상임.
		return 1;
	int flag = 0;

	for (int a = 0; a < count; a++) {
		for (int t = 0; t < 200; t++) {
			if (t > 99) {
				printf("reservation_list.txt %d줄 100글자를 넘길 수 없습니다.\n", a + 1);
				return 0;
			}
			if ( (str[t] = fgetc(fd)) != EOF) { //문자가 있을때.
				if (str[t] == '\n') { //엔터를 만나면 널문자로 바꿈.
					str[t] = '\0';
					break;
				}
			}
			else { //문자가 없다면 탈출
				if (t == 0) {
					return 1;
				}
				if (t != 0) {
					printf("reservation_list.txt 마지막줄은 엔터로 끝나야합니다. \n");
					return 0;
				}
				break;
			}
		}

		if (false) { //문자가 없다면 전체 탐색 종료, 이것은 파일의 끝을 의미.
		}
		else {// 문자가있다.
			char* student;
			char* contents;
			char tmp[200];
			char* tmp2[6];
			
			strcpy(tmp, str);
			char* ptr2 = strchr(str, ' ');     // 'a'로 시작하는 문자열 검색, 포인터 반환
			int ct2 = 0;
			while (ptr2 != NULL)              // 검색된 문자열이 없을 때까지 반복
			{
				ct2++;
				ptr2 = strchr(ptr2 + 1, ' ');  // 포인터에 1을 더하여 a 다음부터 검색
			}
			if (ct2 != 1) {
				printf("reservation_list.txt %d줄 공백의 오류가 발생했습니다.\n", a + 1);
				return 0;
			}
			student = strtok(tmp, " ");
			if (student == NULL) {
				printf("reservation_list.txt %d줄 공백의 오류가 발생했습니다.\n", a + 1);
				return 0;
			}
			contents = strtok(NULL, " ");
			if (contents == NULL) {
				printf("reservation_list.txt %d줄 공백의 오류가 발생했습니다.\n", a + 1);
				return 0;
			}
			if (strtok(NULL, " ") != NULL) {
				//공백은 두개 이상이 될 수 없음.
				printf("reservation_list.txt %d줄 공백의 오류가 발생했습니다.\n", a + 1);
				return 0;
			}

			if (!check_student_id(student)) { //학번이 문법 규칙에 맞지 않을때.
				printf("reservation_list.txt %d줄 학번의 오류가 발생했습니다.\n",a+1);
				return 0;
			}
			char* ptr = strchr(contents, ',');     // 'a'로 시작하는 문자열 검색, 포인터 반환
			int ct = 0;
			while (ptr != NULL)              // 검색된 문자열이 없을 때까지 반복
			{
				ct++;
				ptr = strchr(ptr + 1, ',');  // 포인터에 1을 더하여 a 다음부터 검색
			}

			if (ct != 5) {
				printf("reservation_list.txt %d줄 컴마의 오류가 발생했습니다.\n", a + 1);
				return 0;
			}
			tmp2[0] = strtok(contents, ",");
			if (tmp2[0] == NULL) { //컴마없음
				printf("reservation_list.txt %d줄 컴마의 오류가 발생했습니다.\n", a + 1);
				return 0;
			}

			for (int i = 1; i < 6; i++) {
				tmp2[i] = strtok(NULL, ",");
				if (tmp2[i] == NULL) { //콤마가 부족하면
					printf("reservation_list.txt %d줄 컴마의 오류가 발생했습니다.\n", a + 1);
					return 0;
				}
			}
			if (strtok(NULL, ",") != NULL) { //콤마가 넘게있으면
				printf("reservation_list.txt %d줄 컴마의 오류가 발생했습니다.\n", a + 1);
				return 0;
			}

			if (!strcmp(tmp2[0], "공학관") || !strcmp(tmp2[0], "생명과학관") || !strcmp(tmp2[0], "상허연구관") || !strcmp(tmp2[0], "상허기념도서관") || !strcmp(tmp2[0], "동물생명과학관")) {

			}
			else {
				printf("reservation_list.txt %d줄 건물명의 오류가 발생했습니다.\n", a + 1);
				return 0;
			}

			if (check_GRAMMAR_DATE(tmp2[1]) && check_MEANING_DATE(tmp2[1])) {

			}
			else {
				printf("reservation_list.txt %d줄 날짜의 오류가 발생했습니다.\n", a + 1);
				return 0;
			}

			char time[100];
			strcpy(time, tmp2[2]);
			strcat(time, "~");
			strcat(time, tmp2[3]);

			if (check_GRAMMAR_ACCURATE_TIME(time) && check_MEANING_ACCURATE_TIME(time)) {

			}
			else {
				printf("reservation_list.txt %d줄 시각의 오류가 발생했습니다.\n", a + 1);
				return 0;
			}

			//호실체크
			if (check_GRAMMAR_ROOM_NUMBER(tmp2[5]) && check_hosil(tmp2[0],tmp2[5],0)) {

			}
			else {
				printf("reservation_list.txt %d줄 호실의 오류가 발생했습니다.\n", a + 1);
				return 0;
			}

			//인원체크
			if (check_GRAMMAR_PEOPLE_NUMBER(tmp2[4]) && check_max_people(tmp2[0],tmp2[5],tmp2[4])) {

			}
			else {
				printf("reservation_list.txt %d줄 인원의 오류가 발생했습니다.\n", a + 1);
				return 0;
			}
		}
	}

	if (check_overlap_list())
		return 0;

	return 1;
}

int check_file_date_time_list(FILE* fd) {

	char str[201];
	char str2[201];
	int count = 0;
	
	if (!check_two_file_line())
		return 0;

	while (fgets(str2, 200, fd) != NULL) {
		count++;
	}
	fseek(fd, 0, SEEK_SET);

	if (count == 0) //파일에 아무것도 입력 안되어있을때. 정상임.
		return 1;

	for (int a = 0; a < count; a++) {
		for (int t = 0; t < 200; t++) {
			if (t > 99) {
				printf("reservation_date_time_list.txt %d줄 100글자를 넘길 수 없습니다.\n", a + 1);
				return 0;
			}
			if ((str[t] = fgetc(fd)) != EOF) { //문자가 있을때.
				if (str[t] == '\n') { //엔터를 만나면 널문자로 바꿈.
					str[t] = '\0';
					break;
				}
			}
			else { //문자가 없다면 탈출
				if (t == 0) {
					return 1;
				}
				if (t != 0) {
					printf("reservation_date_time_list.txt 마지막줄은 엔터로 끝나야합니다. \n");
					return 0;
				}
				break;
			}
		}

		if (false) { //문자가 없다면 전체 탐색 종료, 이것은 파일의 끝을 의미.
		}
		else {// 문자가있다.
			char* building;
			char* hosil;
			char* date;
			char tmp[200];
			char* tmp2[6];

			//입력 받은 문자 복사.
			strcpy(tmp, str);
			char* ptr2 = strchr(str, ' ');   
			int ct2 = 0;
			while (ptr2 != NULL)              // 검색된 문자열이 없을 때까지 반복
			{
				ct2++;
				ptr2 = strchr(ptr2 + 1, ' ');  // 포인터에 1을 더하여 a 다음부터 검색
			}
			if (ct2 != 15) {
				printf("reservation_date_time_list.txt %d줄 공백의 오류가 발생했습니다.\n", a + 1);
				return 0;
			}
			building = strtok(tmp, " ");
			if (building == NULL) {
				printf("reservation_date_time_list.txt %d줄 공백의 오류가 발생했습니다.\n", a + 1);
				return 0;
			}
			hosil = strtok(NULL, " ");
			if (hosil == NULL) {
				printf("reservation_date_time_list.txt %d줄 공백의 오류가 발생했습니다.\n", a + 1);
				return 0;
			}
			date = strtok(NULL, " ");
			if (date == NULL) {
				printf("reservation_date_time_list.txt %d줄 공백의 오류가 발생했습니다.\n", a + 1);
				return 0;
			}
			char* ptr = strtok(NULL, "");
			if (!strcmp(building, "공학관") || !strcmp(building, "생명과학관") || !strcmp(building, "상허연구관") || !strcmp(building, "상허기념도서관") || !strcmp(building, "동물생명과학관")) {

			}
			else {
				printf("reservation_date_time_list.txt %d줄 건물명의 오류가 발생했습니다.\n", a + 1);
				return 0;
			}

			//호실체크
			if (check_GRAMMAR_ROOM_NUMBER(hosil) && check_hosil(building, hosil, 0)) {

			}
			else {
				printf("reservation_date_time_list.txt %d줄 호실의 오류가 발생했습니다.\n", a + 1);
				return 0;
			}


			if (check_GRAMMAR_DATE(date) && check_MEANING_DATE(date)) {

			}
			else {
				printf("reservation_date_time_list.txt %d줄 날짜의 오류가 발생했습니다.\n", a + 1);
				return 0;
			}

			ptr = strtok(ptr, " ");
			int ct = 0;
			while (ptr != NULL)              // 검색된 문자열이 없을 때까지 반복
			{
				if (!strcmp(ptr, "x") || !strcmp(ptr, "x\n") || !strcmp(ptr, "o") || !strcmp(ptr, "o\n")) {

				}
				else {
					printf("reservation_date_time_list.txt %d줄 시각 표시에 허용되지 않은 문자가 파일에 입력되었습니다.\n", a + 1);
					return 0;
				}
				ct++;
				ptr = strtok(NULL, " ");     // 포인터에 1을 더하여 a 다음부터 검색
			}
			if (ct != 13) {
				printf("reservation_date_time_list.txt %d줄 시각 표시문자가 허용되지 않은 갯수입니다.\n", a + 1);
				return 0;
			}
		}
	}
	if (check_overlap_time()) {
		return 0;
	}

	return 1;
}

int check_cancel_my_reservaton() {

	char str[1000];
	char* str2;
	int return_flag = 0;
	FILE* file_pointer;
	char* s_id_tmp;
	int count = 0;
	int max_count = 200;
	
	char* s_id = get_check_parameter().STUDENT_ID;
	char* date = get_check_parameter().DATE;
	char* building = get_check_parameter().BUILDING;
	char* hosil = get_check_parameter().ROOM_NUMBER;
	char* accurate_time = get_check_parameter().ACCURATE_TIME;

	file_pointer = fopen("reservation_list.txt", "r");

	if (file_pointer == NULL) {
		printf("reservation_list.txt 파일이 없거나 손상되었습니다.\n");
		return -1;
	}

	while (fgets(str, 1000, file_pointer) != NULL) {
		count++;
	}
	if (count == 0) //파일이 비어 있으므로 저장 내역이 없음.
		return 0;
	char** arr_str = (char**)malloc(sizeof(char*) * count);

	for (int i = 0; i < count; i++) {
		arr_str[i] = (char*)malloc(sizeof(char) * max_count);
	}

	fseek(file_pointer, 0, SEEK_SET);

	int j = 0;
	int k = 0;
	while (fgets(str, 1000, file_pointer) != NULL) {
		//printf("%s", str);

		strcpy(arr_str[j], str);
		j++;
	}

	for (int j = 0; j < count; j++) {
		s_id_tmp = strtok(arr_str[j], " ");
		str2 = strtok(NULL, " ");
		int ch = 0;
		char* tmp[10];

		if (!strcmp(s_id_tmp, s_id)) { //학번이 같으면.

			char* ptr = strtok(str2, ",");    
			while (ptr != NULL)              // 검색된 문자열이 없을 때까지 반복
			{
				tmp[ch] = ptr;
				ch++;
				ptr = strtok(NULL, ",");  // 포인터에 1을 더하여 a 다음부터 검색
			}

			// 0 건물명, 1 날짜, 2 시작시각, 3 끝 시각, 4 인원, 5 호실

			if (strcmp(tmp[0], building)) { //건물명 정보가 다르다면
				continue;
			}
			if (strcmp(tmp[1], date)) { // 날짜가 다르다면
				continue;
			}

			char time[100];
			strcpy(time, tmp[2]);
			strcat(time, "~");
			strcat(time, tmp[3]);

			if (strcmp(time, accurate_time)) {
				continue;
			}
			tmp[5] = strtok(tmp[5], "\n");
			if (strcmp(tmp[5], hosil)) {
				continue;
			}
			
			return 1;

		}
		else { //학번이 다르면
			continue;
		}
	}

	for (int i = 0; i < count; i++) {
		free(arr_str[i]);
	}
	free(arr_str);

	return 0;
}

int check_cancel_my_time() {

	char str[1000];
	char* str2;
	int return_flag = 0;
	FILE* file_pointer;
	int count = 0;
	int max_count = 200;

	char* tmp_building;
	char* tmp_date;
	char* tmp_hosil;

	char* date = get_check_parameter().DATE;
	char* building = get_check_parameter().BUILDING;
	char* hosil = get_check_parameter().ROOM_NUMBER;
	char* accurate_time = get_check_parameter().ACCURATE_TIME;


	file_pointer = fopen("reservation_date_time_list.txt", "r");

	if (file_pointer == NULL) {
		printf("reservation_date_time_list.txt 파일이 없거나 손상되었습니다.\n");
		return -1;
	}

	while (fgets(str, 1000, file_pointer) != NULL) {
		count++;
	}
	if (count == 0) //파일이 비어 있으므로 저장 내역이 없음.
		return 0;
	char** arr_str = (char**)malloc(sizeof(char*) * count);

	for (int i = 0; i < count; i++) {
		arr_str[i] = (char*)malloc(sizeof(char) * max_count);
	}

	fseek(file_pointer, 0, SEEK_SET);

	int j = 0;
	int k = 0;
	while (fgets(str, 1000, file_pointer) != NULL) {
		//printf("%s", str);

		strcpy(arr_str[j], str);
		j++;
	}

	for (int j = 0; j < count; j++) {

		char temp[10];
		char* temp_start;
		char* temp_end;
		char* list[20];

		int i = 0;
		list[i] = strtok(arr_str[j], " ");
		//	printf("%s", list[i]);
		for (i = 1; i < 16; i++) {
			list[i] = strtok(NULL, " ");
		}

			strcpy(temp, accurate_time);

			temp_start = strtok(temp, "~");
			temp_end = strtok(NULL, "~");



			if (!strcmp(list[0], building) && !strcmp(list[1], hosil) && !strcmp(list[2], date)) { // 건물명 호실 날짜가 같으면

				for (int j = 0; j < atoi(temp_end) - atoi(temp_start); j++) {
					if (!strcmp(list[atoi(temp_start) + j - 6], "x") || !strcmp(list[atoi(temp_start) + j - 6], "x\n")) {
						continue;
					}
					else //예약 정보가 없는거임
						for (int i = 0; i < count; i++) {
							free(arr_str[i]);
						}
					free(arr_str);
						return 0;
				}
				for (int i = 0; i < count; i++) {
					free(arr_str[i]);
				}
				free(arr_str);
				return 1;
			}
			else { //건물명 호실 날짜가 다르면
				continue;
			}
		}

		for (int i = 0; i < count; i++) {
			free(arr_str[i]);
		}
		free(arr_str);

		return 0;
	}

int cancel_list() { //지우기 성공 리턴1
	char str[1000];
	char* str2;
	int return_flag = 0;
	FILE* file_pointer;
	char* s_id_tmp;
	int count = 0;
	int max_count = 200;
	int edit_line = -1;

	char* s_id = get_check_parameter().STUDENT_ID;
	char* date = get_check_parameter().DATE;
	char* building = get_check_parameter().BUILDING;
	char* hosil = get_check_parameter().ROOM_NUMBER;
	char* accurate_time = get_check_parameter().ACCURATE_TIME;

	file_pointer = fopen("reservation_list.txt", "r");

	if (file_pointer == NULL) {
		printf("reservation_list.txt 파일이 없거나 손상되었습니다.\n");
		return 1;
	}

	while (fgets(str, 1000, file_pointer) != NULL) {
		count++;
	}
	if (count == 0) //파일이 비어 있으므로 저장 내역이 없음.
		return 1;
	char** arr_str = (char**)malloc(sizeof(char*) * count);

	for (int i = 0; i < count; i++) {
		arr_str[i] = (char*)malloc(sizeof(char) * max_count);
	}

	fseek(file_pointer, 0, SEEK_SET);

	int j = 0;
	while (fgets(str, 1000, file_pointer) != NULL) {
		//printf("%s", str);

		strcpy(arr_str[j], str);
		j++;
	}
	for (int j = 0; j < count; j++) {
		char cpy[1000];
		strcpy(cpy, arr_str[j]);
		s_id_tmp = strtok(cpy, " ");
		str2 = strtok(NULL, " ");
		int ch = 0;
		char* tmp[10];

		if (!strcmp(s_id_tmp, s_id)) { //학번이 같으면.

			char* ptr = strtok(str2, ",");
			while (ptr != NULL)              // 검색된 문자열이 없을 때까지 반복
			{
				tmp[ch] = ptr;
				ch++;
				ptr = strtok(NULL, ",");  // 포인터에 1을 더하여 a 다음부터 검색
			}

			// 0 건물명, 1 날짜, 2 시작시각, 3 끝 시각, 4 인원, 5 호실

			if (strcmp(tmp[0], building)) { //건물명 정보가 다르다면
				continue;
			}
			if (strcmp(tmp[1], date)) { // 날짜가 다르다면
				continue;
			}

			char time[100];
			strcpy(time, tmp[2]);
			strcat(time, "~");
			strcat(time, tmp[3]);

			if (strcmp(time, accurate_time)) {
				continue;
			}
			tmp[5] = strtok(tmp[5], "\n");
			if (strcmp(tmp[5], hosil)) {
				continue;
			}

			edit_line = j;
			break;

		}
		else { //학번이 다르면
			continue;
		}
	}

	fclose(file_pointer);
	file_pointer = fopen("reservation_list.txt", "w");

	if (file_pointer == NULL) {
		printf("reservation_list.txt 파일이 없거나 손상되었습니다.\n");
		return 0;
	}

	for (int i = 0; i < count; i++) {
		if (i != edit_line) {
			fputs(arr_str[i], file_pointer);
		}
		else { //수정라인은 쓰기 안함.
			continue;
		}
	}
	for (int i = 0; i < count; i++) {
		free(arr_str[i]);
	}
	free(arr_str);
	fclose(file_pointer);
	return 1;

}

int cancel_time() { //지우기 성공 리턴1
	char str[1000];
	char* str2;
	int return_flag = 0;
	FILE* file_pointer;
	char* s_id_tmp;
	int count = 0;
	int max_count = 200;
	int edit_line = -1;

	char* date = get_check_parameter().DATE;
	char* building = get_check_parameter().BUILDING;
	char* hosil = get_check_parameter().ROOM_NUMBER;
	char* accurate_time = get_check_parameter().ACCURATE_TIME;

	file_pointer = fopen("reservation_date_time_list.txt", "r");

	if (file_pointer == NULL) {
		printf("reservation_date_time_list.txt 파일이 없거나 손상되었습니다.\n");
		return 1;
	}

	while (fgets(str, 1000, file_pointer) != NULL) {
		count++;
	}
	if (count == 0) //파일이 비어 있으므로 저장 내역이 없음.
		return 1;
	char** arr_str = (char**)malloc(sizeof(char*) * count);

	for (int i = 0; i < count; i++) {
		arr_str[i] = (char*)malloc(sizeof(char) * max_count);
	}

	fseek(file_pointer, 0, SEEK_SET);

	int j = 0;
	while (fgets(str, 1000, file_pointer) != NULL) {
		//printf("%s", str);

		strcpy(arr_str[j], str);
		j++;
	}
	for (int j = 0; j < count; j++) {
		char cpy[1000];
		strcpy(cpy, arr_str[j]);
		char temp[10];
		char* temp_start;
		char* temp_end;
		char* list[20];

		int i = 0;
		list[i] = strtok(cpy, " ");
		//	printf("%s", list[i]);
		for (i = 1; i < 16; i++) {
			list[i] = strtok(NULL, " ");
		}

		strcpy(temp, accurate_time);

		temp_start = strtok(temp, "~");
		temp_end = strtok(NULL, "~");

		if (!strcmp(list[0], building) && !strcmp(list[1], hosil) && !strcmp(list[2], date)) { // 건물명 호실 날짜가 같으면

			for (int j = 0; j < atoi(temp_end) - atoi(temp_start); j++) {
				if (!strcmp(list[atoi(temp_start) + j - 6], "x")) {
					strcpy(list[atoi(temp_start) + j - 6], "o");
				}
				else if (!strcmp(list[atoi(temp_start) + j - 6], "x\n")) {
					strcpy(list[atoi(temp_start) + j - 6], "o\n");
				}
				
			}

			char haha[1000] = "";
			strcat(haha, building);
			strcat(haha, " ");
			strcat(haha, hosil);
			strcat(haha, " ");
			strcat(haha, date);
			strcat(haha, " ");
			for (int j = 0; j < 13; j++) {
				if (j == 12) {
					strcat(haha, list[j + 3]);
				}
				else {
					strcat(haha, list[j + 3]);
					strcat(haha, " ");
				}

			}
			strcpy(arr_str[j], haha);
		}
		else { //건물명 호실 날짜가 다르면
			continue;
		}
	}

	fclose(file_pointer);
	file_pointer = fopen("reservation_date_time_list.txt", "w");

	if (file_pointer == NULL) {
		printf("reservation_date_time_list 파일이 없거나 손상되었습니다.\n");
		return 0;
	}

	for (int i = 0; i < count; i++) {
		fputs(arr_str[i], file_pointer);
	}
	for (int i = 0; i < count; i++) {
		free(arr_str[i]);
	}
	free(arr_str);
	fclose(file_pointer);
	return 1;
}

int check_overlap_list() { //중복 되어있으면 1, 0이면 정상
	char str[1000];
	char* str2;
	int return_flag = 0;
	FILE* file_pointer;
	char* s_id_tmp;
	int count = 0;
	int max_count = 200;
	int edit_line = -1;

	file_pointer = fopen("reservation_list.txt", "r");

	if (file_pointer == NULL) {
		printf("reservation_list.txt 파일이 없거나 손상되었습니다.\n");
		return 1;
	}

	while (fgets(str, 1000, file_pointer) != NULL) {
		count++;
	}
	if (count == 0) //파일이 비어 있으므로 저장 내역이 없음.
		return 1;
	char** arr_str = (char**)malloc(sizeof(char*) * count);

	for (int i = 0; i < count; i++) {
		arr_str[i] = (char*)malloc(sizeof(char) * max_count);
	}

	fseek(file_pointer, 0, SEEK_SET);

	int j = 0;
	while (fgets(str, 1000, file_pointer) != NULL) {
		//printf("%s", str);

		strcpy(arr_str[j], str);
		j++;
	}

	char sort_tmp[1000];
	//오름차순 정렬
	for (int i = 0; i < count - 1; i++)
	{
		for (int j = 0; j < count - 1 - i; j++)
		{//s1 s2
			//s1이크면 1
			if (strcmp(arr_str[j], arr_str[j + 1]) == 0) {
				printf("reservation_list.txt 중복된 예약 정보가 있습니다.\n");
				for (int i = 0; i < count; i++) {
					fputs(arr_str[i], file_pointer);
				}
				fclose(file_pointer);
				return 1;
			}
			if (strcmp(arr_str[j],arr_str[j + 1]) == 1)
			{
				strcpy(sort_tmp,arr_str[j]);
				strcpy(arr_str[j],arr_str[j + 1]);
				strcpy(arr_str[j + 1],sort_tmp);
			}
		}
	}
	for (int i = 0; i < count; i++) {
		free(arr_str[i]);
	}
	free(arr_str);
	fclose(file_pointer);
	return 0;
}

int check_overlap_time() {
	char str[1000];
	char* str2;
	int return_flag = 0;
	FILE* file_pointer;
	char* s_id_tmp;
	int count = 0;
	int max_count = 200;
	int edit_line = -1;

	file_pointer = fopen("reservation_date_time_list.txt", "r");

	if (file_pointer == NULL) {
		printf("reservation_date_time_list.txt 파일이 없거나 손상되었습니다.\n");
		return 1;
	}

	while (fgets(str, 1000, file_pointer) != NULL) {
		count++;
	}
	if (count == 0) //파일이 비어 있으므로 저장 내역이 없음.
		return 1;
	char** arr_str = (char**)malloc(sizeof(char*) * count);

	for (int i = 0; i < count; i++) {
		arr_str[i] = (char*)malloc(sizeof(char) * max_count);
	}

	fseek(file_pointer, 0, SEEK_SET);

	int j = 0;
	while (fgets(str, 1000, file_pointer) != NULL) {
		//printf("%s", str);

		strcpy(arr_str[j], str);
		j++;
	}

	char sort_tmp[1000];
	//오름차순 정렬
	for (int i = 0; i < count - 1; i++)
	{
		for (int j = 0; j < count - 1 - i; j++)
		{//s1 s2
			//s1이크면 1
			if (strcmp(arr_str[j], arr_str[j + 1]) == 0) {
				printf("reservation_date_time_list.txt 중복된 예약 정보가 있습니다.\n");
				for (int i = 0; i < count; i++) {
					fputs(arr_str[i], file_pointer);
				}
				fclose(file_pointer);
				return 1;
			}
			if (strcmp(arr_str[j], arr_str[j + 1]) == 1)
			{
				strcpy(sort_tmp, arr_str[j]);
				strcpy(arr_str[j], arr_str[j + 1]);
				strcpy(arr_str[j + 1], sort_tmp);
			}
		}
	}
	for (int i = 0; i < count; i++) {
		free(arr_str[i]);
	}
	free(arr_str);
	fclose(file_pointer);

	if (!check_time_line_overlap()) //중복이면
		return 1;
	return 0;
}

int check_two_file_line(){ //리턴1은 정상, 리턴0은 오류

	char str_list[1000];
	char str_time[1000];
	int count_list = 0;
	int count_time = 0;
	int max_count = 1000;

	//reservation_list.txt 파일 먼저
	FILE* file_pointer = fopen("reservation_list.txt", "r");

	while (fgets(str_list, 1000, file_pointer) != NULL) {
		count_list++;
	}
	
	char** arr_list = (char**)malloc(sizeof(char*) * count_list);

	for (int i = 0; i < count_list; i++) {
		arr_list[i] = (char*)malloc(sizeof(char) * max_count);
	}

	fseek(file_pointer, 0, SEEK_SET);

	int j = 0;
	while (fgets(str_list, 1000, file_pointer) != NULL) {
		//printf("%s", str);
		strcpy(arr_list[j], str_list);
		j++;
	}


	//reservation_date_time_list.txt 파일 부분
	FILE* file_pointer2 = fopen("reservation_date_time_list.txt", "r");

	while (fgets(str_time, 1000, file_pointer2) != NULL) {
		count_time++;
	}
	if (count_list == 0 && count_time == 0) { //파일이 비어 있으므로 저장 내역이 없음.
		fclose(file_pointer2);
		for (int i = 0; i < count_list; i++) {
			free(arr_list[i]);
		}
		free(arr_list);
		return 1;
	}
	else if (count_time != count_list) {
		printf("reservation_date_time_list.txt 파일이 없거나 손상되었습니다.\n");
		fclose(file_pointer2);
		for (int i = 0; i < count_list; i++) {
			free(arr_list[i]);
		}
		free(arr_list);
		return 0;
	}
	char** arr_time = (char**)malloc(sizeof(char*) * count_time);

	for (int i = 0; i < count_time; i++) {
		arr_time[i] = (char*)malloc(sizeof(char) * max_count);
	}

	fseek(file_pointer2, 0, SEEK_SET);

	int a = 0;
	while (fgets(str_time, 1000, file_pointer2) != NULL) {
		//printf("%s", str);
		strcpy(arr_time[a], str_time);
		a++;
	}

	for (int j = 0; j < count_list; j++) {
		char* tmp_list = arr_list[j];
		char* tmp_time = arr_time[j];

		char* tmp_list_building;
		char* tmp_list_date;
		char tmp_list_time[10];
		char* tmp_list_hosil;

		char* tmp_arr_time[20];

		//리스트
		//학번 0건물명, 1날짜, 2시작시각, 3끝시각, 4인원, 5호실
		strtok(tmp_list, " ");
		tmp_list_building = strtok(NULL, ",");
		tmp_list_date = strtok(NULL, ",");
		char* start_time = strtok(NULL, ",");
		char* end_time = strtok(NULL, ",");
		char start_t[10];
		char end_t[10];
		/*strcpy(start_t, start_time);
		strcpy(end_t, end_time);
		strcat(start_time, "~");
		strcat(start_time, end_time);
		strcpy(tmp_list_timm, start_time);*/
		strtok(NULL, ","); //인원
		tmp_list_hosil = strtok(NULL, "\n");

		//시간
		//0건물명, 1호실, 2날짜
		int i = 0;
		tmp_arr_time[i] = strtok(tmp_time, " ");
		//	printf("%s", list[i]);
		for (i = 1; i < 16; i++) {
			tmp_arr_time[i] = strtok(NULL, " ");
		}
		if (!strcmp(tmp_list_building, tmp_arr_time[0]) && !strcmp(tmp_list_hosil, tmp_arr_time[1]) && !strcmp(tmp_list_date, tmp_arr_time[2])) {
			//건물명 호실 날짜가 일치함
			for (int k = 3; k < 16; k++) {
				if (k >= (atoi(start_time)-6) && k< (atoi(end_time)-6)) { //우리의 지정 범위일때
					if (!strcmp(tmp_arr_time[k], "x") || !strcmp(tmp_arr_time[k], "x\n")) {
						//잘되는거임
					}
					else {
						//오류임
						for (int i = 0; i < count_list; i++) {
							free(arr_list[i]);
						}
						free(arr_list);
						for (int i = 0; i < count_time; i++) {
							free(arr_time[i]);
						}
						free(arr_time);
						printf("reservation_date_time_list.txt 파일이 없거나 손상되었습니다.\n");
						return 0;
					}
				}
				else { //시간 지정 범위가 아닐때
					if (!strcmp(tmp_arr_time[k], "o") || !strcmp(tmp_arr_time[k], "o\n")) {
						//잘되는거임
					}
					else {
						//오류임
						for (int i = 0; i < count_list; i++) {
							free(arr_list[i]);
						}
						free(arr_list);
						for (int i = 0; i < count_time; i++) {
							free(arr_time[i]);
						}
						free(arr_time);
						printf("reservation_date_time_list.txt 파일이 없거나 손상되었습니다.\n");
						return 0;
					}
				}

			}
		}
		else { //일치하지 않음.
			printf("reservation_date_time_list.txt 파일이 없거나 손상 되었습니다.\n");
			for (int i = 0; i < count_list; i++) {
				free(arr_list[i]);
			}
			free(arr_list);
			for (int i = 0; i < count_time; i++) {
				free(arr_time[i]);
			}
			free(arr_time);
			return 0;
		}
	}

	for (int i = 0; i < count_list; i++) {
		free(arr_list[i]);
	}
	free(arr_list);
	for (int i = 0; i < count_time; i++) {
		free(arr_time[i]);
	}
	free(arr_time);
	return 1;
}

int check_time_line_overlap() { //1이면 정상 0이면 오류

	char str[1000];
	char* str2;
	int return_flag = 0;
	FILE* file_pointer;
	int count = 0;
	int max_count = 200;
	char* list[1000][20];

	file_pointer = fopen("reservation_date_time_list.txt", "r");

	if (file_pointer == NULL) {
		printf("reservation_date_time_list.txt 파일이 없거나 손상되었습니다.\n");
		return -1;
	}

	while (fgets(str, 1000, file_pointer) != NULL) {
		count++;
	}
	if (count == 0) //파일이 비어 있으므로 저장 내역이 없음.
		return 0;
	char** arr_str = (char**)malloc(sizeof(char*) * count);

	for (int i = 0; i < count; i++) {
		arr_str[i] = (char*)malloc(sizeof(char) * max_count);
	}

	fseek(file_pointer, 0, SEEK_SET);

	int j = 0;
	int k = 0;
	while (fgets(str, 1000, file_pointer) != NULL) {
		//printf("%s", str);

		strcpy(arr_str[j], str);
		j++;
	}

	for (int j = 0; j < count; j++) {

		char temp[10];
		char* temp_start;
		char* temp_end;

		int i = 0;
		list[j][i] = strtok(arr_str[j], " ");
		//	printf("%s", list[i]);
		for (i = 1; i < 16; i++) {
			list[j][i] = strtok(NULL, " ");
		}

	}

	for (int j = 0; j < count; j++) {// 나 j
		for (int k = 0; k < count; k++) { //비교 대상 k
			if (j == k)
				continue;
			if (!strcmp(list[j][0], list[k][0]) && !strcmp(list[j][1], list[k][1]) && !strcmp(list[j][2], list[k][2])) {
				for (int k2 = 3; k2 < 16; k2++) { // 비교중인 두 라인의 인덱스 k2
					if (!strcmp(list[j][k2], "o") || !strcmp(list[j][k2], "o\n")) {
						if (!strcmp(list[k][k2], "o") || !strcmp(list[k][k2], "o\n")) {
							//라인 시간 중복 오류임
							for (int i = 0; i < count; i++) {
								free(arr_str[i]);
							}
							free(arr_str);
							printf("reservation_date_time_list.txt 중복된 예약 정보가 있습니다.\n");
							return 0;
						}
					}
				}
			}
		}
	}

	for (int i = 0; i < count; i++) {
		free(arr_str[i]);
	}
	free(arr_str);

	return 1;
}