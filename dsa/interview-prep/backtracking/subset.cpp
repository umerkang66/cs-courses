#include <iostream>
using namespace std;

void subsets(string str, string ans = "")
{
  if (str.length() == 0)
  {
    cout << ans << endl;
    return;
  }

  string removed_first = str.substr(1);
  subsets(removed_first, ans + str[0]);
  subsets(removed_first, ans);
}

int main()
{
  string str = "abc";
  subsets(str);
  return 0;
}
