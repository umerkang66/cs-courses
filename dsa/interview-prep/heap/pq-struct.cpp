#include <iostream>
#include <queue>
using namespace std;

struct Student
{
  string name;
  int marks;

  Student(string name, int marks) : name(name), marks(marks) {}

  bool operator<(const Student &obj) const { return this->marks < obj.marks; }
};

int main()
{
  priority_queue<Student> pq;

  pq.push(Student{"Umer", 88});
  pq.push(Student{"Gulzar", 75});
  pq.push(Student{"Ali", 92});

  while (!pq.empty())
  {
    cout << "Name: " << pq.top().name << ", Marks: " << pq.top().marks << endl;
    pq.pop();
  }

  return 0;
}
