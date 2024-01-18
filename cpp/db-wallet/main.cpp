#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct User
{
    string name;
    string password;
    string number;
    int balance;
};

User create_user();
void signup_user();
void save_user(User user);

User *current_user = nullptr;

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
        signup_user();
    }

    return 0;
}

User create_user()
{
    User user;

    cout << "Enter your name: ";
    getline(cin, user.name);

    cout << "Enter your number: ";
    getline(cin, user.number);

    cout << "Enter your password 8 characters are allowed: ";
    getline(cin, user.password);
    user.balance = 0;

    return user;
}

void signup_user()
{
    // create the user in memory
    User user = create_user();
    // save the user in the file
    save_user(user);
    // set the current_user to this user
    *current_user = user;
}

void save_user(User user)
{
    // getting the table
    ifstream input("data.csv");

    string terminator = "---";
    string complete_table = "";
    string current_line;

    while (getline(input, current_line) && current_line != terminator)
    {
        complete_table += current_line;
        complete_table += '\n';
    }

    input.close();

    string row = user.name + ',' + user.password + ',' + user.number + ',' + to_string(user.balance) + '\n' + "---";

    complete_table += row;

    // saving the row in the table
    ofstream output("data.csv");
    output << complete_table;
    output.close();
}

// UTILITY FUNCTIONS
// This will split the string into an array by using the separator
string *split(string str, char separator)
{
    int arr_length = 1;
    for (int i = 0; i < str.length(); i++)
    {
        if (str[i] == separator)
        {
            arr_length++;
        }
    }

    // make an array of that length in the HEAP memory
    // make sure the DEALLOCATE this memory after using it
    string *arr = new string[arr_length];
    int arr_counter = 0;
    string one_string = "";
    for (int i = 0; i < str.length(); i++)
    {
        if (str[i] == separator)
        {
            arr[arr_counter] = one_string;
            one_string = "";
        }
        one_string += str[i];
    }
    arr[arr_counter] = one_string;

    return arr;
}
