#include <iostream>
using namespace std;

class C2;

class C1
{
private:
    int val;

public:
    void setData(int a) { val = a; }
    void display(void) { cout << "The value of C1: " << val << endl; }

    friend void swap(C1 &, C2 &);
};

class C2
{
private:
    int val;

public:
    void setData(int a) { val = a; }
    void display(void) { cout << "The value of C2: " << val << endl; }

    friend void swap(C1 &, C2 &);
};

void swap(C1 &a, C2 &b)
{
    int temp = a.val;
    a.val = b.val;
    b.val = temp;
}

int main(int argc, char const *argv[])
{
    C1 a;
    C2 b;

    a.setData(5);
    b.setData(8);

    a.display();
    b.display();

    swap(a, b);

    a.display();
    b.display();

    return 0;
}
