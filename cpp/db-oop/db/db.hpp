#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "../constants.hpp"
#include "../utils/utils.hpp"

using namespace std;

class DB
{
  string db_name;

public:
  DB(string db_name = "data.db") : db_name(db_name) {}

  // for getting all the database information
  string get_db_name() const;
  string get_database();
  void save_database(string new_database);

  // for getting specific tables
  string get_table(string name);
  void create_table(string header_rows, string name);
  void update_table(string rows, string name);
  void show_all_tables();
};
