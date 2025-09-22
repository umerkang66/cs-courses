#include <iostream>
using namespace std;

class SegmentTree
{
  struct Node
  {
    int data = 0;
    int start_interval;
    int end_interval;
    Node *left = nullptr;
    Node *right = nullptr;

    Node(int start, int end) : start_interval(start), end_interval(end) {}
  };

  static void display(Node *node)
  {
    if (!node)
      return;

    cout << '[' << node->start_interval << ", " << node->end_interval << "]: " << node->data << endl;

    display(node->left);
    display(node->right);
  }

  Node *root;

  Node *construct_tree(int *arr, int start, int end)
  {
    if (start == end)
    {
      // only one element is selected, we are at the leaf node
      Node *leaf = new Node(start, end);
      leaf->data = arr[start];
      return leaf;
    }

    Node *node = new Node(start, end);
    int mid = (start + end) / 2;

    node->left = construct_tree(arr, start, mid);
    node->right = construct_tree(arr, mid + 1, end);

    node->data = node->left->data + node->right->data;

    return node;
  }

  void delete_nodes(Node *node)
  {
    if (!node)
      return;
    delete_nodes(node->left);
    delete_nodes(node->right);
    delete node;
  }

  int query(Node *node, int query_start_i, int query_end_i)
  {
    if (node->start_interval >= query_start_i && node->end_interval <= query_end_i)
    {
      // node lies between the start and end
      // we will take all the items in this node
      return node->data;
    }
    else if (node->start_interval > query_end_i || node->end_interval < query_start_i)
    {
      // completely out of range
      return 0;
    }
    else
    {
      // it is overlapping, to find the left and right, call the recursion
      int left_answer = query(node->left, query_start_i, query_end_i);   // might be 0 or data
      int right_answer = query(node->right, query_start_i, query_end_i); // might be 0 or data
      return left_answer + right_answer;
    }
  }

  int update(Node *node, int index, int value)
  {
    if (index <= node->end_interval && index >= node->start_interval)
    {
      if (index == node->start_interval && index == node->end_interval)
        // only one element is selected
        return node->data = value;
      else
      {
        // index is not pointing at the single element
        // find the data of left and right
        // update the data current node by adding the left and right right
        int left_data = update(node->left, index, value);
        int right_data = update(node->right, index, value);
        node->data = left_data + right_data;
        return node->data;
      }
    }
    else
      // don't update it, just return it
      return node->data;
  }

public:
  SegmentTree(int *arr, int n)
  {
    // create a tree using this arr
    root = construct_tree(arr, 0, n - 1);
  }
  ~SegmentTree() { delete_nodes(root); }

  Node *get_root() const { return root; }

  int query(int query_start_i, int query_end_i) { return query(root, query_start_i, query_end_i); }

  void update(int index, int value) { root->data = update(root, index, value); }

  friend ostream &operator<<(ostream &cout, SegmentTree &t)
  {
    t.display(t.get_root());
    return cout;
  }
};

int main()
{
  int arr[] = {3, 8, 6, 7, -2, -8, 4, 9};
  int n = sizeof(arr) / sizeof(arr[0]);

  SegmentTree tree(arr, n);
  cout << tree.query(1, 4) << endl; // 19
  tree.update(2, 8);
  cout << tree.query(1, 4) << endl; // 21

  return 0;
}
