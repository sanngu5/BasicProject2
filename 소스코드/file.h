#include "data.h"
#include <stdio.h>
#include <locale.h>
#include <stdlib.h> 
#include "filter.h"

int write_reservation();
int write_reservation_time();

int read_reservation_time_check();
int read_my_reservaton(char* s_id);

int read_inquery_date_acuurate_time();
int read_inquery_date_during_time();

int check_file_list(FILE* fd);
int check_file_date_time_list(FILE* fd);
int check_cancel_my_reservaton();
int check_cancel_my_time();

int cancel_list();
int cancel_time();

int check_overlap_list();
int check_overlap_time();

int check_two_file_line();
int check_time_line_overlap();