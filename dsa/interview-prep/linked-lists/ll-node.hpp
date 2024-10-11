#include <iostream>
using namespace std;

template <class T>
struct Node
{
  T data;
  Node<T> *next = NULL;
  Node(const T &data) { this->data = data; }

  friend ostream &operator<<(ostream &os, Node<T> &list_node)
  {
    os << "[";
    Node<T> *current_node = &list_node;
    while (current_node != NULL)
    {
      os << current_node->data;
      if (current_node->next != NULL)
      {
        os << " --> ";
      }
      current_node = current_node->next;
    }
    os << "]";
    return os;
  }
};
