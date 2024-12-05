#include <iostream>
#include <queue>
using namespace std;

struct CustomCompare
{
  bool operator()(pair<string, int> &p1, pair<string, int> &p2)
  {
    return p1.second > p2.second;
  }
};

int main()
{
  // by default this will compare with the first element of pair
  // to compare with the second element of compare, we have to use the custom compare struct
  priority_queue<pair<string, int>, vector<pair<string, int>>, CustomCompare> pairs_queue;

  pairs_queue.push(make_pair("Umer", 88));
  pairs_queue.push(make_pair("Gulzar", 75));
  pairs_queue.push(make_pair("Ali", 92));

  while (!pairs_queue.empty())
  {
    cout << "Name: " << pairs_queue.top().first << ", Marks: " << pairs_queue.top().second << endl;
    pairs_queue.pop();
  }

  return 0;
}
