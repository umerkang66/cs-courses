#include <iostream>
using namespace std;

class Complex
{
private:
    int a, b;

public:
    // now this function can access private data
    // this is not a member function, this is still an outside function
    friend Complex sumNumbers(Complex c1, Complex c2);
    void setNumber(int n1, int n2)
    {
        a = n1;
        b = n2;
    }
    void printNumber(void)
    {
        cout << a << "+" << b << "i" << endl;
    }
    static Complex sumNumbersStatic(Complex c1, Complex c2)
    {
        Complex answer;
        answer.setNumber(c1.a + c2.a, c1.b + c2.b);
        return answer;
    }
};

// friend functions are the function that interact with the class
// we have to make this function a friend with the class
Complex sumNumbers(Complex c1, Complex c2)
{
    Complex answer;
    answer.setNumber(c1.a + c2.a, c1.b + c2.b);
    return answer;
}

int main(int argc, char const *argv[])
{
    Complex c1, c2, answer, answerFriendFunction;
    c1.setNumber(1, 2);
    c2.setNumber(3, 4);

    answer = Complex::sumNumbersStatic(c1, c2);
    answerFriendFunction = sumNumbers(c1, c2);

    c1.printNumber();
    c2.printNumber();
    answer.printNumber();
    answerFriendFunction.printNumber();
    return 0;
}

/*
Properties of friend function
1.) Not in the scope of class
2.) Since it is not in the scope of the class, it can't be called with the object of class like c1.sum() and can be invoked without the help of object
3.) Usually contains the arguments as objects
4.) Can be made friends with class in the public or private section of class
5.) Can't access object properties directly, it has to use object.propertyName
*/
