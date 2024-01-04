#include <iostream>
using namespace std;

class Complex
{
private:
    int a, b;

public:
    Complex(void)
    {
        a = 0;
        b = 0;
    }

    Complex(int real)
    {
        a = real;
        b = 0;
    }

    Complex(int real, int imag)
    {
        a = real;
        b = imag;
    }

    void printNumber(void)
    {
        cout << a << "+" << b << "i" << endl;
    }
};

int main(int argc, char const *argv[])
{
    Complex complex(3, 4);
    complex.printNumber();

    Complex complex2(2);
    complex2.printNumber();

    Complex complex3;
    complex3.printNumber();

    return 0;
}
