#ifndef CUSTOM_VECT_HPP
#define CUSTOM_VECT_HPP

#include <iostream>
#include <vector>

using namespace std;

template <class T>
class custom_vect : public vector<T>
{
public:
  friend ostream &operator<<(ostream &cout, custom_vect &v)
  {
    cout << '[';
    for (int i = 0; i < v.size(); i++)
    {
      cout << v[i];
      if (i < v.size() - 1)
        cout << ", ";
    }
    cout << ']';
    return cout;
  }
};

#endif
