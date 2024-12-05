// imagine as complete binary tree, but create
// this data structure with the help of vectors

// these properties works for complete binary trees, for 0 based indexing
// left child = 2*i+1
// right child = 2*i+2
// parent = (i-1)/2

// for 1 based indexing
// left child = 2*i
// right child = 2*i+1
// parent = i/2

#include <iostream>
#include <vector>
using namespace std;

class Heap
{
  vector<int> vect;

public:
  // push the element at the end, then move it to the correct position
  Heap &push(int n)
  {
    vect.push_back(n);
    // (where last element is pushed-1) / 2
    int c_idx = vect.size() - 1;
    int p_idx = (c_idx - 1) / 2;

    while (p_idx >= 0 && vect[c_idx] > vect[p_idx])
    {
      // if heap condition is not satisfied, so update it
      swap(vect[p_idx], vect[c_idx]);

      // update the
      c_idx = p_idx;
      p_idx = (c_idx - 1) / 2;
    }

    return *this;
  }

  void pop()
  {
    // 1: swap root element with the last element
    swap(vect[0], vect[vect.size() - 1]);
    // 2: delete the last element
    vect.pop_back();
    // 3: Now update the position with respect to heap conditions from top to bottom
    heapify(0);
  }

  void heapify(int parent)
  {
    int l = parent * 2 + 1;
    int r = parent * 2 + 2;

    int max_idx = parent;

    if (l < vect.size() && vect[l] > vect[parent])
      max_idx = l;
    if (r < vect.size() && vect[r] > vect[parent])
      max_idx = r;

    swap(vect[max_idx], vect[parent]);

    // only heapify again, if the previous change had happened
    // now the updated element at the max_idx,
    // provide to the heapify as the new parent
    if (max_idx != parent)
      heapify(max_idx);
  }

  int top() { return vect[0]; }
  bool empty() { return vect.size() == 0; }

  void show()
  {
    for (const int &n : vect)
      cout << n << ' ';
    cout << endl;
  }
};

int main()
{
  Heap heap;
  heap.push(50).push(10).push(100).push(40);
  while (!heap.empty())
  {
    cout << heap.top() << ' ';
    heap.pop();
  }
  cout << endl;

  return 0;
}
