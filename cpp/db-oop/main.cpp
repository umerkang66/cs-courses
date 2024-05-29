#include <iostream>
#include "evaluate/evaluate.hpp"

using namespace std;

int main()
{
  Evaluate evaluator;
  string input;
  cout << "Start to write your Queries. To exit, type (exit)" << endl;

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
      evaluator.evaluate(input);
    }
    catch (const exception &e)
    {
      cerr << "Error: " << e.what() << endl;
    }
  }

  return 0;
}
