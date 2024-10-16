#include <iostream>
#include <stack>
using namespace std;

bool duplicate_parenthesis(string s)
{
  stack<char> checker;

  for (int i = 0; i < s.length(); i++)
  {
    if (s[i] == ')')
    {
      if (checker.top() == '(')
        return true;

      // remove everything between the bracket
      while (checker.top() != '(')
        checker.pop();
      checker.pop();
    }
    else
      checker.push(s[i]);
  }

  return false;
}

int main()
{
  string s1 = "(x+y)";     // 0
  string s2 = "((x+y)+z)"; // 0
  string s3 = "((x+y))";   // 1

  cout << duplicate_parenthesis(s1) << endl;
  cout << duplicate_parenthesis(s2) << endl;
  cout << duplicate_parenthesis(s3) << endl;

  return 0;
}
