#include <iostream>
#include <vector>
#include "queue.hpp"

using namespace std;

struct Node
{
  int data;
  Node *left = nullptr;
  Node *right = nullptr;

  Node(int data) : data(data) {}
};

class BinaryTree
{
  Node *root;

  void append_nodes(Node *node, vector<int> arr, int level)
  {
    if (node == nullptr)
    {
      return;
    }

    int left_level = (2 * level) + 1;
    int right_level = (2 * level) + 2;

    if (left_level < arr.size())
    {
      node->left = new Node(arr[left_level]);
      append_nodes(node->left, arr, left_level);
    }

    if (right_level < arr.size())
    {
      node->right = new Node(arr[right_level]);
      append_nodes(node->right, arr, right_level);
    }
  }

  Node *build_tree(Node *node)
  {
    cout << "Enter the item: " << endl;
    int data;
    cin >> data;
    node = new Node(data);

    if (data == -1)
    {
      return nullptr;
    }

    cout << "Enter data for inserting in left of " << data << endl;
    node->left = build_tree(node->left);
    cout << "Enter data for inserting in right of " << data << endl;
    node->right = build_tree(node->right);
    return node;
  }

  void delete_nodes_destructor(Node *node)
  {
    if (node == nullptr)
    {
      return;
    }

    delete_nodes_destructor(node->left);
    delete_nodes_destructor(node->right);

    delete node;
  }

public:
  BinaryTree(vector<int> arr)
  {
    root = new Node(arr[0]);
    append_nodes(root, arr, 0);
  }

  BinaryTree()
  {
    root = build_tree(root);
  }

  Node *get_root()
  {
    return root;
  }

  // breath first search
  void level_order_traversal(Node *root)
  {
    Queue<Node *> queue;
    queue.enqueue(root);
    queue.enqueue(nullptr);

    while (!queue.is_empty())
    {
      Node *temp = queue.dequeue();

      if (temp == nullptr)
      {
        cout << endl;
        if (!queue.is_empty())
        {
          queue.enqueue(nullptr);
        }
      }
      else
      {
        cout << temp->data << " ";
        if (temp->left)
          queue.enqueue(temp->left);
        if (temp->right)
          queue.enqueue(temp->right);
      }
    }
  }

  void dfs_preorder(Node *node)
  {
    if (!node)
    {
      return;
    }
    cout << node->data << " ";
    dfs_preorder(node->left);
    dfs_preorder(node->right);
  }

  void dfs_postorder(Node *node)
  {
    if (!node)
    {
      return;
    }
    dfs_postorder(node->left);
    dfs_postorder(node->right);
    cout << node->data << " ";
  }

  void dfs_inorder(Node *node)
  {
    if (!node)
    {
      return;
    }
    dfs_inorder(node->left);
    cout << node->data << " ";
    dfs_inorder(node->right);
  }

  ~BinaryTree()
  {
    delete_nodes_destructor(root);
  }
};

int main()
{
  // 1 3 7 -1 -1 11 -1 -1 5 17 -1 -1 -1
  // 1 3 7 11 5 17
  BinaryTree tree;
  tree.level_order_traversal(tree.get_root());
  cout << endl;

  cout << "DFS Preorder: ";
  tree.dfs_preorder(tree.get_root());
  cout << endl;

  cout << "DFS Postorder: ";
  tree.dfs_postorder(tree.get_root());
  cout << endl;

  cout << "DFS Inorder: ";
  tree.dfs_inorder(tree.get_root());
  cout << endl;

  cout << endl
       << endl;

  vector<int> arr = {1, 3, 5, 7, 11, 17};

  BinaryTree tree2(arr);
  tree2.level_order_traversal(tree2.get_root());
  cout << endl;

  cout << "DFS Preorder: ";
  tree2.dfs_preorder(tree2.get_root());
  cout << endl;

  cout << "DFS Postorder: ";
  tree2.dfs_postorder(tree2.get_root());
  cout << endl;

  cout << "DFS Inorder: ";
  tree2.dfs_inorder(tree2.get_root());
  cout << endl;
  return 0;
}
