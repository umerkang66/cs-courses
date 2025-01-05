#include <iostream>
#include "trie.cpp"
using namespace std;

bool count_unique_substrings(Trie &trie, string prefix)
{
  Node *temp = trie.get_root();

  for (int i = 0; i < prefix.size(); i++)
  {
    if (temp->children.count(prefix[i]) == 0)
      return false;
    temp = temp->children[prefix[i]];
  }

  return true;
}

int main()
{
  string str = "ababa";
  Trie trie;
  trie.insert(str);

  count_unique_substrings(trie, str);
  return 0;
}
