#include "table.hpp"

void Table::create_table(vector<string> columns)
{
  database_ptr->upsert_table(joins(columns, ","), table_name);
}
