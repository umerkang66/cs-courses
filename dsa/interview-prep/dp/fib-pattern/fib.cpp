#include <iostream>
#include <map>
#include <vector>
using namespace std;

int fibo_memo(int n, map<int, int> &m)
{
  if (n <= 1)
    return n;
  if (m[n])
    return m[n];
  m[n] = fibo_memo(n - 1, m) + fibo_memo(n - 2, m);
  return m[n];
}

int fibo_tab(int n)
{
  vector<int> v(n + 1, -1);
  v[0] = 0;
  v[1] = 1;

  for (int i = 2; i <= n; i++)
    v[i] = v[i - 1] + v[i - 2];

  return v[n];
}

int main()
{
  map<int, int> m;
  cout << fibo_memo(20, m) << endl;
  cout << fibo_tab(20) << endl;
  return 0;
}
