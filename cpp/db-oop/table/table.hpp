#pragma once

#include <string>
#include <vector>
#include <map>

#include "../db/db.hpp"
#include "../utils/utils.hpp"

using namespace std;

class Table
{
  string table_name;
  // to which database this table belongs to
  DB *database_ptr = nullptr;

public:
  Table(string table_name, DB *database_ptr) : table_name(table_name), database_ptr(database_ptr) {}

  void create_table(string columns);
  void add_row(string row);
  void delete_row(string where);
  void show_table(string key = "", string value = "");
  void show_table_as_json(vector<string> populate);
};
