#include <iostream>

using namespace std;

int main()
{
    // CONTROL TO REGISTRAR
    int class_name_length = 50;
    char class_name[class_name_length];
    cout << "Name of the class: ";
    cin.getline(class_name, class_name_length);

    int total_students_length = 100;
    char students[total_students_length][50];
    char isPresent[total_students_length];
    for (int i = 0; i < total_students_length; i++)
    {
        // entering the garbage value
        // present ==> 1
        // absent  ==> 0
        isPresent[i] = -1;
    }

    int counter = 0;
    char yesOrNo;

    cout << "Enter the name of the student: ";
    cin >> students[counter];
    cout << "Do you want to add more students? (y/n) ";
    cin >> yesOrNo;

    while (yesOrNo == 'y' || yesOrNo == 'Y')
    {
        cout << endl;
        cout << "Enter the name of the student: ";
        cin >> students[++counter];
        cout << "Do you want to add more students? (y/n) ";
        cin >> yesOrNo;
    }

    // CONTROL TO TEACHER
    cout << endl;
    cout << "Here are the names of students" << endl;
    cout << "If they are present enter 'p', otherwise 'a'" << endl;

    for (int i = 0; *students[i] != '\0'; i++)
    {
        cout << students[i] << " (p/a)? ";
        char answer;
        cin >> answer;
        if (answer == 'p')
        {
            isPresent[i] = 1;
        }
        else if (answer == 'a')
        {
            isPresent[i] = 0;
        }
        else
        {
            isPresent[i] = -1;
        }
    }

    // CONTROL TO STUDENT
    for (int i = 0; *students[i] != '\0'; i++)
    {
        string message;
        if (isPresent[i]==1)
        {
            message = "PRESENT";
        }
        else if (isPresent[i]==0)
        {
            message = "ABSENT";
        }
        else
        {
            message = "ATTENDANCE NOT MARKED";
        }
        cout << students[i] << " is " << message << endl;
    }

    return 0;
}
