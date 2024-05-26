#pragma once

#include <iostream>
#include "../utils/utils.hpp"

using namespace std;

class Evaluate
{
  static string current_db;

public:
  // Function to evaluate an expression
  static void evaluate(const string &expression);
};
