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

    for (int i = 0; i < total_students_length; i++)
    {
        for (int j = 0; students[i][j] != '\0'; j++)
        {
            // Process or print the valid data
            printf("%c", students[i][j]);
        }
        printf("\n"); // Move to the next line after each row
    }

    return 0;
}
