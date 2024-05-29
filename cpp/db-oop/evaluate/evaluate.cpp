#include "evaluate.hpp"

int splitted_arr_length(string *str_arr)
{
  int length = 0;
  for (int i = 0; str_arr[i][0] != '\0'; i++)
  {
    length++;
  }
  return length;
}

void Evaluate::evaluate(const string &expression)
{
  string *tokens = split(expression, ' ');
  if (tokens[0] == "clear")
  {
    clear();
  }
  else if (to_lower(tokens[0]) == "create")
  {
    if (str_includes(to_lower(tokens[1]), "database"))
    {
      if (splitted_arr_length(tokens) != 3)
      {
        throw invalid_argument("You haven't provided the table name");
      }
      handle_create_database(tokens[2]);
    }
    else if (str_includes(to_lower(tokens[1]), "table"))
    {
      if (splitted_arr_length(tokens) != 4)
      {
        throw invalid_argument("You haven't provided the name or columns");
      }
      handle_create_table(tokens[2], tokens[3]);
    }
  }
  else if (to_lower(tokens[0]) == "show")
  {
    if (str_includes(to_lower(tokens[1]), "database"))
    {
      handle_show_databases();
    }
    else if (to_lower(tokens[1]) == "current" && str_includes(to_lower(tokens[2]), "database"))
    {
      handle_show_current_database();
    }
  }
  else if (to_lower(tokens[0]) == "use")
  {
    if (!str_includes(tokens[1], ".db"))
      tokens[1] += ".db";
    current_db = new DB(tokens[1]);
    cout << tokens[1] << ": is activated" << endl;
  }
  else
  {
    cout << "--INVALID ARGUMENT--" << endl;
  }
}

void Evaluate::handle_show_current_database()
{
  if (current_db == nullptr)
    cout << "No DB is activated, type 'USE <database_name>' to Select the database" << endl;
  else
    cout << current_db->get_db_name() << endl;
}

void Evaluate::handle_show_databases()
{
  // get all the databases from the 'databases' folder
  if (filesystem::exists(ALL_DATABASES_FOLDER) && filesystem::is_directory(ALL_DATABASES_FOLDER))
  {
    for (const auto &entry : filesystem::directory_iterator(ALL_DATABASES_FOLDER))
    {
      if (filesystem::is_regular_file(entry.status()))
      {
        cout << entry.path().filename().string() << " ";
      }
    }
    cout << endl;
  }
}

void Evaluate::handle_create_database(const string &name)
{
  filesystem::create_directory(ALL_DATABASES_FOLDER);
  const string db_name = !str_includes(name, ".db") ? name + ".db" : name;
  current_db = new DB(db_name);
  current_db->save_database("");
  all_databases.push_back(current_db);
  cout << "DB: " << db_name << " CREATED" << endl;
}

void Evaluate::handle_create_table(string name, string columns)
{
  Table new_table(name, current_db);
  new_table.create_table(columns);
}
