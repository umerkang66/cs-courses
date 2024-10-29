// https://www.naukri.com/code360/problems/top-view-of-binary-tree_799401

#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include "./node.hpp"
using namespace std;

void top_view(Node *tree)
{
  // first is data, second is horizontal distance
  queue<pair<Node *, int>> q;
  q.push(make_pair(tree, 0));

  // first value is
  map<int, int> m;

  while (!q.empty())
  {
    pair<Node *, int> curr = q.front();
    q.pop();

    if (!m[curr.second])
      m[curr.second] = curr.first->data;

    if (curr.first->left)
      q.push(make_pair(curr.first->left, curr.second - 1));

    if (curr.first->right)
      q.push(make_pair(curr.first->right, curr.second + 1));
  }

  for (const auto &[key, value] : m)
    cout << value << ' ';
  cout << endl;
}

int main()
{
  vector<int> preorder = {1, 2, -1, 4, -1, 5, -1, 6, -1, -1, 3, -1, -1};
  Node *tree = build_tree(preorder);

  top_view(tree);

  return 0;
}
