#include <iostream>
using namespace std;

class Employee
{
private:
    int id;
    // static data members
    static int count;
    string name;

public:
    void setData(void)
    {
        cout << "Enter the id: ";
        cin >> id;
        cout << "Enter the name: ";
        cin >> name;
        count++;
    }
    void getData(void)
    {
        cout << id << ": " << name << endl;
    }
    static void getCount(void)
    {
        cout << "The total employees are: " << count << endl;
    }
    static Employee createEmployee(void)
    {
        Employee employee;
        employee.setData();
        return employee;
    }
};

int Employee::count = 0;

int main(int argc, char const *argv[])
{
    Employee umer = Employee::createEmployee();
    Employee kang = Employee::createEmployee();
    Employee gulzar = Employee::createEmployee();

    umer.getData();
    kang.getData();
    gulzar.getData();

    Employee::getCount();
    return 0;
}
