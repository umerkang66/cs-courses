#include <iostream>
using namespace std;

struct employee
{
    int id;
    char favChar;
    float salary;
};

union money
{
    int rice;
    char car;
    float pounds;
};

int main()
{
    employee umer;
    umer.id = 233;
    umer.favChar = 'c';
    umer.salary = 1000.0;

    cout << umer.id << endl;
    cout << umer.favChar << endl;
    cout << umer.salary << endl;

    union money kang;
    kang.rice = 24;

    // this automatically allocate integers starting from zero
    enum Meal
    {
        breakfast,
        lunch,
        dinner
    };
    cout << breakfast << endl;
    cout << lunch << endl;
    cout << dinner << endl;

    return 0;
}
