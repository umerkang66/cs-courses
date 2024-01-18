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

struct Transaction
{
    string from;
    string to;
    int amount;
};

const string table_terminator = "---";
const string database_terminator = "------";

// APPLICATION FUNCTIONS
void authenticate();
User create_user();
void signup_user();
User *get_users();
User *add_user_all_users(User user);
void save_all_users(User *users);
Transaction *get_transactions();

// UTILITY FUNCTIONS
string *split(string str, char separator);
string get_all_tables();
string get_table(string name);
void save_table(string rows, string name);

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
    User *users = add_user_all_users(user);
    // saving all the users
    save_all_users(users);
    delete[] users;

    // set the current_user to this user
    current_user = user;
}

User *add_user_all_users(User user)
{
    // getting the users
    User *users = get_users();
    // finding the length
    int length = 0;
    for (int i = 0; users[i].name != table_terminator; i++)
    {
        length++;
    }
    // make new array and copy all the elements in the new array
    // +1 is for the new user
    // and +1 is for the new terminator string
    User *new_users = new User[length + 2];
    int i;
    for (i = 0; users[i].name != table_terminator; i++)
    {
        new_users[i].name = users[i].name;
        new_users[i].password = users[i].password;
        new_users[i].number = users[i].number;
        new_users[i].balance = users[i].balance;
    }
    // adding the latest added user
    new_users[i].name = user.name;
    new_users[i].password = user.password;
    new_users[i].number = user.number;
    new_users[i].balance = user.balance;

    new_users[++i].name = table_terminator;

    // delete the old heap array
    delete[] users;

    return new_users;
}

void save_all_users(User *users)
{
    // first we have create all the rows
    string rows = "users\nname,password,phone_number,balance";
    for (int i = 0; users[i].name != table_terminator; i++)
    {
        string row = users[i].name + ',' + users[i].password + ',' + users[i].number + ',' + to_string(users[i].balance);
        rows += '\n' + row;
    }
    rows += '\n';

    save_table(rows, "users");
}

void save_all_transactions(Transaction *transactions)
{
    // first we have create all the rows
    string rows = "transactions\nfrom,to,amount";
    for (int i = 0; transactions[i].from != table_terminator; i++)
    {
        string row = transactions[i].from + ',' + transactions[i].to + ',' + to_string(transactions[i].amount);
        rows += '\n' + row;
    }
    rows += '\n';

    save_table(rows, "transactions");
}

// this will return the heap array, make sure to DEALLOCATE it
User *get_users()
{
    string user_table = get_table("users");
    int length = 0;

    string *lines = split(user_table, '\n');
    for (int i = 2; lines[i][0] != '\0'; i++)
    {
        length++;
    }
    // +1 is for the terminator character
    User *users = new User[length + 1];
    int users_counter = 0;

    for (int i = 2; lines[i][0] != '\0'; i++)
    {
        // for every create an array by ',' separator
        string *fields = split(lines[i], ',');
        users[users_counter].name = fields[0];
        users[users_counter].password = fields[1];
        users[users_counter].number = fields[2];
        users[users_counter].balance = stoi(fields[3]);
        users_counter++;

        delete[] fields;
        fields = nullptr;
    }

    users[users_counter].name = table_terminator;

    delete[] lines;
    lines = nullptr;

    return users;
}

// this will return the heap array, make sure to DEALLOCATE it
Transaction *get_transactions()
{
    string transaction_table = get_table("transactions");

    int length = 0;
    string *lines = split(transaction_table, '\n');
    for (int i = 2; lines[i][0] != '\0'; i++)
    {
        length++;
    }
    // +1 is for the terminator character
    Transaction *transactions = new Transaction[length + 1];
    int transactions_counter = 0;

    for (int i = 2; lines[i][0] != '\0'; i++)
    {
        // for every create an array by ',' separator
        string *fields = split(lines[i], ',');
        transactions[transactions_counter].from = fields[0];
        transactions[transactions_counter].to = fields[1];
        transactions[transactions_counter].amount = stoi(fields[2]);
        transactions_counter++;

        delete[] fields;
        fields = nullptr;
    }

    transactions[transactions_counter].from = table_terminator;

    delete[] lines;
    lines = nullptr;

    return transactions;
}

// UTILITY FUNCTIONS
// This will split the string into an array by using the separator
string *split(string str, char separator)
{
    int arr_length = 0;
    for (int i = 0; i < str.length(); i++)
    {
        if (str[i] == separator)
        {
            arr_length++;
        }
    }

    // make an array of that length in the HEAP memory
    // make sure the DEALLOCATE this memory after using it
    // +2: +1 is for there is one more word than separator
    // +1 is for terminator string character
    string *arr = new string[arr_length + 2];
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
    arr[++arr_counter][0] = '\0';

    return arr;
}

