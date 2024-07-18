#include <iostream>
using namespace std;

struct Node
{
  int data;
  Node *next = nullptr;
  Node(const int &data) : data(data) {}
};

int find_max(int *nums, int n)
{
  int largest = nums[0];
  for (int i = 0; i < n; i++)
    largest = max(largest, nums[i]);
  return largest;
}

void sort(int *nums, int n)
{
  int max = find_max(nums, n);

  Node *arr[max + 1];
  for (int i = 0; i < max + 1; i++)
    arr[i] = nullptr;

  for (int i = 0; i < n; i++)
  {
    if (arr[nums[i]] == nullptr)
    {
      arr[nums[i]] = new Node(nums[i]);
    }
    else
    {
      Node *temp = arr[nums[i]];
      while (temp->next != nullptr)
        temp = temp->next;
      temp->next = new Node(nums[i]);
    }
  }

  int k = 0;
  for (int i = 0; i < max + 1; i++)
  {
    Node *temp = arr[i];
    if (temp != nullptr)
    {
      while (temp != nullptr)
      {
        nums[k++] = temp->data;
        Node *to_be_deleted = temp;
        temp = temp->next;
        delete to_be_deleted;
        arr[i] = temp;
      }
    }
  }
}

void display(int *nums, int n)
{
  for (int i = 0; i < n; i++)
    cout << nums[i] << ' ';
  cout << endl;
}

int main()
{
  int nums[] = {5, 8, 3, 4, 3, 9, 1, 9};
  display(nums, 8);
  sort(nums, 8);
  display(nums, 8);

  return 0;
}
