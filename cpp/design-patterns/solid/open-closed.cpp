#include <iostream>
#include <vector>

// YOUR SYSTEMS SHOULD BE OPEN TO EXTENSION BY INHERITANCE, BUT CLOSED TO MODIFICATION

using namespace std;

enum Color
{
  red,
  green,
  blue
};
enum Size
{
  small,
  medium,
  large
};

struct Product
{
  string name;
  Color color;
  Size size;

  Product(const string &n, const Color &c, const Size &s) : name(n), color(c), size(s) {}
};

template <typename T>
struct AndSpec;

template <typename T>
struct Specification
{
  virtual bool is_satisfied(T *item) = 0;

  AndSpec<T> operator&&(Specification<T> &second) { return {*this, second}; }
};

template <typename T>
struct Filter
{
  virtual vector<T *> filter(vector<T *> items, Specification<T> &spec) = 0;
};

struct ProductFilter : Filter<Product>
{
  vector<Product *> filter(vector<Product *> items, Specification<Product> &spec)
  {
    vector<Product *> results;
    for (auto *item : items)
      if (spec.is_satisfied(item))
        results.push_back(item);
    return results;
  }
};

struct ColorSpec : Specification<Product>
{
  Color color;
  ColorSpec(const Color &c) : color(c) {}
  bool is_satisfied(Product *item) { return item->color == color; }
};

struct SizeSpec : Specification<Product>
{
  Size size;
  SizeSpec(const Size &s) : size(s) {}
  bool is_satisfied(Product *item) { return item->size == size; }
};

template <typename T>
struct AndSpec : Specification<T>
{
  Specification<T> &first;
  Specification<T> &second;

  AndSpec(Specification<T> &f, Specification<T> &s) : first(f), second(s) {}

  bool is_satisfied(T *item)
  {
    return first.is_satisfied(item) && second.is_satisfied(item);
  }
};

int main()
{
  Product apple("Apple", Color::green, Size::small);
  Product tree("Tree", Color::green, Size::large);
  Product house("House", Color::blue, Size::large);

  vector<Product *> items = {&apple, &tree, &house};

  ProductFilter pf;
  ColorSpec green(Color::green);
  SizeSpec large(Size::large);

  AndSpec<Product> green_and_large = green && large;

  vector<Product *> filtered = pf.filter(items, green_and_large);

  for (auto *item : filtered)
    cout << item->name << endl;

  return 0;
}
