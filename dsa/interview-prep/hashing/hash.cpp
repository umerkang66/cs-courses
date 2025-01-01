#include <iostream>
#include <vector>
using namespace std;

struct Node
{
  string key;
  int value;
  Node *next = NULL;
  Node(string key, int value) : key(key), value(value) {}

  ~Node()
  {
    if (next)
      delete next;
  }
};

class HashTable
{
  int totalSize;
  int currSize;
  Node **table;

  int hashFunction(string key)
  {
    // JUST RANDOM HASH FUNCTION: we can implement our own logic
    // abc: (97^2 + 98^2 + 99^2) % totalSize;
    int total = 0;
    for (int i = 0; i < key.size(); i++)
      total += ((int)key[i] * (int)key[i]);
    return total % totalSize;
  }

  void rehash()
  {
    cout << "Rehash done" << endl;
    int new_total_size = totalSize * 2;

    Node **new_table = new Node *[new_total_size];
    for (int i = 0; i < new_total_size; i++)
      new_table[i] = NULL;

    // get all the previous elements in a vector in the form of key,value pair
    vector<pair<string, int>> prev_values;
    for (int i = 0; i < totalSize; i++)
    {
      if (table[i])
      {
        Node *temp = table[i];
        while (temp != NULL)
        {
          prev_values.push_back(make_pair(temp->key, temp->value));
          temp = temp->next;
        }
        delete table[i];
        table[i] = NULL;
      }
    }

    delete[] table;

    table = new_table;
    totalSize = new_total_size;
    currSize = 0;

    for (const pair<string, int> &pr : prev_values)
      insert(pr.first, pr.second);
  }

public:
  HashTable(int size = 50) : totalSize(size)
  {
    currSize = 0;
    table = new Node *[totalSize];
    for (int i = 0; i < totalSize; i++)
      table[i] = NULL;
  }

  void insert(string key, int value)
  {
    Node *new_node = new Node(key, value);
    int idx = hashFunction(key);

    new_node->next = table[idx];
    table[idx] = new_node;

    currSize++;

    int threshold = 1;
    if (currSize / (float)totalSize > threshold)
      rehash();
  }

  // BIG CATCH: In remove, we are not deleting the element int the memory, we are just changing the reference to the next element
  // if you want to change it, first remove destructor in node class, then you can do this
  void remove(string key)
  {
    int idx = hashFunction(key);
    if (!table[idx])
    {
      cout << "key: " << key << " not found" << endl;
      return;
    }

    Node *temp = table[idx];
    Node *prev = NULL;
    while (temp != NULL && temp->key != key)
    {
      prev = temp;
      temp = temp->next;
    }

    if (!temp)
    {
      cout << "key: " << key << " not found" << endl;
      return;
    }

    // if prev is null, mean it was the first element
    if (!prev && temp)
    {
      table[idx] = temp->next;
      currSize--;
      return;
    }

    prev->next = temp->next;
    currSize--;
  }

  // returns the value
  int search(string key)
  {
    int idx = hashFunction(key);

    if (!table[idx])
      return -1;

    Node *temp = table[idx];
    while (temp != NULL && temp->key != key)
      temp = temp->next;

    if (!temp)
      return -1;

    return temp->value;
  }

  vector<string> keys()
  {
    vector<string> ks;
    for (int i = 0; i < totalSize; i++)
    {
      Node *temp = table[i];
      while (temp)
      {
        ks.push_back(temp->key);
        temp = temp->next;
      }
    }
    return ks;
  }

  void print()
  {
    for (int i = 0; i < totalSize; i++)
    {
      cout << "idx" << i << " -> ";
      Node *temp = table[i];
      while (temp)
      {
        cout << "(" << temp->key << ',' << temp->value << ") -> ";
        temp = temp->next;
      }
      cout << endl;
    }
  }

  ~HashTable()
  {
    for (int i = 0; i < totalSize; i++)
    {
      if (table[i])
      {
        delete table[i];
        table[i] = NULL;
      }
    }
    delete[] table;
  }
};

int main()
{
  HashTable table(5);
  table.insert("english", 45);
  table.insert("maths", 25);
  table.insert("biology", 35);
  table.insert("physics", 50);
  table.insert("chemistry", 40);

  table.print();

  vector<string> keys = table.keys();
  for (const string &key : keys)
    table.remove(key);

  table.print();

  return 0;
}
