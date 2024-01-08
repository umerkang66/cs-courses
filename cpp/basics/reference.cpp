#include <iostream>
using namespace std;

int main()
{
    int x = 10;
    int &y = x;

    cout << x << endl;
    cout << y << endl;
    x++;
    y++;
    cout << endl;
    cout << x << endl;
    cout << y << endl;
    cout << endl;
    cout << &x << " " << &y << endl;

    return 0;
}
