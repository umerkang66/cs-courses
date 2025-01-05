#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

// we don't need to store the
struct Node
{
  bool is_end = false;
  unordered_map<char, Node *> children;
};

class Trie
{
  Node *root = new Node();

  // for destructor
  void delete_nodes(Node *root)
  {
    for (const pair<char, Node *> &child_map : root->children)
      delete_nodes(child_map.second);
    delete root;
  }

public:
  void insert(string word)
  {
    Node *temp = root;
    for (int i = 0; i < word.size(); i++)
    {
      // didn't found the current character
      if (temp->children.find(word[i]) == temp->children.end())
        temp->children[word[i]] = new Node();
      temp = temp->children[word[i]];
    }
    temp->is_end = true;
  }

  bool search(string word)
  {
    Node *temp = root;
    for (int i = 0; i < word.size(); i++)
    {
      // mean character is not found
      if (temp->children.find(word[i]) == temp->children.end())
        return false;
      else
        temp = temp->children[word[i]];
    }

    return temp->is_end;
  }

  ~Trie() { delete_nodes(root); }
};

int main()
{
  vector<string> words = {"the", "a", "there", "their", "any", "thee"};
  Trie trie;
  for (const string &word : words)
    trie.insert(word);

  cout << trie.search("there") << endl;
  cout << trie.search("their") << endl;
  cout << trie.search("any") << endl;
  cout << trie.search("nodes") << endl;

  return 0;
}
