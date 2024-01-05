#include <iostream>
using namespace std;

void create_schema(string name, char values[3][15])
{
}

int main()
{
    char values[][15] = {"name", "phone_number", "balance"};

    create_schema("users", values);
    return 0;
}
