// https://leetcode.com/problems/powx-n

#include <iostream>
using namespace std;

double pow(double n, int x)
{
  long binary_form = x;
  double ans = 1;

  if (x < 0)
  {
    // handle for negative powers
    binary_form = -1 * binary_form;
    n = 1 / n;
  }

  while (binary_form > 0)
  {
    // if in the binary form if the last digit is 1, then multiply n by answer
    if (binary_form % 2 == 1)
    {
      ans *= n;
    }
    // by each binary iteration, square the initial number
    n *= n;
    binary_form /= 2;
  }

  return ans;
}

int main()
{
  cout << pow(3, 3) << endl;
  return 0;
}
