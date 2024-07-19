#include <iostream>
#include <vector>

using namespace std;

// open hashing
class ChainingHash
{
  struct Node
  {
    int data;
    Node *next = nullptr;
    Node(const int &data) : data(data) {}

    friend ostream &operator<<(ostream &os, Node &list_node)
    {
      os << "[";
      Node *current_node = &list_node;
      while (current_node != NULL)
      {
        os << current_node->data;
        if (current_node->next != NULL)
        {
          os << " --> ";
        }
        current_node = current_node->next;
      }
      os << "]";
      return os;
    }
  };

  Node *hash[10]; // 0-9

  int get_hash(const int &data) { return data % 10; }

public:
  ChainingHash()
  {
    for (int i = 0; i < 10; i++)
      hash[i] = nullptr;
  }

  ChainingHash &insert(const vector<int> &nums)
  {
    for (const int &num : nums)
      insert(num);

    return *this;
  }

  ChainingHash &insert(const int &data)
  {
    if (!hash[get_hash(data)])
    {
      // there is a nullptr at this index of arr
      hash[get_hash(data)] = new Node(data);
    }
    else
    {
      Node *prev = nullptr;
      Node *temp = hash[get_hash(data)];

      while (temp != nullptr && data > temp->data)
      {
        prev = temp;
        temp = temp->next;
      }

      if (!prev)
      {
        // add at the start
        Node *new_node = new Node(data);
        new_node->next = hash[get_hash(data)];
        hash[get_hash(data)] = new_node;
      }
      else if (!temp)
      {
        // add at the end
        prev->next = new Node(data);
      }
      else
      {
        prev->next = new Node(data);
        prev->next->next = temp;
      }
    }

    return *this;
  }

  bool has(const int &data)
  {
    if (!hash[get_hash(data)])
    {
      return false;
    }
    else
    {
      // every linked list is sorted
      Node *temp = hash[get_hash(data)];
      while (temp != nullptr)
      {
        if (temp->data > data)
          return false;
        if (temp->data == data)
          return true;
        temp = temp->next;
      }
    }

    return false;
  }

  friend ostream &operator<<(ostream &os, ChainingHash &chaining_hash)
  {
    for (int i = 0; i < 10; i++)
    {
      cout << i << ": " << *chaining_hash.hash[i] << endl;
    }

    return os;
  }
};

int main()
{
  ChainingHash chaining_hash;
  chaining_hash.insert(vector<int>{10, 15, 17, 9, 20, 29, 55, 99, 49, 39});

  cout << chaining_hash << endl;

  if (chaining_hash.has(29))
    cout << "29 is Present" << endl;
  else
    cout << "29 is not Present" << endl;

  if (chaining_hash.has(3))
    cout << "30 is Present" << endl;
  else
    cout << "30 is not Present" << endl;

  if (chaining_hash.has(1000))
    cout << "1000 is Present" << endl;
  else
    cout << "1000 is not Present" << endl;

  return 0;
}
