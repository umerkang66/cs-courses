#include "evaluate.hpp"

void Evaluate::evaluate(const string &expression)
{
  string *tokens = split(expression, ' ');

  if (tokens[0] == "clear")
  {
    clear();
  }

  cout << endl;
}
