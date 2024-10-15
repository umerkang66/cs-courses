#include <iostream>
#include <stack>
using namespace std;

int *stock_span(int *stocks, int length)
{
  stack<int> s;
  int *results = new int[length];

  for (int i = 0; i < length; i++)
  {
    while (!s.empty() && stocks[s.top()] <= stocks[i])
      s.pop();

    if (s.empty())
      results[i] = i + 1;
    else
      results[i] = i - s.top();

    s.push(i);
  }

  return results;
}

int main()
{
  int stocks[] = {100, 80, 60, 70, 60, 85, 100};
  int n = sizeof(stocks) / sizeof(stocks[0]);
  int *results = stock_span(stocks, n);

  for (int i = 0; i < n; i++)
    cout << stocks[i] << " ";
  cout << endl;

  for (int i = 0; i < n; i++)
    cout << results[i] << " ";
  cout << endl;

  delete[] results;

  return 0;
}
