#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class Journal
{
  string title;
  vector<string> entries;

public:
  Journal(const string &title) : title(title) {}

  void add_entry(const string &entry)
  {
    static int count = 1;
    entries.push_back(to_string(count++) + ": " + entry);
  }

  vector<string> get_entries() const { return entries; }
};

struct PersistenceManager
{
  static void save(const Journal &j, const string &f)
  {
    ofstream ofs(f);
    for (const auto &e : j.get_entries())
      ofs << e << endl;
  }
};

int main()
{
  Journal j("My Diary");
  j.add_entry("I ate Bananas");
  j.add_entry("I went for Shopping");

  PersistenceManager::save(j, "file.txt");

  return 0;
}
