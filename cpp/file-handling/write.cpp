#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    // Writing text to a file
    string st = "this is from constructor\nthis is from constructor\nthis is from constructor\nthis is from constructor\nthis is from constructor\n-- ";
    ofstream out("file.txt");
    out << st;

    return 0;
}
