#include <iostream>
#include <vector>
#include "./node.hpp"
using namespace std;

// the longest distance between two distant nodes
int diameter() {}

int main()
{
  vector<int> preorder = {1, 2, 4, -1, -1, 5, -1, -1, 3, -1, 6, -1, -1};
  Node *tree = build_tree(preorder);

  return 0;
}
