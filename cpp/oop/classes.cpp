#include <iostream>
using namespace std;

class Employee
{
private:
    int a, b, c;
    void setDataPrivately(int a1, int b1, int c1)
    {
        a = a1;
        b = b1;
        c = c1;
    }

public:
    void setData(int, int, int);
    void getData()
    {
        cout << "The value of a: " << a << endl;
        cout << "The value of b: " << b << endl;
        cout << "The value of c: " << c << endl;
    }
};

// methods that are outside but attached to the Employee class
void Employee ::setData(int a, int b, int c)
{
    setDataPrivately(a, b, c);
}

int main(int argc, char const *argv[])
{
    Employee umer;
    umer.setData(1, 2, 3);
    umer.getData();

    return 0;
}
