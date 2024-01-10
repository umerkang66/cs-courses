#include <iostream>
using namespace std;

// call by address
void swapByAddress(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

// call by reference
void swapByReference(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

// return by address
int *fun(int size)
{
    int *ptr = new int[size];
    for (int i = 0; i < size; i++)
    {
        ptr[i] = 1 * i;
    }
    return ptr;
}

// return by reference
int &funReference(int &x)
{
    // also returning the reference
    return x;
}

int main()
{
    int a = 10, b = 20;
    cout << a << " " << b << endl;
    swapByAddress(&a, &b);
    cout << a << " " << b << endl;

    cout << endl;

    cout << a << " " << b << endl;
    swapByReference(a, b);
    cout << a << " " << b << endl;

    // by address
    int *ptr = fun(5);
    for (int i = 0; i < 5; i++)
    {
        cout << *(ptr + i);
        if (i < 5 - 1)
        {
            cout << " ";
        }
    }
    cout << endl;

    delete[] ptr;
    ptr = nullptr;
    cout << endl;

    // by reference
    // reference is multiple variables pointing to the same address in the memory
    a = 10;
    cout << a << " ";
    funReference(a) = 25;
    cout << a << endl;

    return 0;
}
