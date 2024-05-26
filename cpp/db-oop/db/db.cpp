#include <fstream>

#include "db.hpp"
#include "../constants.hpp"
#include "../utils/utils.hpp"

string DB::get_database()
{
  // getting the db
  ifstream input(db_name);

  string all_tables = "";
  string current_line;

  while (getline(input, current_line) && current_line != database_terminator)
  {
    all_tables += current_line;
    all_tables += '\n';
  }

  input.close();

  // if schema doesn't exist create the schema
  // and write it to the db
  int does_schemas_exists = str_include_start(all_tables, terminator);

  if (does_schemas_exists == -1)
  {
    // there is no db file, first populate the db file with
    // appropriate data and and return that data
    // first reset the value
    all_tables = "users\nname,password,phone_number,balance\n" + terminator + "\ntransactions\nfrom,to,amount\n" + terminator + "\nloans\ntaker,amount,last_date,status\n" + terminator + '\n' + database_terminator;

    ofstream output(db_name);
    output << all_tables;
    output.close();
  }

  return all_tables;
}

void DB::save_database(string new_database)
{
  ofstream output(db_name);
  output << new_database;
  output.close();
}
