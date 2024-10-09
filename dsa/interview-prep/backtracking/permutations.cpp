#include <iostream>
using namespace std;

void permutations(string str, string ans = "")
{
  if (str.length() == 0)
  {
    cout << ans << endl;
    return;
  }

  for (int i = 0; i < str.length(); i++)
  {
    string removed = str.substr(0, i) + str.substr(i + 1);
    permutations(removed, ans + str[i]);
  }
}

int main()
{
  string str = "abc";
  permutations(str);
  return 0;
}
