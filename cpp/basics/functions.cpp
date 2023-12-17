#include <iostream>
using namespace std;

int sum(int, int);

int main()
{
    int num1, num2;
    cout << "Enter num1: ";
    cin >> num1;
    cout << "Enter num2: ";
    cin >> num2;
    cout << "Your sum is: " << sum(num1, num2) << endl;
    return 0;
}

int sum(int a, int b)
{
    return a + b;
}
