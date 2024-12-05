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
  heap.show();
  return 0;
}
