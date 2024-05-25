#include <iostream>
#include "utils/utils.hpp"

using namespace std;

// Function to evaluate an expression
void evaluate(const string &expression)
{
  string *tokens = split(expression, ' ');
  for (int i = 0; tokens[i][0] != '\0'; i++)
  {
    cout << tokens[i] << " ";
  }
  cout << endl;
}

int main()
{
  string input;
  cout << "Start to write your Queries." << endl;

  while (true)
  {
    cout << "> ";
    getline(cin, input);

    if (input == "exit")
    {
      break;
    }

    try
    {
      evaluate(input);
    }
    catch (const exception &e)
    {
      cerr << "Error: " << e.what() << endl;
    }
  }

  return 0;
}
