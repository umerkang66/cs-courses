#include <string>
#include "../db/db.hpp"

using namespace std;

class Table : public DB
{
  string table_name;
  // to which database this table belongs to
  DB *database_ptr = nullptr;

public:
  Table(string table_name, DB *database_ptr) : table_name(table_name), database_ptr(database_ptr) {}

  void save_table(string rows, string name);
  string get_table(string name);
};
