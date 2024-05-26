#include <iostream>
#include "utils/utils.hpp"
#include "evaluate/evaluate.hpp"

using namespace std;

int main()
{
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
      Evaluate::evaluate(input);
    }
    catch (const exception &e)
    {
      cerr << "Error: " << e.what() << endl;
    }
  }

  return 0;
}
