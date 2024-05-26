#pragma once

#include <iostream>
#include <vector>

#include "../utils/utils.hpp"
#include "../db/db.hpp"

using namespace std;

class Evaluate
{
  vector<DB *> all_databases;

public:
  DB *current_db = NULL;

  // Function to evaluate an expression
  void evaluate(const string &expression);

  void handle_create_database(const string &name);

  ~Evaluate()
  {
    for (int i = 0; i < all_databases.size(); i++)
    {
      delete all_databases[i];
    }
  }
};
