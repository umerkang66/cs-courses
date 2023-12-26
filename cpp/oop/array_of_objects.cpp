#include <iostream>
using namespace std;

class Employee
{
private:
    int id;
    int salary;
    void setData(int idInput, int salaryInput)
    {
        id = idInput;
        salary = salaryInput;
    }

public:
    void getData(void) { cout << "ID: " << id << "  SALARY: " << salary << endl; }
    static Employee createEmployee(Employee employee, int id, int salary)
    {
        employee.setData(id, salary);
        return employee;
    }
};

int main(int argc, char const *argv[])
{
    int length = 100;
    Employee employees[length];
    for (int i = 0; i < length; i++)
    {
        employees[i] = Employee::createEmployee(employees[i], i + 1, (i + 1) * 1000);
    }
    for (int i = 0; i < length; i++)
    {
        employees[i].getData();
    }
    return 0;
}
