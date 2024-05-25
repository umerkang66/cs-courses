#include <string>
using namespace std;

class DB
{
  string db_name;

public:
  DB(string db_name = "data.db") : db_name(db_name) {}

  string get_database();
  void save_database(string);
};
