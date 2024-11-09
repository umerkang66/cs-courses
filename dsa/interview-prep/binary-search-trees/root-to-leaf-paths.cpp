#include <iostream>
#include "node.hpp"
using namespace std;

void print_vector(vector<int> &v)
{
  for (const int &item : v)
    cout << item << ' ';
  cout << endl;
}

void root_to_leaf_paths(Node *root)
{
  static vector<int> answers;
  if (root == NULL)
    return;

  answers.push_back(root->data);
  if (!root->left && !root->right)
    print_vector(answers);

  root_to_leaf_paths(root->left);
  root_to_leaf_paths(root->right);
  answers.pop_back();
}

int main()
{
  vector<int> arr = {8, 5, 3, 6, 1, 4, 10, 11, 14};
  Node *tree = build_from_arr(arr);

  root_to_leaf_paths(tree);

  return 0;
}
