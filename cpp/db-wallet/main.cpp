#include <iostream>
#include <fstream>

using namespace std;

struct User
{
    string name;
    string password;
    string number;
    int balance;
};

// APPLICATION FUNCTIONS
void authenticate();
User create_user();
void signup_user();
void save_user_to_file(User user);
// UTILITY FUNCTIONS
string *split(string str, char separator);
string get_all_tables();

User current_user;

int main()
{
    // This will prompt the user to signIn or signUp
    // and will set the current user
    authenticate();

    return 0;
}

void authenticate()
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
    save_user_to_file(user);
    // set the current_user to this user
    current_user = user;
}

void save_user_to_file(User user)
{
    // getting the table
    string complete_table = get_all_tables();
    cout << complete_table << endl;
    string terminator = "---";
    cout << complete_table << endl;

    // if user already exists update the user
    // else add the user at the end of table
    bool does_user_exists = false; // THIS IS TEMPORARY TRUE
    // first create array by new line separator
    string *lines = split(complete_table, '\n');
    for (int i = 2; i < lines->size() - 2; i++)
    {
        // for every create an array by ',' separator
        string *fields = split(lines[i], ',');

        // this field will be a number in database
        if (fields[2] == user.number)
        {
            does_user_exists = true;
        }

        delete[] fields;
        fields = nullptr;
    }

    delete[] lines;
    lines = nullptr;

    if (does_user_exists)
    {
        cout << "umer did this" << endl;
    }
    else
    {
        string row = user.name + ',' + user.password + ',' + user.number + ',' + to_string(user.balance) + '\n';

        complete_table += row;
    }

    complete_table += terminator;

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
    string *arr = new string[arr_length + 1];
    int arr_counter = 0;
    string one_string = "";
    for (int i = 0; i < str.length(); i++)
    {
        if (str[i] == separator)
        {
            arr[arr_counter] = one_string;
            arr_counter++;
            // reset the string
            one_string = "";
        }
        else
        {
            one_string += str[i];
        }
    }
    arr[arr_counter] = one_string;

    return arr;
}

string get_all_tables()
{
    // getting the table
    ifstream input("data.csv");

    string terminator = "------";
    string all_tables = "";
    string current_line;

    while (getline(input, current_line) && current_line != terminator)
    {
        all_tables += current_line;
        all_tables += '\n';
    }

    input.close();

    return all_tables;
}

string get_table(string name)
{
    string all_tables = get_all_tables();
    string table_terminator = "---";

    string table = "";
    for (int i = 0; i < all_tables.length(); i++)
    {
        if (all_tables.length() > name.length())
        {
            // there is a chance that that table will exist
        }
    }
}
