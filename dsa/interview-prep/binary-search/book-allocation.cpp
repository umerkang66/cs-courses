#include <iostream>
using namespace std;

int sum(int *arr, int length)
{
  int sum = 0;
  for (int i = 0; i < length; i++)
    sum += arr[i];
  return sum;
}

bool is_valid(int *books, int length, int students, int mid)
{
  int curr_students = 1;
  int curr_pages = 0;

  for (int i = 0; i < length; i++)
  {
    // if current book page is greater than mid, answer is false
    if (books[i] > mid)
      return false;

    // if pages are more than the limit, increase the students, and reset the current page
    if (curr_pages + books[i] > mid)
    {
      curr_students++;
      curr_pages = books[i];
    }
    else
      curr_pages += books[i];
  }

  // if students are increasing than the allowed students, solution is invalid
  if (curr_students > students)
    return false;
  return true;
}

int allocate_books(int *books, int length, int students)
{
  if (students > length)
    return -1;

  int start = 0;
  // get all the possible answers
  int end = sum(books, length);
  int ans = -1;

  // binary search all the possible answers
  while (start <= end)
  {
    int mid = start + (end - start) / 2;

    if (is_valid(books, length, students, mid))
    {
      ans = mid;
      // solution is found
      // be more greedy, check if more less solution exists
      end = mid - 1;
    }
    else
    {
      // if the valid solution does not exist, increase the pages
      start = mid + 1;
    }
  }

  return ans;
}

int main(int argc, const char *argv[])
{
  int books[] = {2, 1, 3, 4};
  int length = sizeof(books) / sizeof(books[0]);

  cout << allocate_books(books, length, 2) << endl;

  return 0;
}
