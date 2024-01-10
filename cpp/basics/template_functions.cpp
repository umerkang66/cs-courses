#include <iostream>
using namespace std;

template <class T>
T maxim(T a, T b)
{
    return a + b;
}

int main()
{
    float a1 = 10.2, b1 = 20.4;
    int a2 = 10, b2 = 10;

    cout << maxim(a1, b1) << endl;
    cout << maxim(a2, b2) << endl;

    return 0;
}
