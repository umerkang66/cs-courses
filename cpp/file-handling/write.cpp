#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    // opening files using constructor
    string st;
    ofstream out("file.txt");
    out << st;

    return 0;
}
