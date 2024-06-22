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
    return clear();
  }

  if (to_lower(tokens[0]) == "use")
  {
    if (!str_includes(tokens[1], ".db"))
      tokens[1] += ".db";
    current_db = new DB(tokens[1]);
    cout << tokens[1] << ": is activated" << endl;
  }
  else
  {
    if (!(to_lower(tokens[0]) == "show" && to_lower(tokens[1]) == "databases") && !(to_lower(tokens[0]) == "create" && to_lower(tokens[1]) == "database") && !current_db)
    {
      cout << "No DB is activated, type 'USE <database_name>' to Select the database" << endl;
      return;
    }

    if (to_lower(tokens[0]) == "create")
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
      else if (str_includes(to_lower(tokens[1]), "row"))
      {
        if (splitted_arr_length(tokens) != 4)
        {
          throw invalid_argument("You haven't provided the name or columns");
        }
        const string table_name = tokens[2];
        const string row = tokens[3];
        handle_create_row(tokens[2], tokens[3]);
      }
    }
    else if (to_lower(tokens[0]) == "delete")
    {
      if (to_lower(tokens[1]) == "row")
      {
        if (splitted_arr_length(tokens) != 5)
        {
          throw invalid_argument("You haven't provided the name or columns");
        }
        const string table_name = tokens[2];
        if (to_lower(tokens[3]) == "where")
        {
          const string WHERE = tokens[4];
          handle_delete_row(table_name, WHERE);
        }
      }
    }
    else if (to_lower(tokens[0]) == "show")
    {
      if (str_includes(to_lower(tokens[1]), "all") && (str_includes(to_lower(tokens[2]), "table")))
      {
        handle_show_all_tables();
      }
      if (str_includes(to_lower(tokens[1]), "table"))
      {
        if (splitted_arr_length(tokens) == 5 && to_lower(tokens[3]) == "where")
        {
          vector<string> where_id_value = split_into_vector(tokens[4], '=');
          string key = where_id_value[0];
          string value = where_id_value[1];
          return handle_show_table_with_where(tokens[2], key, value);
        }
        if (splitted_arr_length(tokens) >= 5 && to_lower(tokens[4]) == "json")
        {
          string populate = "";
          if (splitted_arr_length(tokens) == 7)
            populate = tokens[6];
          return handle_show_table_as_JSON(tokens[2], populate);
        }
        else if (splitted_arr_length(tokens) < 3)
        {
          throw invalid_argument("You haven't provided the name of table");
        }
        handle_show_table(tokens[2]);
      }
      if (str_includes(to_lower(tokens[1]), "database"))
      {
        handle_show_databases();
      }
      else if (to_lower(tokens[1]) == "current" && str_includes(to_lower(tokens[2]), "database"))
      {
        handle_show_current_database();
      }
    }
    else
    {
      cout << "--INVALID ARGUMENT--" << endl;
    }
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

void Evaluate::handle_create_row(string table_name, string row)
{
  Table new_table(table_name, current_db);
  new_table.add_row(row);
}

void Evaluate::handle_delete_row(string table_name, string where)
{
  Table new_table(table_name, current_db);
  new_table.delete_row(where);
}

void Evaluate::handle_show_all_tables()
{
  current_db->show_all_tables();
}

void Evaluate::handle_show_table(string name)
{
  Table new_table(name, current_db);
  new_table.show_table();
}

void Evaluate::handle_show_table_with_where(string name, string key, string value)
{
  Table new_table(name, current_db);
  new_table.show_table(key, value);
}

void Evaluate::handle_show_table_as_JSON(string name, string populate)
{
  Table new_table(name, current_db);
  if (populate == "")
  {
    vector<string> empty;
    return new_table.show_table_as_json(empty);
  }
  new_table.show_table_as_json(split_into_vector(populate, '='));
}
