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

const string terminator = "---";
const string database_terminator = "------";
string logged_out_number = "-1";

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
void transfer_amount();
int get_user_index_by_number(string user_number);

// UTILITY FUNCTIONS
string *split(string str, char separator);
string get_all_tables();
string get_table(string name);
int str_len(string str);
void save_table(string rows, string name);
int str_include_start(string str, string check);
int str_include_end(int starting_index, string str, string check);
void show_as_table(string **matrix, int rows, int cols);
void clear();
string to_upper(string);
string to_lower(string);

// adding the default empty user
User default_user = {"", "", logged_out_number, 0};
User current_user = default_user;

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

    clear();

    // move forward with the application
    start_app();

    return 0;
}

void clear()
{
    // if the operating system is windows
// then run this
#ifdef _WIN32
    system("cls");
#else
    // if operating system is unix or linux, run this
    system("clear");
#endif
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
            transfer_amount();
        }
        else if (answer == 2)
        {
            show_history();
        }
        else if (answer == 3)
        {
            render_user_information();
        }
        else if (answer == 4)
        {
            logout();
            // return because logout will start the new application
            return;
        }
    }

    exit(0);
}

void transfer_amount()
{
    cout << endl;
    cout << "Enter the number of receiver: ";
    string n;
    cin >> n;

    while (n == current_user.number)
    {
        cout << "HAHA - NICE TRY! You can't send money to your self 😜" << endl;
        cout << "Enter the number of receiver: ";
        cin >> n;
    }

    User *users = get_users();
    int receiver_index = get_user_index_by_number(n);
    int sender_index = get_user_index_by_number(current_user.number);

    while (receiver_index == -1)
    {
        cout << "This user does not exists" << endl;
        cout << endl;
        cout << "Enter the number of receiver: ";
        cin >> n;
        receiver_index = get_user_index_by_number(n);
    }

    int amount;
    cout << "Enter amount to transfer: ";
    cin >> amount;
    cout << endl;
    cout << "Do you want to transfer Rs. " << amount << " to " << to_upper(users[receiver_index].name) << " (y/n): ";
    char answer;
    cin >> answer;

    while (answer != 'y' && answer != 'Y' && answer != 'n' && answer != 'N')
    {
        cout << "Only (y/n) are permitted: ";
        cin >> answer;
    }

    if (users[sender_index].balance >= amount)
    {
        // sender can send the data
        users[receiver_index].balance += amount;
        users[sender_index].balance -= amount;
        // also update the current user
        current_user = users[sender_index];

        // getting all the transactions
        Transaction *transactions = get_transactions();
        // also create a transaction
        Transaction new_transaction;
        new_transaction.from = users[sender_index].number;
        new_transaction.to = users[receiver_index].number;
        new_transaction.amount = amount;

        int length = 0;
        for (int i = 0; transactions[i].from != terminator; i++)
        {
            length++;
        }

        // make new array and copy all the elements in the new array
        // +1 is for the new transaction
        // and +1 is for the new terminator string
        Transaction *new_transactions = new Transaction[length + 2];
        int i;
        for (i = 0; transactions[i].from != terminator; i++)
        {
            new_transactions[i].from = transactions[i].from;
            new_transactions[i].to = transactions[i].to;
            new_transactions[i].amount = transactions[i].amount;
        }
        // adding the latest added transaction
        new_transactions[i].from = new_transaction.from;
        new_transactions[i].to = new_transaction.to;
        new_transactions[i].amount = new_transaction.amount;

        new_transactions[++i].from = terminator;

        // save in database
        save_all_users(users);
        save_all_transactions(new_transactions);

        delete[] transactions;
        delete[] new_transactions;

        cout << endl;
        cout << "Money is sent successfully ✔️" << endl;
    }
    else
    {
        cout << "You don't have enough balance 😢" << endl;
    }

    delete[] users;
}

void show_history()
{
    cout << endl;
    Transaction *transactions = get_transactions_of_user(current_user.number);

    int length = 0;
    for (int i = 0; transactions[i].from != terminator; i++)
    {
        length++;
    }

    // from to amount
    // because there are only three properties
    int rows = length + 1;
    int cols = 7;
    string **matrix = new string *[length + 1];
    for (int i = 0; i < length + 1; i++)
    {
        matrix[i] = new string[cols];
    }

    matrix[0][0] = "Sr.";
    matrix[0][1] = "Sender No.";
    matrix[0][2] = "Sender";
    matrix[0][3] = "Receiver No.";
    matrix[0][4] = "Receiver";
    matrix[0][5] = "Amount";
    matrix[0][6] = "Payment Status";
    int i;
    for (i = 0; transactions[i].from != terminator; i++)
    {
        // to go from last to the first, first i should go to last
    }
    // it is out of index
    // move left the index to the last element
    i--;
    int row_counter = 1;
    while (i >= 0)
    {
        Transaction t = transactions[i];
        matrix[row_counter][0] = to_string(row_counter);
        matrix[row_counter][1] = t.from;
        matrix[row_counter][2] = get_user_by_number(t.from).name;
        matrix[row_counter][3] = t.to;
        matrix[row_counter][4] = get_user_by_number(t.to).name;
        matrix[row_counter][5] = to_string(t.amount) + " Rs.";
        matrix[row_counter][6] = t.from == current_user.number ? "Sent" : "Received";
        i--;
        row_counter++;
    }

    // make a matrix then pass it to the show_as_table function
    show_as_table(matrix, rows, cols);

    // deallocating the memory
    for (int i = 0; i < length + 1; ++i)
    {
        delete[] matrix[i];
    }
    delete[] matrix;

    delete[] transactions;
}

