// https://leetcode.com/problems/reverse-linked-list

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

void reverse(Node<int> *&head)
{
  Node<int> *prev = NULL;
  Node<int> *curr = head;

  while (curr != NULL)
  {
    Node<int> *next = curr->next;
    curr->next = prev;

    prev = curr;
    curr = next;
  }

  head = prev;
}

int main()
{
  int arr[] = {5, 4, 3, 2, 1};
  int n = 5;
  Node<int> *list = new Node(arr[0]);

  Node<int> *current = list;
  for (int i = 1; i < n; i++)
  {
    current->next = new Node(arr[i]);
    current = current->next;
  }

  print_list(list);
  reverse(list);
  print_list(list);

  return 0;
}
