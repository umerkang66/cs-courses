// https://leetcode.com/problems/reorder-list/

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

Node<int> *mid(Node<int> *head)
{
  Node<int> *slow = head;
  Node<int> *fast = head;
  Node<int> *prev = NULL;

  while (fast != NULL && fast->next != NULL)
  {
    prev = slow;
    slow = slow->next;
    fast = fast->next->next;
  }

  prev->next = NULL;
  return slow;
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

void zig_zag(Node<int> *head)
{
  if (head == NULL || head->next == NULL)
    return;

  Node<int> *second_half = mid(head);
  Node<int> *first_half = head;
  // reverse the second half
  reverse(second_half);

  Node<int> *first_half_pointer = first_half;
  Node<int> *second_half_pointer = second_half;

  Node<int> *result = first_half_pointer;
  first_half_pointer = first_half_pointer->next;

  Node<int> *result_pointer = result;

  while (first_half_pointer != NULL && second_half_pointer != NULL)
  {
    // second half merging
    result->next = second_half_pointer;
    result = result->next;
    second_half_pointer = second_half_pointer->next;

    // first half merging
    result->next = first_half_pointer;
    result = result->next;
    first_half_pointer = first_half_pointer->next;
  }

  while (first_half_pointer != NULL)
  {
    result->next = first_half_pointer;
    result = result->next;
    first_half_pointer = first_half_pointer->next;
  }

  while (second_half_pointer != NULL)
  {
    result->next = second_half_pointer;
    result = result->next;
    second_half_pointer = second_half_pointer->next;
  }

  head = result;
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
  zig_zag(list);
  print_list(list);

  return 0;
}
