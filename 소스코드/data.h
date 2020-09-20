#include <string.h>
#ifndef data_h
#define data_h
#include <locale.h>

/*
현재 시각 - CURRENT_ACCURATE_TIME
시각 - ACCURATE_TIME
시간 - DURING_TIME

time -> duringtime
during_time -> accurate_time
*/

struct check_reserve_parameter {
	char* BUILDING = NULL; //건물이름
	char* ROOM_NUMBER = NULL; //방 번호
	char* DATE = NULL; //예약 날짜
	char* ACCURATE_TIME = NULL; //예약 시각
	char* DURING_TIME = NULL; // 예약 시간
	char* PEOPLE_NUMBER = NULL; //예약 인원
	char* STUDENT_ID = NULL; //학번
};

struct current_INFO {
	char* CURRENT_DATE = NULL;
	char* CURRENT_ACCURATE_TIME = NULL;
};

enum error_flag_type {
	NOERROR = 0,
	FALSE = 1,
	OVERSPACE = 2, //최대 입력가능 공백문자 초과
	UNDERSPACE = 3, //최소 입력가능 공백문자 미달
	INPUTERROR = 4, // 입력 인자의 에러
	ERROR_GRAMMAR_BUILDING = 5,
	ERROR_GRAMMAR_ROOM_NUMBER = 6,
	ERROR_GRAMMAR_DATE = 7,
	ERROR_GRAMMAR_ACCURATE_TIME = 8, //시각
	ERROR_GRAMMAR_DURING_TIME = 9, //시간
	ERROR_GRAMMAR_PEOPLE_NUMBER = 10,
	ERROR_CURRENT_ACCURATE_TIME = 11,
	ERROR_CURRENT_DATE = 12,
	ERROR_MEANING_ROOM_NUMBER = 13,
	ERROR_MEANING_DATE = 14,
	ERROR_MEANING_ACCURATE_TIME = 15,
	ERROR_MEANING_DURING_TIME = 16,
	ERROR_MEANING_PEOPLE_NUMBER = 17,
	ERROR_RESERVATION_NO_PAST = 18,
	ERROR_RESERVATION_ALREADY = 19,
	ERROR_NEED_INPUT = 20, //필수 인자 없음.
	ERROR_DENY_INPUT = 21, //허용되지 않는 인자
	ERROR_OVERLAP_INPUT = 22, //중복 인자
	ERROR_NO_TWO_TIME= 23, //시간과 시각을 동시에 입력
	ERROR_FILE = 24, //파일 오류
	ERROR_GRAMMAR_STUDENT_ID = 25,


};

void set_error_flag(int set_flag);
int get_error_flag();
check_reserve_parameter get_check_parameter();
void set_check_parameter_building(char* str);
void set_check_parameter_room_number(char* str);
void set_check_parameter_date(char* str);
void set_check_parameter_during_time(char* str);
void set_check_parameter_accurate_time(char* str);
void set_check_parameter_people_number(char* str);
void set_check_parameter_student_id(char* str);
void reset_reserve_parameter();
void real_set_error_flag(int set_flag);
int check_hosil(char* building, char* hosil, int number);

int check_max_people(char* building, char* hosil, char* number);
int check_hosil(char* building, char* hosil, int number);

static check_reserve_parameter check_parameter;
static int ERROR_FLAG = 0;

//공학관, 생명과학관, 상허연구관, 상허기념도서관, 동물생명과학관
// 건물명 [] []
// ex 건물명 [0][3] => 3호실이 있으면 1 없으면 0
// ex 건물명 [1][3] => 3호실에 최대 몇명이 들어가는지 반환.
static int building_gonghak[2][10] = {{0,1,1,1,1,1,1,1,1,0},{-1,10,10,6,6,6,6,6,6,-1}};
static int building_life[2][10] = { {0,1,1,1,1,1,1,1,0,0},{-1,6,6,6,7,6,4,8,-1,-1} };
static int building_sangheo[2][10] = { {0,1,1,1,1,1,1,1,1,0},{-1,6,6,6,6,6,6,6,6,-1} };
static int building_library[2][10] = { {0,1,1,1,1,1,1,0,0,0},{-1,8,8,6,6,6,6,-1,-1,-1} };
static int building_animal[2][10] = { {0,1,1,1,1,1,0,0,0,0},{-1,6,6,6,8,8,-1,-1,-1,-1} };

#endif