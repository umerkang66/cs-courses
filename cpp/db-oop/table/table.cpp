#include "table.hpp"
#include "../constants.hpp"
#include "../utils/utils.hpp"

void Table::save_table(string rows, string name)
{
  string database = database_ptr->get_database();
  int table_starting_index = str_include_start(database, name);

  if (table_starting_index == -1)
  {
    return;
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
  // after adding the rows also the table-terminator
  // end + 1 is actually a '\n' character so we don't need to add it
  new_database += terminator;
  // now add the database after the end
  for (int i = end + 1; database[i] != '\0'; i++)
  {
    new_database += database[i];
  }

  // database terminator
  new_database += database_terminator;

  database_ptr->save_database(new_database);
}

string Table::get_table(string name)
{
  string all_tables = database_ptr->get_database();
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
