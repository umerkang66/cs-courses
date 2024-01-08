#include <iostream>
using namespace std;

enum day
{
    mon = 1,
    tue,
    wed,
    thur,
    fri,
    sat,
    sun
};

int main()
{
    day d;
    d = mon;

    if (d == mon)
    {
        cout << "Today is monday" << endl;
    }

    cout << d << endl;
    cout << sun << endl;
    return 0;
}
