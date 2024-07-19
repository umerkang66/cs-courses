#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// closed hashing
// h(x) = x % 10
// h'(x) = (h(x) + f(i)) % 10
// where f(i) = i ---- i=0,1,2,3...
class QuadraticProbingHash
{
  int n = 10;
  int **hash = new int *[n];
  int size = 0;

  int get_hash(const int &x, int previous_i)
  {
    int h_x = x % 10;
    int h_p_x = (h_x + (int)pow(previous_i + 1, 2)) % 10;
    return h_p_x;
  }

public:
  QuadraticProbingHash()
  {
    for (int i = 0; i < n; i++)
      hash[i] = nullptr;
  }
  ~QuadraticProbingHash()
  {
    for (int i = 0; i < n; i++)
      delete hash[i];
    delete[] hash;
  }

  QuadraticProbingHash &insert(const vector<int> &nums)
  {
    for (const int &num : nums)
      insert(num);

    return *this;
  }

  QuadraticProbingHash &insert(const int &data)
  {
    if (size + 1 > n / 2)
    {
      n *= 2;
      int **new_hash = new int *[n];
      for (int i = 0; i < n / 2; i++)
      {
        new_hash[i] = hash[i];
      }
      hash = new_hash;
    }

    int i = -1;

    if (!hash[get_hash(data, i)])
      hash[get_hash(data, i)] = new int(data);
    else
    {
      i++;
      while (hash[get_hash(data, i)])
        i++;
      hash[get_hash(data, i)] = new int(data);
    }

    size++;
    return *this;
  }

  bool has(const int &data)
  {
    int i = -1;

    if (hash[get_hash(data, i)] && data == *hash[get_hash(data, i)])
      return true;
    else
    {
      i++;
      while (hash[get_hash(data, i)])
      {
        if (*hash[get_hash(data, i)] == data)
          return true;
        i++;
      }
    }

    return false;
  }

  friend ostream &
  operator<<(ostream &os, QuadraticProbingHash &qp_hash)
  {
    for (int i = 0; i < qp_hash.n; i++)
    {
      if (!qp_hash.hash[i])
        cout << '#' << ' ';
      else
        cout << *qp_hash.hash[i] << ' ';
    }
    return os;
  }
};

int main()
{
  QuadraticProbingHash qp_hash;
  qp_hash.insert(vector<int>{10, 15, 17, 9, 20});

  cout << qp_hash << endl;
  cout << endl;

  if (qp_hash.has(20))
    cout << "20 is Present" << endl;
  else
    cout << "20 is not Present" << endl;

  if (qp_hash.has(15))
    cout << "15 is Present" << endl;
  else
    cout << "15 is not Present" << endl;

  if (qp_hash.has(15))
    cout << "1000 is Present" << endl;
  else
    cout << "1000 is not Present" << endl;

  return 0;
}
