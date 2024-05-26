#include <fstream>
#include <iostream>

#include "db.hpp"
#include "../constants.hpp"
#include "../utils/utils.hpp"

string DB::get_db_name() const { return db_name; }

string DB::get_database()
{
  // getting the db
  ifstream input(ALL_DATABASES_FOLDER + '/' + db_name);

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
  int does_schemas_exists = str_include_start(all_tables, database_terminator);

  if (does_schemas_exists == -1)
  {
    // there is no db file, first populate the db file with
    // appropriate data and and return that data
    // first reset the value
    all_tables = database_terminator;

    ofstream output(ALL_DATABASES_FOLDER + '/' + db_name);
    output << all_tables;
    output.close();
  }

  return all_tables;
}

void DB::save_database(string new_database)
{
  ofstream output(ALL_DATABASES_FOLDER + '/' + db_name);
  output << new_database;
  output.close();
}

void DB::upsert_table(string rows, string name)
{
  string database = get_database();
  int table_starting_index = str_include_start(database, name);

  if (table_starting_index == -1)
  {
    // add this new table at the end
    int start_of_database_terminator = str_include_start(database, database_terminator);

    string new_database = "";
    for (int i = 0; i < start_of_database_terminator; i++)
    {
      // add everything from 0 index to start of removal content
      new_database += database[i];
    }
    // now add the new rows
    for (int i = 0; rows[i] != '\0'; i++)
    {
      new_database += rows[i];
    }
    // after adding the rows, add the new line
    new_database += '\n';
    // after adding the rows also the table-terminator
    new_database += terminator;
    // now add the database after the end
    for (int i = start_of_database_terminator; database[i] != '\0'; i++)
    {
      new_database += database[i];
    }

    // database terminator
    new_database += database_terminator;

    return save_database(new_database);
  }

  // find the starting index (already found)
  int start = table_starting_index;
  // find the ending index of table terminator (where is terminator '---' ends)
  int end = str_include_end(start, database, terminator);

  // for new database we wants to remove the database content from start to end
  // and add the new rows instead of this
  string new_database = "";
  for (int i = 0; i < start; i++)
  {
    // add everything from 0 index to start of removal content
    new_database += database[i];
  }
  // now add the new rows
  for (int i = 0; rows[i] != '\0'; i++)
  {
    new_database += rows[i];
  }
  new_database += '\n';
  // after adding the rows also the table-terminator
  new_database += terminator;
  // now add the database after the end
  for (int i = end + 1; database[i] != '\0'; i++)
  {
    new_database += database[i];
  }

  // database terminator
  new_database += database_terminator;

  save_database(new_database);
}

string DB::get_table(string name)
{
  string all_tables = get_database();
  int table_starting_index = str_include_start(all_tables, name);

  if (table_starting_index == -1)
  {
    return "not found";
  }

  string table = "";
  int i = table_starting_index;
  // check for terminator
  while (all_tables[i] != '\0')
  {
    table += all_tables[i];
    bool chars_of_terminator_found[3] = {0, 0, 0};
    for (int j = i + 1; j <= i + 3; j++)
    {
      if (all_tables[j] == '-')
      {
        chars_of_terminator_found[j - i - 1] = 1;
      }
    }
    bool is_found = true;
    for (int i = 0; i < 3; i++)
    {
      if (chars_of_terminator_found[i] == 0)
      {
        is_found = false;
      }
    }
    if (is_found)
    {
      break;
    }
    i++;
  }
  return table;
}
