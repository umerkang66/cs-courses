#include <iostream>
#include <vector>
using namespace std;

struct GraphicObject
{
  virtual void draw() = 0;
};

struct Circle : GraphicObject
{
  void draw() override
  {
    cout << "Circle" << endl;
  }
};

struct Group : GraphicObject
{
  string name;
  vector<GraphicObject *> objects;

  Group(const string &name) : name{name} {}

  void draw() override
  {
    cout << "Group " << name << " contains:" << endl;
    for (auto &&o : objects)
      o->draw();
  }

  void add_object(GraphicObject *obj)
  {
    objects.push_back(obj);
  }
};

int main()
{
  Group root("root");
  Circle c1, c2;
  root.add_object(&c1);

  Group subgroup("sub");
  subgroup.add_object(&c2);

  root.add_object(&subgroup);

  root.draw();
}
