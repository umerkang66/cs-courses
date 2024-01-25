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
int authenticate();
User create_user();
void signup_user();
void signin_user();
User *get_users();
User *add_user_to_all_users(User user);
void save_all_users(User *users);
Transaction *get_transactions();
void save_all_transactions(Transaction *transactions);
void start_app();
void render_user_information();
int show_and_get_answer();
void logout();
void show_history();
Transaction *get_transactions_of_user(string user_number);
User get_user_by_number(string user_number);

// UTILITY FUNCTIONS
string *split(string str, char separator);
string get_all_tables();
string get_table(string name);
int str_len(string str);
void save_table(string rows, string name);
int str_include_start(string str, string check);
int str_include_end(int starting_index, string str, string check);

User *current_user = new User;

int main()
{
    // This will prompt the user to signIn or signUp
    // and will set the current user
    int status = authenticate();
    while (status != 0)
    {
        cout << endl;
        status = authenticate();
    }

    // move forward with the application
    start_app();

    return 0;
}

void start_app()
{
    render_user_information();
    int answer = -1;
    while (answer != 0)
    {
        answer = show_and_get_answer();
        if (answer == 1)
        {
            // handle transfer amount
        }
        else if (answer == 2)
        {
            show_history();
        }
        else if (answer == 3)
        {
            render_user_information();
        }
    }

    logout();
}

void show_history()
{
    cout << endl;
    Transaction *transactions = get_transactions_of_user(current_user->number);

    delete[] transactions;
    transactions = nullptr;
}

void logout()
{
    cout << "You are logged out successfully" << endl;
    exit(0);
}

int show_and_get_answer()
{
    cout << endl;
    cout << "1: Transfer amounts" << endl;
    cout << "2: Show history" << endl;
    cout << "3: My account" << endl;
    cout << "0: Exit" << endl;
    int n;
    cout << "Enter number: ";
    cin >> n;

    while (n < 0 && n > 3)
    {
        cout << "Please enter between 1 and 3: ";
        cin >> n;
    }
    return n;
}

void render_user_information()
{
    string introduction = current_user->name + "  Balance: " + to_string(current_user->balance) + " Rs.";
    if (str_len(introduction) % 2 == 0)
    {
        introduction.replace(introduction.find('.'), 1, "");
    }

    cout << endl;
    // generating a reasonably good looking pattern
    int line_length = str_len(introduction) + 6;
    for (int i = 1; i <= 5; i++)
    {
        string line = "";
        // if i == 3 don't generate patterns
        if (i == 3)
        {
            // render the user information here
            line += "#  " + introduction + "  #";
        }
        else
        {
            for (int j = 1; j <= line_length; j++)
            {
                if ((i == 1 || i == 5 || j == 1 || j == line_length) && j % 2 != 0)
                {
                    line += "#";
                }
                else
                {
                    line += " ";
                }
            }
        }
        cout << line << endl;
    }
}

int authenticate()
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
        signin_user();
    }
    else
    {
        // USER WANTS TO SIGNUP
        signup_user();
    }

    // AFTER SIGNING IN OR SIGNING UP, CURRENT_USER WILL BE SETUP
    // IF CURRENTUSER IS NOT AVAILABLE, MEANS SOMETHING WENT WRONG
    if (current_user->number.empty())
    {
        cout << "You are not authenticated" << endl;
        return 1;
    }
    return 0;
}

void signin_user()
{
    string number;
    string password;
    cout << "Enter your number: ";
    getline(cin, number);
    cout << "Enter your password: ";
    getline(cin, password);

    User *users = get_users();
    for (int i = 0; users[i].name != table_terminator; i++)
    {
        if (users[i].number == number && users[i].password == password)
        {
            *current_user = users[i];
            cout << "Congratulations You are Signed In" << endl;
            delete[] users;
            return;
        }
    }
    delete[] users;
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
    User *users = add_user_to_all_users(user);
    // saving all the users
    save_all_users(users);
    delete[] users;

    cout << "Congratulations you are Signed Up" << endl;
    // set the current_user to this user
    *current_user = user;
}

