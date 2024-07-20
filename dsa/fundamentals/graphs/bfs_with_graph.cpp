#include <iostream>
#include <vector>
#include <queue>

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

void bfs(Node *root)
{
  queue<Node *> tracking_queue;
  tracking_queue.push(root);

  while (!tracking_queue.empty())
  {
    Node *current_vertex = tracking_queue.front();
    current_vertex->visited = true;
    tracking_queue.pop();

    for (Node *&connected_vertex : current_vertex->connected_nodes)
    {
      if (!connected_vertex->visited)
      {
        tracking_queue.push(connected_vertex);
        connected_vertex->visited = true;
      }
    }

    cout << current_vertex->data << ' ';
  }

  cout << endl;
}

int main()
{
  Node *root = create_graph();
  bfs(root);

  return 0;
}
