#include <iostream>
#include <vector>
#include <stack>

using namespace std;

struct Node
{
  int data;
  bool visited = false;
  vector<Node *> connected_nodes;
  Node(int n = 0) : data(n) {}
};

Node *create_graph()
{
  Node *one = new Node(1);
  Node *two = new Node(2);
  Node *three = new Node(3);
  Node *four = new Node(4);
  Node *five = new Node(5);
  Node *six = new Node(6);
  Node *seven = new Node(7);

  five->connected_nodes = vector<Node *>{six, seven};
  four->connected_nodes = vector<Node *>{five, three, one};
  three->connected_nodes = vector<Node *>{five, four, two, one};
  two->connected_nodes = vector<Node *>{one, three};
  one->connected_nodes = vector<Node *>{two, four, three};

  return one;
}

void dfs(Node *node)
{
  if (!node)
    return;

  cout << node->data << ' ';
  node->visited = true;

  for (Node *connected_node : node->connected_nodes)
  {
    if (!connected_node->visited)
      dfs(connected_node);
  }
}

int main()
{
  Node *root = create_graph();

  cout << "Preorder: ";
  dfs(root);
  cout << endl;

  return 0;
}
