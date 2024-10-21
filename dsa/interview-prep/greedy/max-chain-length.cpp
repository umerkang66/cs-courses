// https://www.naukri.com/code360/problems/maximum-length-pair-chain_985258

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int max_chain_length(vector<pair<int, int>> &pairs)
{
  sort(pairs.begin(), pairs.end(), [](pair<int, int> &a, pair<int, int> &b)
       { return a.second < b.second; });

  // add the first item, because its end is the smallest one (sorted), so
  int chain = 1;
  int curr_end = pairs[0].second;

  for (int i = 1; i < pairs.size(); i++)
  {
    if (pairs[i].first > curr_end)
    {
      chain += 1;
      curr_end = pairs[i].second;
    }
  }

  return chain;
}

int main()
{
  vector<pair<int, int>> pairs;
  pairs.push_back({5, 24});
  pairs.push_back({39, 60});
  pairs.push_back({5, 28});
  pairs.push_back({27, 40});
  pairs.push_back({50, 90});

  cout << max_chain_length(pairs) << endl;

  return 0;
}
