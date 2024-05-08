#include <iostream>
using namespace std;

struct Node
{
  int data;
  Node *left = nullptr;
  Node *right = nullptr;

  Node(int data) : data(data) {}
};

class Tree
{
  Node *root;

public:
  Tree()
  {
  }
};

int main()
{

  return 0;
}
