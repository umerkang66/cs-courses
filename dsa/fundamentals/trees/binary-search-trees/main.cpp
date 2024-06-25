#include <iostream>
#include <vector>

using namespace std;

struct Node
{
  Node *left = nullptr;
  Node *right = nullptr;
  int value;
  Node(int n) : value(n) {}
};

// every element should be unique
class BinarySearchTree
{
  Node *head = nullptr;

  bool search_r_helper(Node *node, int n)
  {
    if (node == nullptr)
    {
      return false;
    }

    if (n > node->value)
      return search_r_helper(node->right, n);
    else if (n < node->value)
      return search_r_helper(node->left, n);
    else
      return true;
  }

  void delete_all_nodes(Node *node)
  {
    if (node == nullptr)
      return;

    if (node->left)
      delete_all_nodes(node->left);
    if (node->right)
      delete_all_nodes(node->right);

    delete node;
  }

  Node *insert_r_helper(Node *node, int n)
  {
    if (!node)
    {
      return new Node(n);
    }

    if (n > node->value)
    {
      node->right = insert_r_helper(node->right, n);
    }
    else if (n < node->value)
    {
      node->left = insert_r_helper(node->left, n);
    }

    return node;
  }

public:
  BinarySearchTree() {}
  BinarySearchTree(vector<int> &nums)
  {
    for (int num : nums)
    {
      insert(num);
    }
  }
  BinarySearchTree(int n)
  {
    Node *new_node = new Node(n);
    head = new_node;
  }

  BinarySearchTree &insert(int n)
  {
    Node *new_node = new Node(n);
    if (!head)
    {
      head = new_node;
      return *this;
    }

    bool is_found = search(n);
    // only add is element is not found
    if (!is_found)
    {
      Node *tail = nullptr;
      Node *current = head;

      while (current != nullptr)
      {
        tail = current;
        if (n > current->value)
        {
          current = current->right;
        }
        else if (n < current->value)
        {
          current = current->left;
        }
      }

      if (n < tail->value)
      {
        tail->left = new Node(n);
        return *this;
      }

      tail->right = new Node(n);
    }

    return *this;
  }

  BinarySearchTree &insertR(int n)
  {
    if (!head)
    {
      head = insert_r_helper(head, n);
      return *this;
    }

    insert_r_helper(head, n);

    return *this;
  }

  BinarySearchTree &remove(int value)
  {
    auto last_left_of_node = [](Node *node) -> Node *
    {
      Node *current = node;
      while (current && current->left != nullptr)
      {
        current = current->left;
      }
      return current;
    };

    auto helper = [&last_left_of_node](Node *node) -> Node *
    {
      if (node->left == nullptr)
      {
        Node *right = node->right;
        delete node;
        return right;
      }
      if (node->right == nullptr)
      {
        Node *left = node->left;
        delete node;
        return left;
      }

      // if both are present
      Node *that_connects_to_previous = node->right;
      // connect the left side of node to the previous last left of node->right
      Node *last_left_of_node_right = last_left_of_node(node->right);
      last_left_of_node_right->left = node->left;

      delete node;
      return that_connects_to_previous;
    };

    if (!head)
      return *this;

    // if the found node is at the head
    if (head->value == value)
    {
      head = helper(head);
      return *this;
    }

    // otherwise
    Node *current = head;
    while (current != nullptr)
    {
      if (value > current->value)
      {
        // on the right side
        if (current->right != nullptr && current->right->value == value)
        {
          current->right = helper(current->right);
        }
        else
        {
          current = current->right;
        }
      }
      else
      {
        // on the left side
        if (current->left != nullptr && current->left->value == value)
        {
          current->left = helper(current->left);
        }
        else
        {
          current = current->left;
        }
      }
    }

    return *this;
  }

  bool search(int n)
  {
    return search_r_helper(head, n);
  }

  ~BinarySearchTree()
  {
    delete_all_nodes(head);
  }
};

int main()
{
  BinarySearchTree bst(*new vector<int>{30, 20, 40, 10, 25, 35, 50, 45});
  bst.remove(45).remove(35).remove(30);

  if (bst.search(45))
    cout << "45 Found" << endl;
  else
    cout << "45 Not Found" << endl;
  if (bst.search(35))
    cout << "35 Found" << endl;
  else
    cout << "35 Not Found" << endl;
  if (bst.search(30))
    cout << "30 Found" << endl;
  else
    cout << "30 Not Found" << endl;

  return 0;
}
