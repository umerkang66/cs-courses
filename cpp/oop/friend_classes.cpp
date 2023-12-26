#include <iostream>
using namespace std;

class Calculator
{
public:
    int add(int a, int b) { return a + b; }
    Complex sumComplex(Complex a, Complex b)
    {
        Complex answer;
        answer.setNumber(a.a + b.a, a.b + b.b);
    }
};

class Complex
{
private:
    int a, b;

public:
    // hey sumComplex of of Calculator class, get access to my private data
    friend Complex Calculator::sumComplex(Complex a, Complex b);
    void setNumber(int n1, int n2)
    {
        a = n1;
        b = n2;
    }
    void printNumber(void)
    {
        cout << a << "+" << b << "i" << endl;
    }
};

int main(int argc, char const *argv[])
{

    return 0;
}
