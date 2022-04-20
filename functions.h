#pragma once
#pragma once

#include "main.h"

bool is_int(string);
bool is_grade(string);
bool check_name(string);
bool check_select(string);
bool check_select1(string);
bool compareByName(const data&, const data&);
bool compareBySurname(const data&, const data&);

void quick_sort(vector<int>& array, int first, int last);
void quick_sort(vector<data>& array, int first, int last);

double median(vector<int> arr);
double average(vector<int> arr);

void data_generation();
void generate(int, int);

void vector_data_input();
void vector_student_sorting();

void list_data_input();
void list_student_sorting();

void deque_data_input();
void deque_student_sorting();

void input_grades(vector<int>& grades);
void input_grades(list<int>& grades);
void input_grades(deque<int>& grades);

void input_data(vector<data>& arr);
void input_data(list<data>& arr);
void input_data(deque<data>& arr);

void print(const vector<data> arr, const int s);
void print(const list<data> arr, const int s);
void print(const deque<data> arr, const int s);

void split_two_new(vector<data> arr, double (*func)(vector<int>));
void split_one_new(vector<data> arr, double (*func)(vector<int>));
void split_two_new(list<data> arr, double (*func)(vector<int>));
void split_one_new(list<data> arr, double (*func)(vector<int>));
void split_two_new(deque<data> arr, double (*func)(vector<int>));
void split_one_new(deque<data> arr, double (*func)(vector<int>));

void read_data(vector<data>& arr, string filename);
void read_data(list<data>& arr, string filename);
void read_data(deque<data>& arr, string filename);

void write_students(const string, const vector<data>);
void write_students(const string, const list<data>);
void write_students(const string, const deque<data>);