#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int job_sequencing(vector<vector<int>> jobs)
{
  sort(jobs.begin(), jobs.end(), [](const vector<int> &a, const vector<int> &b)
       { return a[1] > b[1]; });

  int total_profit = jobs[0][1];
  int safe_deadline = jobs[0][0] + 1;

  for (int i = 1; i < jobs.size(); i++)
  {
    if (jobs[i][0] >= safe_deadline)
    {
      total_profit += jobs[i][1];
      safe_deadline = jobs[i][0] + 1;
    }
  }

  return total_profit;
}

int main()
{
  // first is deadline
  // second is profit
  vector<vector<int>> jobs = {
      {1, 10},
      {1, 30},
      {1, 40},
      {4, 20},
  };

  cout << job_sequencing(jobs) << endl;

  return 0;
}
