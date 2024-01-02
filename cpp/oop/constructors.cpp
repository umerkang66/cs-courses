#include <iostream>
using namespace std;

class Complex
{
private:
    int a, b;

public:
    Complex(int real, int imag);
    void printNumber(void)
    {
        cout << a << "+" << b << "i" << endl;
    }
};

Complex::Complex(int real, int imag)
{
    a = real;
    b = imag;
}

int main(int argc, char const *argv[])
{
    Complex complex(3, 4);
    complex.printNumber();
    return 0;
}
