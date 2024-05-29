#include "table.hpp"

void Table::create_table(string columns)
{
  database_ptr->create_table(columns, table_name);
}
