#include <iostream>
using namespace std;

// forward declaration
class Complex;

class Calculator
{
public:
    Complex sumComplexComplete(Complex, Complex);
    int sumRealPart(Complex, Complex);
    int sumImagPart(Complex, Complex);
};

class Complex
{
private:
    int a, b;

public:
    // hey sumComplex of of Calculator class, get access to my private data
    // Individually declaring functions as FRIENDS
    friend Complex Calculator::sumComplexComplete(Complex a, Complex b);
    // Declaring the entire Calculator class
    friend class Calculator;

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

Complex Calculator::sumComplexComplete(Complex a, Complex b)
{
    Complex answer;
    answer.setNumber(a.a + b.a, a.b + b.b);
    return answer;
}
// BELOW two functions will run, because we have made the whole class FRIEND CLASS
int Calculator::sumRealPart(Complex a, Complex b)
{
    return a.a + b.a;
}
int Calculator::sumImagPart(Complex a, Complex b)
{
    return a.b + b.b;
}

int main(int argc, char const *argv[])
{
    Complex a, b, sum;
    a.setNumber(4, 5);
    b.setNumber(3, 9);

    Calculator calculator;
    sum = calculator.sumComplexComplete(a, b);

    a.printNumber();
    b.printNumber();
    sum.printNumber();

    cout << "The of real part: " << calculator.sumRealPart(a, b) << endl;
    cout << "The of imaginary part: " << calculator.sumImagPart(a, b) << endl;

    return 0;
}
