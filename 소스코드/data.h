#include <string.h>
#ifndef data_h
#define data_h
#include <locale.h>

/*
���� �ð� - CURRENT_ACCURATE_TIME
�ð� - ACCURATE_TIME
�ð� - DURING_TIME

time -> duringtime
during_time -> accurate_time
*/

struct check_reserve_parameter {
	char* BUILDING = NULL; //�ǹ��̸�
	char* ROOM_NUMBER = NULL; //�� ��ȣ
	char* DATE = NULL; //���� ��¥
	char* ACCURATE_TIME = NULL; //���� �ð�
	char* DURING_TIME = NULL; // ���� �ð�
	char* PEOPLE_NUMBER = NULL; //���� �ο�
	char* STUDENT_ID = NULL; //�й�
};

struct current_INFO {
	char* CURRENT_DATE = NULL;
	char* CURRENT_ACCURATE_TIME = NULL;
};

enum error_flag_type {
	NOERROR = 0,
	FALSE = 1,
	OVERSPACE = 2, //�ִ� �Է°��� ���鹮�� �ʰ�
	UNDERSPACE = 3, //�ּ� �Է°��� ���鹮�� �̴�
	INPUTERROR = 4, // �Է� ������ ����
	ERROR_GRAMMAR_BUILDING = 5,
	ERROR_GRAMMAR_ROOM_NUMBER = 6,
	ERROR_GRAMMAR_DATE = 7,
	ERROR_GRAMMAR_ACCURATE_TIME = 8, //�ð�
	ERROR_GRAMMAR_DURING_TIME = 9, //�ð�
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
	ERROR_NEED_INPUT = 20, //�ʼ� ���� ����.
	ERROR_DENY_INPUT = 21, //������ �ʴ� ����
	ERROR_OVERLAP_INPUT = 22, //�ߺ� ����
	ERROR_NO_TWO_TIME= 23, //�ð��� �ð��� ���ÿ� �Է�
	ERROR_FILE = 24, //���� ����
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

//���а�, ������а�, ���㿬����, �����䵵����, ����������а�
// �ǹ��� [] []
// ex �ǹ��� [0][3] => 3ȣ���� ������ 1 ������ 0
// ex �ǹ��� [1][3] => 3ȣ�ǿ� �ִ� ����� ������ ��ȯ.
static int building_gonghak[2][10] = {{0,1,1,1,1,1,1,1,1,0},{-1,10,10,6,6,6,6,6,6,-1}};
static int building_life[2][10] = { {0,1,1,1,1,1,1,1,0,0},{-1,6,6,6,7,6,4,8,-1,-1} };
static int building_sangheo[2][10] = { {0,1,1,1,1,1,1,1,1,0},{-1,6,6,6,6,6,6,6,6,-1} };
static int building_library[2][10] = { {0,1,1,1,1,1,1,0,0,0},{-1,8,8,6,6,6,6,-1,-1,-1} };
static int building_animal[2][10] = { {0,1,1,1,1,1,0,0,0,0},{-1,6,6,6,8,8,-1,-1,-1,-1} };

#endif