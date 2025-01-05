// https://leetcode.com/problems/longest-word-with-all-prefixes/

#include <iostream>
#include "trie.cpp"
using namespace std;

void longest_word_with_all_prefix(Node *trie_root, string &ans, string temp = "")
{
  for (const pair<char, Node *> child_pair : trie_root->children)
  {
    if (child_pair.second->is_end)
    {
      temp += child_pair.first;
      if (temp.size() > ans.size())
        ans = temp;
      longest_word_with_all_prefix(child_pair.second, ans, temp);
      temp = temp.substr(temp.size() - 1);
    }
  }
}

int main()
{
  vector<string> words = {"a", "banana", "app", "appl", "ap", "apply", "apple"};
  Trie trie;
  for (const string &word : words)
    trie.insert(word);

  string ans = "";
  longest_word_with_all_prefix(trie.get_root(), ans);
  cout << ans << endl;

  return 0;
}
