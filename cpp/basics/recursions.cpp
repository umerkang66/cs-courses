#include <iostream>
using namespace std;

int fibonacci(int);
int factorial(int, int);

int main()
{
    int n;
    cout << "Enter n: ";
    cin >> n;
    int fib = fibonacci(n);
    cout << "The fibonacci of " << n << " is: " << fib << endl;

    int fact = factorial(n, 1);
    cout << "The factorial of " << n << " is: " << fact << endl;
    return 0;
}

int fibonacci(int n)
{
    if (n == 0 || n == 1)
    {
        return n;
    }
    return fibonacci(n - 1) + fibonacci(n - 2);
}

int factorial(int n, int ans = 1)
{
    if (n == 1)
    {
        return ans;
    }
    return factorial(n - 1, ans * n);
}
