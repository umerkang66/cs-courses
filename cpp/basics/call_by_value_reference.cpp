#include <iostream>
using namespace std;

void swapByAddress(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void swapCppReference(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

int main()
{
    int a = 4, b = 5;
    cout << "a: " << a << ", b: " << b << endl;
    swapCppReference(a, b);
    cout << "a: " << a << ", b: " << b << endl;
    return 0;
}
