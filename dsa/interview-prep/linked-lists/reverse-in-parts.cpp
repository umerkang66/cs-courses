// https://leetcode.com/problems/reverse-linked-list-ii/

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

void reverse_in_parts(Node<int> *&head, int left, int right)
{
  if (head == NULL || left == right)
    return;

  Node<int> *prev = NULL;
  Node<int> *curr = head;
  Node<int> *last_previous = NULL;
  Node<int> *last_next = NULL;

  int counter = 1;

  while (counter < left)
  {
    // this will be 1 in our case
    last_previous = curr;
    prev = curr;
    curr = curr->next;
    counter++;
  }

  // this will be 2 in our case
  last_next = curr;

  while (counter <= right)
  {
    Node<int> *next = curr->next;
    curr->next = prev;

    prev = curr;
    curr = next;
    counter++;
  }

  if (last_previous == NULL)
    head = prev;
  else
    last_previous->next = prev;

  last_next->next = curr;
}

int main()
{
  int arr[] = {1, 2, 3, 4, 5};
  int n = 5;
  Node<int> *list = new Node(arr[0]);

  Node<int> *current = list;
  for (int i = 1; i < n; i++)
  {
    current->next = new Node(arr[i]);
    current = current->next;
  }

  print_list(list);
  reverse_in_parts(list, 2, 4);
  print_list(list);

  return 0;
}
