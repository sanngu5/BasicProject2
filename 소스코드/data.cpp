#include "data.h"
#include "filter.h"

void set_error_flag(int set_flag) {
	ERROR_FLAG = set_flag;
	show_error(ERROR_FLAG);
	ERROR_FLAG = NOERROR;
}
void real_set_error_flag(int set_flag) {
	ERROR_FLAG = set_flag;
}
void reset_reserve_parameter() {
	check_parameter.BUILDING = NULL;
	check_parameter.ROOM_NUMBER = NULL;
	check_parameter.DATE = NULL;
	check_parameter.ACCURATE_TIME = NULL;
	check_parameter.DURING_TIME = NULL;
	check_parameter.PEOPLE_NUMBER = NULL;
	check_parameter.STUDENT_ID = NULL;
}
int get_error_flag() {
	return ERROR_FLAG;
}
check_reserve_parameter get_check_parameter() {
	return check_parameter;
}

void set_check_parameter_building(char* str) {
	check_parameter.BUILDING = str;
}
void set_check_parameter_room_number(char* str) {
	check_parameter.ROOM_NUMBER = str;
}
void set_check_parameter_date(char* str) {
	check_parameter.DATE = str;
}
void set_check_parameter_during_time(char* str) {
	check_parameter.DURING_TIME = str;
}
void set_check_parameter_accurate_time(char* str) {
	check_parameter.ACCURATE_TIME = str;
}
void set_check_parameter_people_number(char* str) {
	check_parameter.PEOPLE_NUMBER = str;
}
void set_check_parameter_student_id(char* str) {
	check_parameter.STUDENT_ID = str;
}

int check_max_people(char* building, char* hosil, char* number) { 
	//건물명, 호실, 예약하고자 하는 인원을 입력하면
	//해당 호실이 존재하는지 체크하고 해당 인원으로 예약할 수 있는지 체크.
	char tmp_hosil[20];
	char tmp_number[20];
	strcpy(tmp_hosil, hosil);
	strcpy(tmp_number, number);

	char* room_number = strtok(tmp_hosil, "호실");
	char* people_number = strtok(tmp_number, "명");
	int people_number_int = atoi(people_number);
	int room_number_int = atoi(room_number);

	if (people_number_int < 2)
		return 0;
	if (!strcmp(building, "공학관")) {
		if (building_gonghak[0][room_number_int]) {
			if (building_gonghak[1][room_number_int] >= people_number_int)
				return 1;
			else
				return 0;
		}
		else
			return 0;
	}
	else if (!strcmp(building, "생명과학관")) {
		if (building_life[0][room_number_int]) {
			if (building_life[1][room_number_int] >= people_number_int)
				return 1;
			else
				return 0;
		}
		else
			return 0;
	}
	else if (!strcmp(building, "상허연구관")) {
		if (building_sangheo[0][room_number_int]) {
			if (building_sangheo[1][room_number_int] >= people_number_int)
				return 1;
			else
				return 0;
		}
		else
			return 0;
	}
	else if (!strcmp(building, "상허기념도서관")) {
		if (building_library[0][room_number_int]) {
			if (building_library[1][room_number_int] >= people_number_int)
				return 1;
			else
				return 0;
		}
		else
			return 0;
	}
	else if (!strcmp(building, "동물생명과학관")) {
		if (building_life[0][room_number_int]) {
			if (building_animal[1][room_number_int] >= people_number_int)
				return 1;
			else
				return 0;
		}
		else
			return 0;
	}
	else
		return 0;
}

int check_hosil(char* building, char* hosil,int number) {
	//건물명, 호실, 예약하고자 하는 인원을 입력하면
	//해당 호실이 존재하는지 체크하고 해당 인원으로 예약할 수 있는지 체크.

	char tmp[10];

	strcpy(tmp, hosil);
	char* room_number = strtok(tmp, "호실");
	int people_number_int = number;
	int room_number_int = atoi(room_number);

	if (!strcmp(building, "공학관")) {
		if (building_gonghak[0][room_number_int]) {
			if (building_gonghak[1][room_number_int] >= people_number_int)
				return 1;
			else
				return 0;
		}
		else
			return 0;
	}
	else if (!strcmp(building, "생명과학관")) {
		if (building_life[0][room_number_int]) {
			if (building_life[1][room_number_int] > people_number_int)
				return 1;
			else
				return 0;
		}
		else
			return 0;
	}
	else if (!strcmp(building, "상허연구관")) {
		if (building_sangheo[0][room_number_int]) {
			if (building_sangheo[1][room_number_int] > people_number_int)
				return 1;
			else
				return 0;
		}
		else
			return 0;
	}
	else if (!strcmp(building, "상허기념도서관")) {
		if (building_library[0][room_number_int]) {
			if (building_library[1][room_number_int] > people_number_int)
				return 1;
			else
				return 0;
		}
		else
			return 0;
	}
	else if (!strcmp(building, "동물생명과학관")) {
		if (building_life[0][room_number_int]) {
			if (building_animal[1][room_number_int] > people_number_int)
				return 1;
			else
				return 0;
		}
		else
			return 0;
	}
	else
		return 0;
}
