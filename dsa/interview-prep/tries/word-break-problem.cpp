#include <iostream>
#include "trie.cpp"
using namespace std;

bool word_break(Trie &trie, string key)
{
  if (key.size() == 0)
    return true;

  for (int i = 0; i < key.size(); i++)
  {
    string first = key.substr(0, i + 1);
    string second = key.substr(i + 1);

    // if first is found, only then go for the second one
    if (trie.search(first) && word_break(trie, second))
      return true;
  }

  return false;
}

int main()
{
  vector<string> words = {"i", "like", "sam", "samsung", "mobile", "ice"};
  string key = "ilikesamsung";
  Trie trie;
  for (const string &word : words)
    trie.insert(word);

  cout << word_break(trie, key) << endl;

  return 0;
}

class Solution
{
public:
  bool wordBreak(string s, vector<string> &wordDict)
  {
  }
};