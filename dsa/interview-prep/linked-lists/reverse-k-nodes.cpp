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

Node<int> *reverse_k_nodes(Node<int> *node, int k)
{
  if (node == NULL)
    return node;

  Node<int> *prev = NULL;
  Node<int> *curr = node;

  // check if you even have the k nodes
  Node<int> *temp = node;
  int count = 0;
  while (temp != NULL && count < k)
  {
    temp = temp->next;
    count++;
  }
  // this count would have been increased by one, due to line no.31, so check for less than if count is less than 3.
  if (count < k)
    return node;

  for (int i = 0; (curr != NULL) && i < k; i++)
  {
    Node<int> *next = curr->next;
    curr->next = prev;

    prev = curr;
    curr = next;
  }

  node->next = reverse_k_nodes(curr, k);
  return prev;
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
  Node<int> *reversed_by_k = reverse_k_nodes(list, 3);
  print_list(reversed_by_k);

  return 0;
}