void show_as_table(string **matrix, int rows, int cols)
{
    // Calculate the maximum length of strings in each column
    int max_col_lengths[cols];
    for (int i = 0; i < cols; i++)
    {
        max_col_lengths[i] = 0;
        for (int j = 0; j < rows; j++)
        {
            int len = str_len(matrix[j][i]);
            if (len > max_col_lengths[i])
            {
                max_col_lengths[i] = len;
            }
        }
    }

    // Display the table
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            cout << "+-" << string(max_col_lengths[j], '-') << "-";
        }
        cout << "+" << endl;

        for (int j = 0; j < cols; j++)
        {
            cout << "| " << matrix[i][j] << string(max_col_lengths[j] - str_len(matrix[i][j]), ' ') << " ";
        }
        cout << "|" << endl;
    }

    // Bottom border of the table
    for (int j = 0; j < cols; j++)
    {
        cout << "+-" << string(max_col_lengths[j], '-') << "-";
    }
    cout << "+" << endl;
}

void logout()
{
    current_user = default_user;
    clear();
    cout << "You are logged out successfully 😃" << endl;
    cout << endl;

    // RECURSIVELY calling the main function
    main();
}

int show_and_get_answer()
{
    cout << endl;
    cout << "1: Transfer amounts 💵" << endl;
    cout << "2: Show history 🕰️" << endl;
    cout << "3: My account 📊" << endl;
    cout << "4: Logout 🔓" << endl;
    cout << "0: Exit 🚪" << endl;
    int n;
    cout << "Enter number from above: ";
    cin >> n;

    while (n < 0 || n > 4)
    {
        cout << "Please enter between 1 and 4: ";
        cin >> n;
    }
    return n;
}

void render_user_information()
{
    string introduction = current_user.name + "  Balance: " + to_string(current_user.balance) + " Rs.";
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
    if (current_user.number == logged_out_number)
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
    for (int i = 0; users[i].name != terminator; i++)
    {
        if (users[i].number == number && users[i].password == password)
        {
            current_user = users[i];
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
    user.balance = 100;

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
    current_user = user;
}

User *add_user_to_all_users(User user)
{
    // getting the users from db
    User *users = get_users();
    // finding the length
    int length = 0;
    for (int i = 0; users[i].name != terminator; i++)
    {
        length++;
    }
    // make new array and copy all the elements in the new array
    // +1 is for the new user
    // and +1 is for the new terminator string
    User *new_users = new User[length + 2];
    int i;
    for (i = 0; users[i].name != terminator; i++)
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

    new_users[++i].name = terminator;

    // delete the old heap array
    delete[] users;

    return new_users;
}

void save_all_users(User *users)
{
    // first we have create all the rows
    string rows = "users\nname,password,phone_number,balance";
    for (int i = 0; users[i].name != terminator; i++)
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
    for (int i = 0; transactions[i].from != terminator; i++)
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
    }

    users[users_counter].name = terminator;

    delete[] lines;

    return users;
}

// this will return the heap array, make sure to DEALLOCATE it
User get_user_by_number(string user_number)
{
    User *users = get_users();
    User found_user = default_user;
    for (int i = 0; users[i].name != terminator; i++)
    {
        if (users[i].number == user_number)
        {
            found_user = users[i];
        }
    }
    return found_user;
}

int get_user_index_by_number(string user_number)
{
    User *users = get_users();
    int index = -1;
    for (int i = 0; users[i].name != terminator; i++)
    {
        if (users[i].number == user_number)
        {
            index = i;
        }
    }
    return index;
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
    }

    transactions[transactions_counter].from = terminator;

    delete[] lines;

    return transactions;
}

Transaction *get_transactions_of_user(string user_number)
{
    Transaction *transactions = get_transactions();
    int length = 0;
    for (int i = 0; transactions[i].from != terminator; i++)
    {
        length++;
    }
    // +1 for the table terminator
    Transaction *user_transactions = new Transaction[length + 1];
    int counter = 0;
    for (int i = 0; transactions[i].from != terminator; i++)
    {
        if (transactions[i].from == user_number || transactions[i].to == user_number)
        {
            user_transactions[counter] = transactions[i];
            counter++;
        }
    }
    // add the table terminator in the from property
    user_transactions[counter].from = terminator;
    delete[] transactions;
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
    int does_schemas_exists = str_include_start(all_tables, terminator);

    if (does_schemas_exists == -1)
    {
        // there is no db file, first populate the db file with
        // appropriate data and and return that data
        // first reset the value
        all_tables = "users\nname,password,phone_number,balance\n" + terminator + "\ntransactions\nfrom,to,amount\n" + terminator + "\n" + database_terminator;

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
    int end = str_include_end(start, database, terminator);

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
    new_database += terminator;
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

string to_lower(string str)
{
    string answer = "";
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] >= 65 && str[i] <= 92)
        {
            answer += (char)str[i] + 32;
        }
        else
        {
            answer += str[i];
        }
    }
    return answer;
}

string to_upper(string str)
{
    string answer = "";
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] >= 97 && str[i] <= 122)
        {
            answer += (char)str[i] - 32;
        }
        else
        {
            answer += str[i];
        }
    }
    return answer;
}
