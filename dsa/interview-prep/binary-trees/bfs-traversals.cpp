#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct Node
{
  int data;
  Node *left = NULL;
  Node *right = NULL;

  Node(int n) : data(n) {}
};

Node *build_tree(vector<int> &nodes)
{
  static int index = 0;
  if (index >= nodes.size() || nodes[index] == -1)
  {
    index++;
    return NULL;
  }

  Node *node = new Node(nodes[index++]);
  node->left = build_tree(nodes);
  node->right = build_tree(nodes);

  return node;
}

void bfs_traversal(Node *tree)
{
  queue<Node *> q;
  q.push(tree);

  while (!q.empty())
  {
    Node *curr = q.front();
    // removing the current
    q.pop();

    cout << curr->data << ' ';

    // adding the childrens of current popped
    if (curr->left)
      q.push(curr->left);
    if (curr->right)
      q.push(curr->right);
  }
}

void bfs_traversal_inline(Node *tree)
{
  queue<Node *> q;
  q.push(tree);
  q.push(NULL);

  while (!q.empty())
  {
    Node *curr = q.front();
    // removing the current
    q.pop();

    if (curr == NULL)
    {
      cout << endl;
      if (q.empty())
        break;
      q.push(NULL);
    }
    else
    {
      cout << curr->data << ' ';

      // adding the childrens of current popped
      if (curr->left)
        q.push(curr->left);
      if (curr->right)
        q.push(curr->right);
    }
  }
}

int main()
{
  vector<int> preorder = {1, 2, 4, -1, -1, 5, -1, -1, 3, -1, 6, -1, -1};
  Node *tree = build_tree(preorder);

  bfs_traversal(tree);
  cout << endl;
  bfs_traversal_inline(tree);

  return 0;
}
