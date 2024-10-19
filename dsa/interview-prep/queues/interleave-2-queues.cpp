#include <iostream>
#include <queue>
using namespace std;

void interleave(queue<int> &q)
{
  int original_size = q.size();
  queue<int> first_queue;

  for (int _ = 1; _ <= original_size / 2; _++)
  {
    first_queue.push(q.front());
    q.pop();
  }

  // here we have to queues, only check for the first queue emptiness, because if first queue is empty, second queue will also be empty
  while (!first_queue.empty())
  {
    q.push(first_queue.front());
    first_queue.pop();
    q.push(q.front());
    q.pop();
  }
}

int main()
{
  queue<int> q;
  for (int i = 1; i <= 10; i++)
    q.push(i);

  interleave(q);

  for (int _ = 1; _ <= 10; _++)
  {
    cout << q.front() << ' ';
    q.pop();
  }
  cout << endl;

  return 0;
}
