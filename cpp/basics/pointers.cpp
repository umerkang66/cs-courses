#include <iostream>
using namespace std;

int main()
{
    int arr[5] = {2, 4, 6, 8, 10};
    int *p = arr;
    int *q = &arr[4];

    cout << q - p << endl;
}
