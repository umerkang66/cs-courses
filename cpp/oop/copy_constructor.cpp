#include <iostream>
using namespace std;

class Number
{
    int a;

public:
    Number() {}
    Number(int num)
    {
        a = num;
    }
    Number(Number &obj)
    {
        cout << "Copy constructor called" << endl;
        a = obj.a;
    }
    void display()
    {
        cout << a << endl;
    }
};

int main()
{
    Number a1(5);
    Number a2(a1);
    Number a3 = a1;

    a1.display();
    a2.display();
    a3.display();

    cout << endl;

    cout << &a1 << endl;
    cout << &a2 << endl;
    cout << &a3 << endl;

    return 0;
}
