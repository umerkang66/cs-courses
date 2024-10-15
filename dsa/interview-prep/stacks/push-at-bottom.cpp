#include <iostream>
#include <stack>

using namespace std;

void push_at_bottom(stack<int> &s, int n)
{
  stack<int> new_stack;
  while (!s.empty())
  {
    new_stack.push(s.top());
    s.pop();
  }
  s.push(n);
  while (!new_stack.empty())
  {
    s.push(new_stack.top());
    new_stack.pop();
  }
}

int main()
{
  stack<int> s;
  s.push(1);
  s.push(2);
  s.push(3);

  push_at_bottom(s, 4);

  while (!s.empty())
  {
    cout << s.top() << ' '; // 3 2 1 4
    s.pop();
  }
  cout << endl;

  return 0;
}
