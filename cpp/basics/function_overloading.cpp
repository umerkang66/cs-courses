#include <iostream>
using namespace std;

int add(int a, int b);
int add(int a, int b, int c);

int main()
{
    int a = 2, b = 3, c = 4;
    cout << "The sum of 2 numbers: " << add(a, b) << endl;
    cout << "The sum of 3 numbers: " << add(a, b, c) << endl;

    return 0;
}

int add(int a, int b)
{
    return a + b;
}

int add(int a, int b, int c)
{
    return a + b + c;
}