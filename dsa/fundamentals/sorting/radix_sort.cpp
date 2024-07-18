#include <iostream>
#include <cmath>

using namespace std;

struct Node
{
  int data;
  Node *next = nullptr;
  Node(const int &data) : data(data) {}
};

int find_length_of_max_element(int *nums, int n)
{
  int largest = nums[0];
  for (int i = 0; i < n; i++)
    largest = max(largest, nums[i]);
  int length = 0;
  while (largest != 0)
  {
    length++;
    largest /= 10;
  }
  return length;
}

void sort(int *nums, int n)
{
  int max_length = find_length_of_max_element(nums, n);

  // for decimal numbers, on 10 are needed
  int decimal_length = 10;
  Node *arr[decimal_length];
  for (int i = 0; i < decimal_length; i++)
    arr[i] = nullptr;

  for (int i = 0; i < max_length; i++)
  {
    for (int j = 0; j < n; j++)
    {
      int index = (nums[j] / (int)pow(10, i)) % 10;
      if (arr[index] == nullptr)
      {
        arr[index] = new Node(nums[j]);
      }
      else
      {
        Node *temp = arr[index];
        while (temp->next != nullptr)
          temp = temp->next;
        temp->next = new Node(nums[j]);
      }
    }

    int k = 0;
    for (int i = 0; i < decimal_length; i++)
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
}

void display(int *nums, int n)
{
  for (int i = 0; i < n; i++)
    cout << nums[i] << ' ';
  cout << endl;
}

int main()
{
  int nums[] = {237, 146, 259, 348, 152, 163, 235, 48, 36, 62};
  display(nums, 10);
  sort(nums, 10);
  display(nums, 10);

  return 0;
}
