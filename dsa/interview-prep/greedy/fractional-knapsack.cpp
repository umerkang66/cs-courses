// https://www.naukri.com/code360/problems/fractional-knapsack_975286

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

double fractional_knapsack(const vector<int> &prices, const vector<int> &weights, int total_weight)
{
  int n = prices.size();
  vector<pair<pair<int, int>, double>> data(n);

  for (int i = 0; i < n; i++)
  {
    data[i] = make_pair(make_pair(prices[i], weights[i]), prices[i] / weights[i]);
  }

  // sort this data according to the max price1kg

  sort(data.begin(), data.end(),
       [](auto &a, auto &b)
       { return a.second > b.second; });

  double total_value = 0.0;

  for (int i = 0; i < n; i++)
  {
    if (total_weight == 0)
      break;

    if (data[i].first.second <= total_weight)
    {
      total_value += data[i].first.first;
      total_weight -= data[i].first.second;
    }
    else
    {
      // we can only add the small amount
      // price1kg * total_kg_remaining
      total_value += data[i].second * total_weight;
      total_weight = 0;
    }
  }

  return total_value;
}

int main()
{
  vector<int> prices = {60, 100, 120};
  vector<int> weights = {10, 20, 30};
  int total_weight = 50;

  cout << fractional_knapsack(prices, weights, total_weight) << endl;

  return 0;
}
