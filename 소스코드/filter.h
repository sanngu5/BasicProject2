#include "data.h"
#include <stdio.h>
#include <stdlib.h>

//int check_case1(reserve_parameter a); //�� ����
int reservation_main(char* input_string); //ù��° ���͸�
int check_GRAMMAR_ROOM_NUMBER(char* str);
int check_GRAMMAR_DATE(char* str);
int check_GRAMMAR_ACCURATE_TIME(char* str);
int check_GRAMMAR_DURING_TIME(char* str);
int check_GRAMMAR_PEOPLE_NUMBER(char* str);

int check_CURRENT_TIME(char* str);					//�߰��߰�
int check_CURRENT_DATE(char* str);
int check_student_id(char* str);
int check_date_and_time(char* current_time, char* current_date);

int check_MEANING_ROOM_NUMBER(char* str);
int check_MEANING_DATE(char* str);
int check_MEANING_ACCURATE_TIME(char* str);
int check_MEANING_DURING_TIME(char* str);
int check_MEANING_PEOPLE_NUMBER(char* str);

void show_error(int error_flag);
int check_reservation_input_type(char* str);