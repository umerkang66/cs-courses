#include <iostream>
#include <map>
#include <fstream>
#include <vector>

using namespace std;

struct Database
{
  virtual int get_population(const string &) = 0;
};

class SingletonDatabase : public Database
{
  SingletonDatabase()
  {
    cout << "Initializing the database" << endl;
    ifstream ifs("capitals.txt");
    string s1, s2;
    while (getline(ifs, s1))
    {
      getline(ifs, s2);
      int pop = stoi(s2);
      capitals[s1] = pop;
    }
  }
  map<string, int> capitals;

public:
  SingletonDatabase(SingletonDatabase const &) = delete;
  void operator=(SingletonDatabase const &) = delete;

  static SingletonDatabase &get()
  {
    static SingletonDatabase db;
    return db;
  }

  int get_population(const string &name) override { return capitals[name]; }
};

class DummyDatabase : public Database
{
  map<string, int> capitals;
  DummyDatabase()
  {
    capitals["alpha"] = 1;
    capitals["beta"] = 1;
    capitals["gamma"] = 1;
  }

public:
  static DummyDatabase &get()
  {
    static DummyDatabase dummy_db;
    return dummy_db;
  }

  int get_population(const string &name) override { return capitals[name]; }
};

class RecordFinder
{
  // we can inject the db as dependency
  Database &db;

public:
  RecordFinder(Database &db) : db(db) {}

  int total_population(const vector<string> &names)
  {
    int results = 0;
    for (auto &name : names)
      results += db.get_population(name);
    return results;
  }
};

int main()
{
  RecordFinder srf(SingletonDatabase::get());

  cout << srf.total_population(vector<string>{"Tokyo", "Delhi", "Mumbai"}) << endl;

  RecordFinder srf2(DummyDatabase::get());

  cout << srf2.total_population(vector<string>{"alpha", "beta", "gamma"}) << endl;

  return 0;
}
