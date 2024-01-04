#include <iostream>
using namespace std;

int count = 0;

class Num
{
public:
    Num(void)
    {
        count++;
        cout << "Constructor is called: " << count << endl;
    }

    // destructor
    ~Num()
    {
        cout << "Destructor is called: " << count << endl;
        count--;
    }
};

int main()
{
    cout << "Main function" << endl;
    cout << "Creating first object n1" << endl;
    Num n1;

    {
        cout << "Entering this block" << endl;
        cout << "Creating two more objects" << endl;
        Num n2, n3;
        cout << "Existing this block" << endl;
    }

    cout << "Back to main" << endl;

    return 0;
}