string get_all_tables()
{
    // getting the table
    ifstream input("data.db");

    string all_tables = "";
    string current_line;

    while (getline(input, current_line) && current_line != table_terminator)
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

    // to check if all the characters of name are in
    // all_tables create an array
    bool all_chars_of_name_in_all_tables[name.length()];
    // initialize it with 0
    for (int i = 0; i < name.length(); i++)
    {
        all_chars_of_name_in_all_tables[i] = 0;
    }
    int table_starting_index = -1;

    for (int i = 0; i < all_tables.length(); i++)
    {
        if (all_tables.length() > name.length())
        {
            // there is a chance that that table will exist
            for (int j = 0; j < name.length(); j++)
            {
                if (all_tables[i + j] == name[j])
                {
                    all_chars_of_name_in_all_tables[j] = 1;
                }
            }

            // check if the word is found
            bool is_word_found = true;
            for (int i = 0; i < name.length(); i++)
            {
                if (all_chars_of_name_in_all_tables[i] == 0)
                {
                    is_word_found = false;
                }
            }

            // if all the characters are found
            if (is_word_found)
            {
                // store the starting index
                table_starting_index = i;
                // and break the loop
                break;
            }
            else
            {
                // reset the values
                for (int i = 0; i < name.length(); i++)
                {
                    all_chars_of_name_in_all_tables[i] = 0;
                }
            }
        }
    }

    if (table_starting_index == -1)
    {
        return "not found";
    }

    string table = "";
    int i = table_starting_index;
    // check for terminator
    while (i < all_tables.length())
    {
        table += all_tables[i];
        bool chars_of_terminator_found[3] = {0, 0, 0};
        for (int j = i + 1; j <= i + 3; j++)
        {
            if (all_tables[j] == '-')
            {
                chars_of_terminator_found[j - i - 1] = 1;
            }
        }
        bool is_found = true;
        for (int i = 0; i < 3; i++)
        {
            if (chars_of_terminator_found[i] == 0)
            {
                is_found = false;
            }
        }
        if (is_found)
        {
            break;
        }
        i++;
    }
    return table;
}

void save_table(string rows, string name)
{
    string database = get_all_tables();
    string table_terminator = "---";

    // to check if all the characters of name are in
    // all_tables create an array
    bool all_chars_of_name_in_all_tables[name.length()];
    // initialize it with 0
    for (int i = 0; i < name.length(); i++)
    {
        all_chars_of_name_in_all_tables[i] = 0;
    }
    int table_starting_index = -1;

    for (int i = 0; i < database.length(); i++)
    {
        if (database.length() > name.length())
        {
            // there is a chance that that table will exist
            for (int j = 0; j < name.length(); j++)
            {
                if (database[i + j] == name[j])
                {
                    all_chars_of_name_in_all_tables[j] = 1;
                }
            }

            // check if the word is found
            bool is_word_found = true;
            for (int i = 0; i < name.length(); i++)
            {
                if (all_chars_of_name_in_all_tables[i] == 0)
                {
                    is_word_found = false;
                }
            }

            // if all the characters are found
            if (is_word_found)
            {
                // store the starting index
                table_starting_index = i;
                // and break the loop
                break;
            }
            else
            {
                // reset the values
                for (int i = 0; i < name.length(); i++)
                {
                    all_chars_of_name_in_all_tables[i] = 0;
                }
            }
        }
    }

    if (table_starting_index == -1)
    {
        return;
    }

    // find the starting index (already found)
    int start = table_starting_index;
    // find the ending index (where is terminator '---')
    int end = -1;
    for (int i = 0; i < database.length(); i++)
    {
        bool chars_of_terminator_found[3] = {0, 0, 0};
        for (int j = i + 1; j <= i + 3; j++)
        {
            if (database[j] == '-')
            {
                chars_of_terminator_found[j - i - 1] = 1;
            }
        }
        bool is_found = true;
        for (int i = 0; i < 3; i++)
        {
            if (chars_of_terminator_found[i] == 0)
            {
                is_found = false;
            }
        }
        if (is_found)
        {
            end = i;
            break;
        }
    }

    // for new database we wants to remove the database content from start to end
    // and add the new rows instead of this
    string new_database = "";
    for (int i = 0; i < start; i++)
    {
        // add everything from 0 index to start of removal content
        new_database += database[i];
    }
    // now add the new rows
    for (int i = 0; i < rows.length(); i++)
    {
        new_database += rows[i];
    }
    // now add the database after the end
    for (int i = end + 1; i < database.length(); i++)
    {
        new_database += database[i];
    }

    // database terminator
    new_database += database_terminator;
    cout << new_database << endl;

    // ofstream output("data.db");
    // output << new_database;
    // output.close();
}
