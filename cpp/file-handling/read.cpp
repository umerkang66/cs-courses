#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    string st;
    string st2;

    // reading files using constructor and reading it
    ifstream in("file.txt");
    getline(in, st2);
    st += st2;
    while (st2 != "--")
    {
        getline(in, st2);
        st += "\n" + st2;
    }

    cout << st << endl;

    return 0;
}
