#pragma once

#include <string>
using namespace std;

int str_include_start(string str, string check);

int str_include_end(int starting_index, string str, string check);

string *split(const string &str, char delimeter);

void clear();
