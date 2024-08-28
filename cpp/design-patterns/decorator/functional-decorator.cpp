#include <iostream>
#include <functional>
using namespace std;

// DECORATOR FOR FUNCTION WITHOUT ARGUMENTS
template <typename T>
struct Logger
{
  // replace function<void()> with any function, using template argument
  T func;
  string name;

  Logger(const T &func, const string &name) : func(func), name(name) {}

  void operator()() const
  {
    cout << "Entering: " << name << endl;
    func();
    cout << "Exiting: " << name << endl;
  }
};

// DECORATOR FOR FUNCTION WITH ARGUMENTS, R is for return type
template <typename R, typename... Args>
struct LoggerWithAR
{
  function<R(Args...)> func;
  string name;

  LoggerWithAR(const function<R(Args...)> &func, const string &name) : func(func), name(name) {}

  R operator()(Args... args) const
  {
    cout << "Entering: " << name << endl;
    R result = func(args...);
    cout << "Exiting: " << name << endl;
    return result;
  }
};

int add(int a, int b)
{
  return a + b;
}

int main()
{
  Logger([]()
         { cout << "Hello" << endl; },
         "Hello Function")();

  // first is return type, others are arguments
  int logged_sum = LoggerWithAR<int, int, int>(
      [](int a, int b)
      {
        cout << "Sum is: " << a + b << endl;
        return a + b;
      },
      "Hello Function")(1, 2);

  cout << "Sum in Main: " << logged_sum << endl;

  // also works with normals functions
  int logged_sum2 = LoggerWithAR<int, int, int>(add, "Hello Function")(1, 2);

  cout << "Sum in Main: " << logged_sum2 << endl;

  return 0;
}
