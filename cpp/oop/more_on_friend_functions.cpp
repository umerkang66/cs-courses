#include <iostream>
using namespace std;

class Y;

class X
{
private:
    int data;

public:
    void setData(int value) { data = value; }
    friend void add(X, Y);
};

class Y
{
private:
    int num;

public:
    void setData(int value) { num = value; }
    friend void add(X, Y);
};

void add(X a1, Y a2)
{
    cout << "Sum of X and Y data is: " << a1.data + a2.num << endl;
}

int main(int argc, char const *argv[])
{
    X a;
    Y b;
    a.setData(5);
    b.setData(10);
    add(a, b);

    return 0;
}
