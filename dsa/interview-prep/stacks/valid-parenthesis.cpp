#include <iostream>
#include <stack>
using namespace std;

bool valid_parenthesis(string s)
{
  stack<char> checker;

  for (int i = 0; i < s.length(); i++)
  {
    if (s[i] == '[' || s[i] == '{' || s[i] == '(')
      checker.push(s[i]);
    else
    {
      // insufficient opening brackets
      if (s.empty())
        return false;

      if (
          s[i] == ']' && checker.top() == '[' ||
          s[i] == '}' && checker.top() == '{' ||
          s[i] == ')' && checker.top() == '(')
        checker.pop();
      else
        return false;
    }
  }

  return s.empty();
}

int main()
{
  string s1 = "[([{()}])]"; // 1
  string s2 = "[";          // 0

  cout << valid_parenthesis(s1) << endl;
  cout << valid_parenthesis(s2) << endl;

  return 0;
}
