#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct User
{
    char name[40];
    char password[9]; // one for string terminator char
    char number[12];
    int balance;
};

User signup_user();
void save_user(User user);

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

    cin.ignore();

    if (haveAccount == 'y' || haveAccount == 'Y')
    {
        // USER WANTS TO SIGNIN
    }
    else
    {
        // USER WANTS TO SIGNUP
        User user = signup_user();
        save_user(user);
    }

    return 0;
}

User signup_user()
{
    User user;

    cout << "Enter your name: ";
    cin.getline(user.name, 40);

    cout << "Enter your number: ";
    cin.getline(user.number, 40);

    cout << "Enter your password 8 characters are allowed: ";
    cin.getline(user.password, 40);
    user.balance = 0;

    return user;
}

void save_user(User user)
{
    // first check if the user table exists
    ifstream input("data.csv");

    string terminator = "---";
    string complete_table = "";
    string current_line;

    while (getline(input, current_line) && current_line != terminator)
    {
        complete_table += current_line;
        if (current_line != terminator)
        {
            complete_table += '\n';
        }
    }

    cout << complete_table << endl;
}
