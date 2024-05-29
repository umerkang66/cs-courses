#pragma once

#include <vector>
#include <iostream>

using namespace std;

int str_include_start(string str, string check);

int str_include_end(int starting_index, string str, string check);

string *split(const string &str, char delimeter);

void clear();

string to_lower(string str);

string to_upper(string str);

bool str_includes(const string &str, const string &substr);

string joins(vector<string> arr, string separator);

vector<string> split_into_vector(string str, char separator);

string generateRandomID(int length);

void show_as_table(string **matrix, int rows, int cols);

void show_as_table_vector(vector<vector<string>> matrix);

string split_long_line(string longLine, int maxLength);
