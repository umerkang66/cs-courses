#include <iostream>
#include "ll-node.hpp"

using namespace std;

bool detect_cycle(Node<int> *head)
{
  Node<int> *slow = head;
  Node<int> *fast = head;

  while (fast != NULL && fast->next != NULL)
  {
    slow = slow->next;
    fast = fast->next->next;

    if (slow == fast)
      return true;
  }

  return false;
}

int main()
{
  Node<int> *list = new Node(1);

  Node<int> *current = list;

  current->next = new Node<int>(2);
  current = current->next;
  current->next = new Node<int>(3);
  current = current->next;
  Node<int> *cycle_start = current;
  current->next = new Node<int>(4);
  current = current->next;
  current->next = new Node<int>(5);
  current = current->next;
  current->next = new Node<int>(6);
  current = current->next;
  current->next = new Node<int>(7);
  current = current->next;
  current->next = new Node<int>(8);
  current = current->next;
  current->next = cycle_start;

  cout << detect_cycle(list) << endl;

  return 0;
}
