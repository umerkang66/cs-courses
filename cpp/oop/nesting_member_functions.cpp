#include <iostream>
#include <string>
using namespace std;

class Binary
{
private:
    string s;
    void chk_bin(void)
    {
        for (int i = 0; i < s.length(); i++)
        {
            if (s.at(i) != '0' && s.at(i) != '1')
            {
                cout << "Incorrect binary format" << endl;
                exit(1);
            }
        }
    }

public:
    void read(void)
    {
        cout << "Enter a binary number: ";
        cin >> s;
    }

    void show(void)
    {
        cout << s << endl;
    }

    void ones_compliment(void)
    {
        chk_bin();
        for (int i = 0; i < s.length(); i++)
        {
            if (s.at(i) == '0')
            {
                s.at(i) = '1';
            }
            else if (s.at(i) == '1')
            {
                s.at(i) = '0';
            }
        }
    }
};

int main(int argc, char const *argv[])
{
    Binary binary;
    binary.read();
    binary.show();
    binary.ones_compliment();
    binary.show();
    return 0;
}
