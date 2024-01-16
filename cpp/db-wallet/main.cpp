#include <iostream>
#include <fstream>

using namespace std;

struct user
{
    char name[40];
    char number[11];
    int balance;
};

int main()
{
    cout << "Do you have the account? (y/n) ";
    char haveAccount;
    cin >> haveAccount;

    while (haveAccount != 'y' && haveAccount != 'Y' && haveAccount != 'n' && haveAccount != 'N')
    {
        cout << "Do you have the account? (y/n) ";
        cin >> haveAccount;
    }

    if (haveAccount == 'y' || haveAccount == 'Y')
    {
        // USER WANTS TO SIGNIN
    }
    else
    {
        // USER WANTS TO SIGNUP
    }

    return 0;
}
