#include <iostream>
#include <vector>

using namespace std;

struct Node
{
  Node *left = nullptr;
  Node *right = nullptr;
  // when new node is inserted, by default its height becomes 0
  int height = 1;
  int value;
  Node(int n) : value(n) {}
};

class AVL
{
private:
  Node *root = nullptr;

  void delete_nodes(Node *node)
  {
    if (node == nullptr)
      return;

    if (node->left)
      delete_nodes(node->left);
    if (node->right)
      delete_nodes(node->right);

    delete node;
  }

  int node_height(Node *node)
  {
    int h_l = node && node->left ? node->left->height : 0;

    int h_r = node && node->right ? node->right->height : 0;

    // which one is greater add one to it
    return h_l > h_r ? h_l + 1 : h_r + 1;
  }

  int balance_factor(Node *node)
  {
    int h_l = node && node->left ? node->left->height : 0;

    int h_r = node && node->right ? node->right->height : 0;

    return h_l - h_r;
  }

  Node *LL_rotation(Node *p)
  {
    Node *pl = p->left;
    Node *plr = pl->right;

    pl->right = p;
    p->left = plr;

    // updating the heights
    // only p and pl heights will change
    p->height = node_height(p);
    pl->height = node_height(pl);

    return pl;
  }
  Node *LR_rotation(Node *p)
  {
    Node *pl = p->left;
    Node *plr = pl->right;

    pl->right = plr->left;
    p->left = plr->right;

    plr->left = pl;
    plr->right = p;

    p->height = node_height(p);
    pl->height = node_height(pl);
    plr->height = node_height(plr);

    return plr;
  }
  Node *RR_rotation(Node *p)
  {
    Node *pr = p->right;
    Node *prl = pr->left;

    pr->left = p;
    p->right = prl;

    // updating the heights
    // only p and pl heights will change
    p->height = node_height(p);
    pr->height = node_height(pr);

    return pr;
  }
  Node *RL_rotation(Node *p)
  {
    Node *pr = p->right;
    Node *prl = pr->left;

    pr->left = prl->right;
    p->right = prl->left;

    prl->left = p;
    prl->right = pr;

    p->height = node_height(p);
    pr->height = node_height(pr);
    prl->height = node_height(prl);

    return prl;
  }

  Node *insert_helper(Node *node, int n)
  {
    Node *new_node = new Node(n);
    if (!node)
    {
      node = new_node;
      return node;
    }

    if (n < node->value)
      node->left = insert_helper(node->left, n);
    else
      node->right = insert_helper(node->right, n);

    node->height = node_height(node);

    if (balance_factor(node) == 2 && balance_factor(node->left) == 1)
      return LL_rotation(node);
    else if (balance_factor(node) == 2 && balance_factor(node->left) == -1)
      return LR_rotation(node);
    else if (balance_factor(node) == -2 && balance_factor(node->right) == -1)
      return RR_rotation(node);
    else if (balance_factor(node) == -2 && balance_factor(node->right) == 1)
      return RL_rotation(node);

    return node;
  }

public:
  AVL() {}
  AVL(const vector<int> &nums)
  {
    for (int num : nums)
    {
      insert(num);
    }
  }
  AVL(int n)
  {
    Node *new_node = new Node(n);
    root = new_node;
  }
  ~AVL() { delete_nodes(root); }
  Node *get_root() const { return root; }
  AVL &insert(int n)
  {
    root = insert_helper(root, n);
    return *this;
  }
  AVL &insert(const vector<int> &nums)
  {
    for (int num : nums)
    {
      // because of balancing, root might change
      // so update the root every time
      root = insert_helper(root, num);
    }
    return *this;
  }
  void reset()
  {
    delete_nodes(root);
    root = nullptr;
  }
};

int main()
{
  AVL avl(vector<int>{10, 5, 2});
  avl.insert(10).insert(5).insert(2);
  cout << avl.get_root()->value << endl; // 5 should be new root

  avl.reset();
  avl.insert(vector<int>{50, 10, 20});
  cout << avl.get_root()->value << endl; // root should be 20

  avl.reset();
  avl.insert(vector<int>{10, 20, 15, 14, 16});
  cout << avl.get_root()->value << endl; // root should be 15

  return 0;
}
