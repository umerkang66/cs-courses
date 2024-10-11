#include <iostream>
#include <list>
using namespace std;

void print_list(list<int> l)
{
  list<int>::iterator itr;
  for (itr = l.begin(); itr != l.end(); itr++)
    cout << *itr << " -> ";
  cout << "NULL" << endl;
}

list<int> merge(list<int> l_1, list<int> l_2)
{
  list<int>::iterator pointer_1 = l_1.begin();
  list<int>::iterator pointer_2 = l_2.begin();
  list<int> merged;

  while (pointer_1 != l_1.end() && pointer_2 != l_2.end())
  {
    if (*pointer_1 < *pointer_2)
    {
      merged.push_back(*pointer_1);
      pointer_1++;
    }
    else
    {
      merged.push_back(*pointer_2);
      pointer_2++;
    }
  }

  while (pointer_1 != l_1.end())
  {
    merged.push_back(*pointer_1);
    pointer_1++;
  }

  while (pointer_2 != l_2.end())
  {
    merged.push_back(*pointer_2);
    pointer_2++;
  }

  return merged;
}

pair<list<int>, list<int>> mid(list<int> l)
{
  list<int>::iterator slow = l.begin();
  list<int>::iterator fast = l.begin();

  while (fast != l.end() && next(fast) != l.end())
  {
    advance(slow, 1);
    advance(fast, 2);
  }

  list<int> first_half(l.begin(), slow);
  list<int> second_half(slow, l.end());

  return make_pair(first_half, second_half);
}

list<int> sort(list<int> l)
{
  if (l.size() == 1)
    return l;

  pair<list<int>, list<int>> list_pair = mid(l);

  return merge(sort(list_pair.first), sort(list_pair.second));
}

int main()
{
  list<int> ll = {5, 1, 3, 2, 9, 11, 8};
  print_list(ll);
  ll = sort(ll);
  print_list(ll);

  return 0;
}
