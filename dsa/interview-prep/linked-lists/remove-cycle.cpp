#include <iostream>
#include "ll-node.hpp"

using namespace std;

void print_list(Node<int> *head)
{
  Node<int> *current = head;
  while (current != NULL)
  {
    cout << current->data << " -> ";
    current = current->next;
  }
  cout << "NULL";
  cout << endl;
}

void remove_cycle(Node<int> *head)
{
  Node<int> *slow = head;
  Node<int> *fast = head;
  Node<int> *previous_to_fast;

  while (fast != NULL && fast->next != NULL)
  {
    slow = slow->next;
    fast = fast->next->next;
    previous_to_fast = fast->next;

    if (slow == fast)
      break;
  }

  // if there is no cycle
  if (fast == NULL || fast->next == NULL)
    return;

  slow = head;
  while (slow != fast)
  {
    slow = slow->next;
    previous_to_fast = fast;
    fast = fast->next;
  }

  previous_to_fast->next = NULL;
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

  remove_cycle(list);

  print_list(list);

  return 0;
}
