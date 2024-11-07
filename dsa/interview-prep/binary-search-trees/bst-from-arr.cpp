#include <iostream>
#include <queue>
using namespace std;

struct Node
{
  int data;
  Node *left = NULL;
  Node *right = NULL;

  Node(int n) : data(n) {}
};

void show(Node *tree)
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

Node *insert_in_root(Node *root, int n)
{
  if (root == NULL)
    return new Node(n);

  if (n < root->data)
    root->left = insert_in_root(root->left, n);
  else
    root->right = insert_in_root(root->right, n);

  return root;
}

Node *build_from_arr(int *arr, int n)
{
  Node *root = new Node(arr[0]);

  for (int i = 1; i < n; i++)
    insert_in_root(root, arr[i]);

  return root;
}

int main()
{
  int arr[] = {5, 1, 3, 4, 2, 7};
  Node *tree = build_from_arr(arr, sizeof(arr) / sizeof(arr[0]));

  show(tree);

  return 0;
}
