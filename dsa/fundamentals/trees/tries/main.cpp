#include <iostream>
#include <vector>

using namespace std;

class Trie
{
  struct Node
  {
    Node *children[26]; // there are 26 characters in english
    bool is_end = false;

    Node()
    {
      for (int i = 0; i < 26; i++)
        children[i] = nullptr;
    }
  };

  Node *root = new Node();

  void delete_nodes(Node *node)
  {
    for (int i = 0; i < 26; i++)
    {
      if (node->children[i] != nullptr)
      {
        delete_nodes(node->children[i]);
      }
    }

    delete node;
  }

public:
  Trie(vector<string> words)
  {
    for (const string &word : words)
      insert(word);
  }
  ~Trie() { delete_nodes(root); }

  void insert(string word)
  {
    Node *current = root;

    for (int i = 0; i < word.length(); i++)
    {
      int idx = word[i] - 'a';

      if (current->children[idx] == nullptr)
        current->children[idx] = new Node();
      if (i == word.length() - 1)
        current->children[idx]->is_end = true;

      current = current->children[idx];
    }
  }

  bool search(string key)
  {
    Node *current = root;

    for (int i = 0; i < key.length(); i++)
    {
      int idx = key[i] - 'a';
      if (current->children[idx] == nullptr)
        return false;
      if (i == key.length() - 1 && current->children[idx]->is_end == false)
        return false;

      current = current->children[idx];
    }

    return true;
  }
};

int main()
{
  Trie trie(vector<string>{"the", "a", "there", "their", "any"});

  if (trie.search("there"))
    cout << "there found" << endl;
  else
    cout << "there not found" << endl;

  if (trie.search("data"))
    cout << "data found" << endl;
  else
    cout << "data not found" << endl;

  return 0;
}
