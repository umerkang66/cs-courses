#include <iostream>
#include <sstream>
using namespace std;

struct Shape
{
  virtual string str() const = 0;
};

struct Circle : Shape
{
  float radius;
  Circle(float r) : radius(r) {}
  Circle() {}

  void resize(float factor)
  {
    radius *= factor;
  }

  string str() const override
  {
    ostringstream oss;
    oss << "A circle of radius: " << radius;
    return oss.str();
  }
};

struct Square : Shape
{
  float side;
  Square(float s) : side(s) {}
  Square() {}

  string str() const override
  {
    ostringstream oss;
    oss << "A square with side: " << side;
    return oss.str();
  }
};

// DYNAMIC DECORATOR
struct ColoredShape : Shape
{
  Shape &shape;
  string color;

  ColoredShape(Shape &s, const string &c) : shape(s), color(c) {}

  string str() const override
  {
    ostringstream oss;
    oss << shape.str() << " has the color: " << color;
    return oss.str();
  }
};

// this will inherit from T, what will be provided in T, assert static_assert make sures that T is type of Shape Class
template <class T>
struct ColoredShape2 : T
{
  static_assert(is_base_of<Shape, T>::value,
                "Template argument must be a Shape");

  string color;

  // need this (or not!)
  ColoredShape2() {}

  template <typename... Args>
  ColoredShape2(const string &color, Args... args)
      : T(std::forward<Args>(args)...), color{color}
  {
    // you cannot call base class ctor here
    // b/c you have no idea what it is
  }

  string str() const override
  {
    ostringstream oss;
    oss << T::str() << " has the color " << color;
    return oss.str();
  }
};

int main()
{
  Square sqr{5};
  ColoredShape colored_sqr{sqr, "red"};

  cout << sqr.str() << endl
       << colored_sqr.str() << endl;

  cout << endl;

  ColoredShape2<Circle> green_circle{"green", 5};
  green_circle.resize(5);
  cout << green_circle.str() << endl;

  return 0;
}
