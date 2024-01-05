#include <iostream>
#include <fstream>

using namespace std;

void create_schema(string name, int length, string values[])
{
    string content = name + "\n";
    for (int i = 0; i < length; i++)
    {
        content += (values[i] + ",");
    }
    content += "\n";
    ofstream file("data.csv");
    file << content;
    file.close();
}

int main()
{
    string name = "users";
    int length = 3;
    string values[length] = {"name", "phone_number", "balance"};

    create_schema(name, length, values);
    return 0;
}
