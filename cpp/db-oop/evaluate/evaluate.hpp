#pragma once

#include <iostream>
#include <vector>
#include <filesystem>

#include "../utils/utils.hpp"
#include "../db/db.hpp"
#include "../table/table.hpp"
#include "../constants.hpp"

using namespace std;

class Evaluate
{
  vector<DB *> all_databases;

public:
  Evaluate()
  {
    // get all the databases from the file
    if (filesystem::exists(ALL_DATABASES_FOLDER) && filesystem::is_directory(ALL_DATABASES_FOLDER))
    {
      for (const auto &entry : filesystem::directory_iterator(ALL_DATABASES_FOLDER))
      {
        if (filesystem::is_regular_file(entry.status()))
        {
          const string file_name = entry.path().filename().string();
          all_databases.push_back(new DB(file_name));
        }
      }
    }
  }

  DB *current_db = NULL;

  // Function to evaluate an expression
  void evaluate(const string &expression);

  void handle_create_database(const string &name);

  void handle_show_databases();

  void handle_show_current_database();

  void handle_create_table(string name, string columns);

  void handle_create_row(string table_name, string row);

  void handle_delete_row(string table_name, string where);

  void handle_show_table(string name);

  void handle_show_table_with_where(string name, string key, string value);

  void handle_show_all_tables();

  void handle_show_table_as_JSON(string name, string populate);

  ~Evaluate()
  {
    for (int i = 0; i < all_databases.size(); i++)
    {
      delete all_databases[i];
    }
  }
};
