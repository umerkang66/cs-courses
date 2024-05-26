#include "filesystem"
#include "evaluate.hpp"
#include "../constants.hpp"

void Evaluate::evaluate(const string &expression)
{
  string *tokens = split(expression, ' ');
  if (tokens[0] == "clear")
  {
    clear();
  }
  else if (to_lower(tokens[0]) == "create")
  {
    if (to_lower(tokens[1]) == "database")
    {
      handle_create_database(tokens[2]);
    }
  }
}

void Evaluate::handle_create_database(const string &name)
{
  filesystem::create_directory(ALL_DATABASES_FOLDER);
  const string db_name = name + ".db";
  current_db = new DB(name + ".db");
  current_db->save_database("");
  all_databases.push_back(current_db);
  cout << "DB: " << db_name << " CREATED" << endl;
}
