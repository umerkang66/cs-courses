#pragma once

#include <string>

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
};
