#include <iostream>
using namespace std;

class Person
{
protected:
    string name;
    int age;

public:
    Person(string _name, int _age)
    {
        name = _name;
        age = _age;
    }
};

// class Student : public Person
// default: class Student: private Person
class Student : Person
{
    string subject;

public:
    Student(string _name, int _age, string _subject) : Person(_name, _age)
    {
        subject = _subject;
    }

    void introduce(void)
    {
        cout << "My name is " << name << ". I am " << age << " years old, and studying " << subject << endl;
    }
};

int main()
{
    Student umer("umer", 20, "computer science");
    umer.introduce();

    return 0;
}
