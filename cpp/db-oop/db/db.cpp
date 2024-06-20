#include "db.hpp"

string DB::get_db_name() const { return db_name; }

string DB::get_database()
{
  // getting the db
  ifstream input(ALL_DATABASES_FOLDER + '/' + db_name);

  string all_tables = "";
  string current_line;

  while (getline(input, current_line) && current_line != DATABASE_TERMINATOR)
  {
    all_tables += current_line;
    all_tables += '\n';
  }

  all_tables += DATABASE_TERMINATOR;

  input.close();

  // if schema doesn't exist create the schema
  // and write it to the db
  int does_schemas_exists = str_includes(all_tables, DATABASE_TERMINATOR);

  if (!does_schemas_exists)
  {
    // there is no db file, first populate the db file with
    // appropriate data and and return that data
    // first reset the value
    all_tables = DATABASE_TERMINATOR;

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

void DB::create_table(string header_rows, string name)
{
  string database = get_database();
  int table_starting_index = str_include_start(database, name);

  if (table_starting_index == -1)
  {
    // add this new table at the end
    int start_of_database_terminator = str_include_start(database, DATABASE_TERMINATOR);

    string new_database = "";
    for (int i = 0; i < start_of_database_terminator; i++)
    {
      // add everything from 0 index to start of removal content
      new_database += database[i];
    }
    header_rows = name + '\n' + "id," + header_rows;
    // now add the new rows
    for (int i = 0; header_rows[i] != '\0'; i++)
    {
      new_database += header_rows[i];
    }
    // after adding the rows, add the new line
    new_database += '\n';
    // after adding the rows also the table-terminator
    new_database += TERMINATOR;
    new_database += '\n';
    // now add the database after the end
    for (int i = start_of_database_terminator; database[i] != '\0'; i++)
    {
      new_database += database[i];
    }
    // database terminator already exists

    return save_database(new_database);
  }

  cout << "TABLE: " << name << " ALREADY EXISTS" << endl;
}

void DB::update_table(string rows, string name)
{
  string database = get_database();
  int table_starting_index = str_include_start(database, name);

  // find the starting index (already found)
  int start = table_starting_index;
  // find the ending index of table terminator (where is terminator '---' ends)
  int end = str_include_end(start, database, TERMINATOR);

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
  new_database += TERMINATOR;
  // now add the database after the end
  for (int i = end + 1; database[i] != '\0'; i++)
  {
    new_database += database[i];
  }

  // database terminator is already present

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

void DB::show_all_tables()
{
  vector<string> all_db_lines = split_into_vector(get_database(), '\n');
  vector<string> tables;
  tables.push_back(all_db_lines[0]);

  for (int i = 1; i < all_db_lines.size() - 1; i++)
  {
    if (all_db_lines[i] == TERMINATOR && all_db_lines[i + 1] != DATABASE_TERMINATOR)
    {
      tables.push_back(all_db_lines[i + 1]);
    }
  }

  for (int i = 0; i < tables.size(); i++)
  {
    cout << i + 1 << ": " << tables[i] << '\t';
  }

  cout << endl;
}
