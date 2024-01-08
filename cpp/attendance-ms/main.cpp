#include <iostream>
#include <string>
#include <fstream>

using namespace std;

const int char_length = 50;

int main()
{
    // CONTROL TO REGISTRAR
    char areStudentsAvailable;
    cout << "Do you have the data? (y/n) ";
    cin >> areStudentsAvailable;

    if (areStudentsAvailable == 'n' || areStudentsAvailable == 'N')
    {
        int total_students_length;
        cout << "How many students there are: ";
        cin >> total_students_length;

        char class_name[char_length];
        cout << "Name of the class: ";
        cin >> class_name;

        char students[total_students_length - 1][char_length];

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

        // ADDING THE STUDENTS TO DATA.TXT
        ofstream output("data.txt");
        string answer = "";
        for (int i = 0; *students[i] != '\0'; i++)
        {
            answer += (students[i] + string(","));
        }
        output << answer;
        output.close();
    }
    else
    {
        ifstream input("data.txt");
        char raw_user_data[200];
        // backslash 0 means where to stop adding data into raw_user_data from input stream
        // if we add backslash 0, it will also add the next line
        input.getline(raw_user_data, 200);
        input.close();

        int how_many_students = 0;
        for (int i = 0; raw_user_data[i] != '\0'; i++)
        {
            if (raw_user_data[i] == ',')
            {
                how_many_students++;
            }
        }

        // now we know how many students there are
        // so make an array of that students
        // +1 for the NULL CHAR
        char retrieved_students[how_many_students][char_length];
        int row_counter = 0;
        int column_counter = 0;

        for (int i = 0; raw_user_data[i] != '\0'; i++)
        {
            if (raw_user_data[i] == ',')
            {
                // we also have to add the '\0' at the last column of previous row
                retrieved_students[row_counter][column_counter] = '\0';

                // going to the next string (row) in array
                row_counter++;
                column_counter = 0;
            }
            else
            {
                // going to the next index (column) in same string (row)
                retrieved_students[row_counter][column_counter] = raw_user_data[i];
                column_counter++;
            }
        }
        // at the very LAST row and very FIRST column, add the NULL CHAR
        retrieved_students[row_counter][column_counter] = '\0';

        // we have populated the array
        // CONTROL TO TEACHER
        cout << endl;
        cout << "Here are the names of students" << endl;
        cout << "If they are present enter 'p', otherwise 'a'" << endl;

        // make the attendance array
        int isPresent[how_many_students];
        // populating it with garbage value (-1)
        for (int i = 0; i < how_many_students; i++)
        {
            isPresent[i] = -1;
        }

        for (int i = 0; retrieved_students[i][0] != '\0'; i++)
        {
            cout << retrieved_students[i] << " (p/a)? ";
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
        cout << endl;

        // CONTROL TO STUDENT
        for (int i = 0; retrieved_students[i][0] != '\0'; i++)
        {
            string message;
            if (isPresent[i] == 1)
            {
                message = "PRESENT";
            }
            else if (isPresent[i] == 0)
            {
                message = "ABSENT";
            }
            else
            {
                message = "ATTENDANCE NOT MARKED";
            }
            cout << retrieved_students[i] << " is " << message << endl;
        }
    }

    return 0;
}
