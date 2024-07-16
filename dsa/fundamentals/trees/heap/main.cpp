#include <iostream>
#include <vector>
#include "custom_vect.hpp"

using namespace std;

// MAX HEAP
class Heap
{
  custom_vect<int> data;

public:
  Heap() = default;
  Heap(const Heap &other) : data(other.data) {}

  Heap &insert(const vector<int> items)
  {
    for (const int &item : items)
    {
      insert(item);
    }
    return *this;
  }

  Heap &insert(int n)
  {
    data.push_back(n);

    int i = data.size() - 1;

    // temp is greater than its parent
    while (i >= 1 && data[i] > data[i / 2])
    {
      int temp = data[i];
      data[i] = data[i / 2];
      data[i / 2] = temp;
      i /= 2;
    }

    return *this;
  }

  bool is_empty() const { return data.size() == 0; }

  int remove()
  {
    int removed_item = data[0];
    data[0] = data.back();
    data.pop_back();

    int i = 0;

    while (true)
    {
      int left_child_idx = (2 * i) + 1;
      int right_child_idx = (2 * i) + 2;

      if (left_child_idx >= data.size())
      {
        // left child doesn't exist
        break;
      }

      int greater_child = left_child_idx;

      if (right_child_idx < data.size())
      {
        // right child also exists, now check which is the greater
        greater_child = data[left_child_idx] > data[right_child_idx] ? left_child_idx : right_child_idx;
      }

      if (data[i] < data[greater_child])
      {
        // swap them
        int temp = data[i];
        data[i] = data[greater_child];
        data[greater_child] = temp;

        i = greater_child;
      }
      else
      {
        break;
      }
    }

    return removed_item;
  }

  custom_vect<int> heap_sort()
  {
    custom_vect<int> sorted;
    Heap copied_heap = *this;

    while (!copied_heap.is_empty())
    {
      sorted.push_back(copied_heap.remove());
    }

    return sorted;
  }

  void clear() { data.clear(); }

  friend ostream &operator<<(ostream &cout, Heap &h)
  {
    cout << h.data;
    return cout;
  }
};

int main()
{
  Heap heap;
  heap.insert(vector<int>{35, 15, 30, 10, 12, 6, 5, 20, 40});

  cout << "Heap: " << heap << endl;
  while (!heap.is_empty())
  {
    cout << "R: " << heap.remove() << "   ";
    cout << heap << endl;
  }

  cout << endl;

  heap.clear();
  heap.insert(vector<int>{35, 15, 30, 10, 12, 6, 5, 20, 40});
  cout << "Unsorted: " << heap << endl;
  custom_vect<int> sorted = heap.heap_sort();
  cout << "Sorted: " << sorted << endl;
  cout << "Original Heap: " << heap << endl;

  return 0;
}
