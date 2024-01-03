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

        char students[total_students_length-1][char_length];

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
            if (i == 0)
            {
                answer += students[i];
            }
            else
            {
                answer += string(",") + students[i];    
            }
        }
        output << answer;
        output.close();
    }
    else
    {
        ifstream input("data.txt");
        string raw_user_data;
        getline(input, raw_user_data);
        input.close();

        int how_many_students = 0;
        int counter = 0;
        char curr_char = raw_user_data[counter];
        while (curr_char != '\0')
        {
            if (curr_char == ',')
            {
                how_many_students++;
            }
            curr_char = raw_user_data[++counter];
        }

        // now we know how many students there are
        // so make an array of that students
        char retreived_students[how_many_students][char_length];
        int retreived_students_counter = 0;
        int single_student_counter = 0;

        counter = 0;
        curr_char = raw_user_data[counter];
        while (curr_char != '\0')
        {
            if (curr_char == ',')
            {
                retreived_students_counter++;
                single_student_counter = 0;
            }
            else
            {
                retreived_students[retreived_students_counter][single_student_counter] = curr_char;
                single_student_counter++;
            }

            curr_char = raw_user_data[++counter];
        }

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

        for (int i = 0; *retreived_students[i] != '\0'; i++)
        {
            cout << retreived_students[i] << " (p/a)? ";
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
        for (int i = 0; *retreived_students[i] != '\0'; i++)
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
            cout << retreived_students[i] << " is " << message << endl;
        }
    }

    return 0;
}