User *add_user_to_all_users(User user)
{
    // getting the users from db
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
User get_user_by_number(string user_number)
{
    User *users = get_users();
    User found_user;
    for (int i = 0; users[i].name != table_terminator; i++)
    {
        if (users[i].number == user_number)
        {
            found_user = users[i];
        }
    }
    return found_user;
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

Transaction *get_transactions_of_user(string user_number)
{
    Transaction *transactions = get_transactions();
    int length = 0;
    for (int i = 0; transactions[i].from != table_terminator; i++)
    {
        length++;
    }
    // +1 for the table terminator
    Transaction *user_transactions = new Transaction[length + 1];
    int counter = 0;
    for (int i = 0; transactions[i].from != table_terminator; i++)
    {
        if (transactions[i].from == user_number)
        {
            user_transactions[counter] = transactions[i];
            counter++;
        }
    }
    // add the table terminator in the from property
    user_transactions[counter].from = table_terminator;
    delete[] transactions;
    transactions = nullptr;
    return user_transactions;
}

// UTILITY FUNCTIONS
// This will split the string into an array by using the separator
string *split(string str, char separator)
{
    int arr_length = 0;
    for (int i = 0; str[i] != '\0'; i++)
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
    for (int i = 0; str[i] != '\0'; i++)
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

    while (getline(input, current_line) && current_line != database_terminator)
    {
        all_tables += current_line;
        all_tables += '\n';
    }

    input.close();

    // if schema doesn't exist create the schema
    // and write it to the db
    int does_schemas_exists = str_include_start(all_tables, table_terminator);

    if (does_schemas_exists == -1)
    {
        // there is no db file, first populate the db file with
        // appropriate data and and return that data
        // first reset the value
        all_tables = "users\nname,password,phone_number,balance\n" + table_terminator + "\ntransactions\nfrom,to,amount\n" + table_terminator + "\n" + database_terminator;

        ofstream output("data.db");
        output << all_tables;
        output.close();
    }

    return all_tables;
}

int str_len(string str)
{
    int length = 0;
    for (int i = 0; str[i] != '\0'; i++)
    {
        length++;
    }
    return length;
}

int str_include_start(string str, string check)
{
    // this will return -1, if it doesn't include
    // the check string, otherwise it will return the index
    int check_length = str_len(check);
    bool all_chars_in_str[check_length];
    // initialize it with 0
    for (int i = 0; i < check_length; i++)
    {
        all_chars_in_str[i] = 0;
    }
    int check_starting_index = -1;

    for (int i = 0; str[i] != '\0'; i++)
    {
        // there is a chance that that table will exist
        for (int j = 0; j < check_length; j++)
        {
            if (str[i + j] == check[j])
            {
                all_chars_in_str[j] = 1;
            }
        }

        // check if the word is found
        bool is_word_found = true;
        for (int i = 0; i < check_length; i++)
        {
            if (all_chars_in_str[i] == 0)
            {
                is_word_found = false;
            }
        }

        // if all the characters are found
        if (is_word_found)
        {
            // store the starting index
            check_starting_index = i;
            // and break the loop
            break;
        }
        else
        {
            // reset the values
            for (int i = 0; i < check_length; i++)
            {
                all_chars_in_str[i] = 0;
            }
        }
    }

    return check_starting_index;
}

int str_include_end(int starting_index, string str, string check)
{
    int end = -1;
    int check_length = str_len(check);

    for (int i = starting_index; str[i] != '\0'; i++)
    {
        bool chars_of_check_found[check_length];
        for (int i = 0; i < check_length; i++)
        {
            // initialize every value with 0 means not found
            chars_of_check_found[i] = 0;
        }
        int chars_check_counter = 0;
        for (int j = i; j < i + check_length; j++)
        {
            if (str[j] == check[j - i])
            {
                chars_of_check_found[chars_check_counter] = 1;
                chars_check_counter++;
            }
        }
        bool is_found = true;
        for (int i = 0; i < check_length; i++)
        {
            if (chars_of_check_found[i] == 0)
            {
                is_found = false;
            }
        }
        if (is_found)
        {
            end = i + check_length - 1;
            break;
        }
    }
    return end;
}

string get_table(string name)
{
    string all_tables = get_all_tables();
    int table_starting_index = str_include_start(all_tables, name);

    if (table_starting_index == -1)
    {
        return "not found";
    }

    string table = "";
    int i = table_starting_index;
    // check for terminator
    while (all_tables[i] != '\0')
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
    int table_starting_index = str_include_start(database, name);

    if (table_starting_index == -1)
    {
        return;
    }

    // find the starting index (already found)
    int start = table_starting_index;
    // find the ending index of table terminator (where is terminator '---' ends)
    int end = str_include_end(start, database, table_terminator);

    // for new database we wants to remove the database content from start to end
    // and add the new rows instead of this
    string new_database = "";
    for (int i = 0; i < start; i++)
    {
        // add everything from 0 index to start of removal content
        new_database += database[i];
    }
    // now add the new rows
    for (int i = 0; rows[i] != '\0'; i++)
    {
        new_database += rows[i];
    }
    // after adding the rows also the table-terminator
    // end + 1 is actually a '\n' character so we don't need to add it
    new_database += table_terminator;
    // now add the database after the end
    for (int i = end + 1; database[i] != '\0'; i++)
    {
        new_database += database[i];
    }

    // database terminator
    new_database += database_terminator;

    ofstream output("data.db");
    output << new_database;
    output.close();
}
