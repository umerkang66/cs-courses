#include <iostream>
#include <vector>
using namespace std;

struct Node
{
  string key;
  int value;
  Node *next = NULL;
  Node(string key, int value) : key(key), value(value) {}
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
    Node **new_table = new Node *[totalSize * 2];
    for (int i = 0; i < totalSize * 2; i++)
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
          Node *curr = temp;
          temp = temp->next;

          delete curr;
        }
        table[i] = NULL;
      }
    }

    delete[] table;
    table = new_table;
    totalSize *= 2;
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
      Node *next = temp->next;
      delete temp;
      table[idx] = next;
      currSize--;
      return;
    }

    Node *next = temp->next;
    delete temp;
    prev->next = next;
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

  ~HashTable()
  {
    for (int i = 0; i < totalSize; i++)
    {
      Node *temp = table[i];
      while (temp)
      {
        Node *next = temp->next;
        delete temp;
        temp = next;
      }
    }
    delete[] table;
  }
};

int main()
{
  HashTable table;
  table.insert("english", 45);
  table.insert("maths", 25);
  table.insert("biology", 35);
  table.insert("physics", 50);
  table.insert("chemistry", 40);

  for (const string &key : table.keys())
    cout << table.search(key) << ' ';
  cout << endl;

  return 0;
}
