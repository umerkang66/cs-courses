// https://www.interviewbit.com/problems/shortest-unique-prefix/

#include <iostream>
#include "trie.cpp"
using namespace std;

void prefix_problem(Trie &trie, const vector<string> &words)
{
  vector<string> answers;

  for (const string &word : words)
  {
    string ans = "";
    Node *temp = trie.get_root();

    for (int i = 0; i < word.size(); i++)
    {
      if (temp->children.count(word[i]))
      {
        ans += word[i];
        // it doesn't have any children
        // so this should be the last unique element
        if (temp->children[word[i]]->freq == 1)
          break;
      }
      temp = temp->children[word[i]];
    }

    answers.push_back(ans);
  }

  for (const string &vals : answers)
    cout << vals << ' ';
  cout << endl;
}

int main()
{
  vector<string> words = {"zebra", "dog", "duck", "dove"};
  Trie trie;
  for (const string &word : words)
    trie.insert(word);

  prefix_problem(trie, words);
  return 0;
}
