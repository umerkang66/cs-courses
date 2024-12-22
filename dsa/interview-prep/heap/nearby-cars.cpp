// https://leetcode.com/problems/k-closest-points-to-origin/

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct Car
{
  int x, y, dist;
  Car(int x, int y, int dist) : x(x), y(y), dist(dist) {}

  // here we provide, in heap if we have to swap or not
  // here we are telling if p1 value is bigger than p2, means swap, smaller elements should be at first
  // so this is making a min-heap
  bool operator<(const Car &obj) const { return this->dist > obj.dist; }
};

void nearby_cars(vector<pair<int, int>> &positions, int K)
{
  if (K > positions.size())
    return;

  // in outer pair, first is pair of their x,y axis, second is their distance from origin
  priority_queue<Car> pq;

  for (const pair<int, int> &position : positions)
  {
    int pythagoras_sqr = (position.first * position.first) + (position.second * position.second);

    Car car{position.first, position.second, pythagoras_sqr};

    pq.push(car);
  }

  int counter = 1;
  while (counter <= K)
  {
    cout << pq.top().x << ' ';
    cout << pq.top().y << ' ';
    cout << ": " << pq.top().dist;
    cout << endl;
    pq.pop();
    counter++;
  }
}

int main()
{
  vector<pair<int, int>> positions;
  positions.push_back(make_pair(3, 3));
  positions.push_back(make_pair(5, -1));
  positions.push_back(make_pair(-2, 4));

  int K = 2;

  nearby_cars(positions, K);

  return 0;
}
