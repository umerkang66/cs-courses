#include "table.hpp"

void Table::create_table(string columns)
{
  database_ptr->create_table(columns, table_name);
}

void Table::add_row(string row)
{
  string random_id = generateRandomID(24);
  row = random_id + ',' + row;
  string rows = database_ptr->get_table(table_name);
  rows += row;

  database_ptr->update_table(rows, table_name);
}

void Table::delete_row(string where)
{
  string previous_rows = database_ptr->get_table(table_name);
  vector<string> column_and_value = split_into_vector(where, '=');
  vector<string> row_vector = split_into_vector(previous_rows, '\n');

  int which_column = -1;
  int which_row = -1;

  vector<string> row_of_columns = split_into_vector(row_vector[1], ',');
  for (int i = 0; i < row_of_columns.size(); i++)
  {
    if (to_lower(row_of_columns[i]) == to_lower(column_and_value[0]))
    {
      which_column = i;
    }
  }

  for (int i = 2; i < row_vector.size() - 1; i++)
  {
    if (split_into_vector(row_vector[i], ',')[which_column] == column_and_value[1])
    {
      which_row = i;
    }
  }

  vector<string> new_rows_vector;
  vector<string> previous_rows_vector = split_into_vector(previous_rows, '\n');
  for (int i = 0; i < previous_rows_vector.size() - 1; i++)
  {
    if (i != which_row)
    {
      new_rows_vector.push_back(previous_rows_vector[i]);
    }
  }

  database_ptr->update_table(joins(new_rows_vector, "\n"), table_name);
}

void Table::show_table(string key, string value)
{
  vector<vector<string>> matrix;
  vector<string> rows = split_into_vector(database_ptr->get_table(table_name), '\n');

  vector<string> first_row = split_into_vector(rows[1], ',');
  int which_column = -1;
  for (int i = 0; i < first_row.size(); i++)
  {
    if (first_row[i] == key)
      which_column = i;
  }

  for (int i = 1; i < rows.size() - 1; i++)
  {
    if (i > 1 && key != "" && value != "" && which_column != -1)
    {
      vector<string> row = split_into_vector(rows[i], ',');
      if (row[which_column] == value)
      {
        matrix.push_back(row);
      }
    }
    else
    {
      matrix.push_back(split_into_vector(rows[i], ','));
    }
  }

  bool is_table_show_able = true;

  for (int i = 0; i < matrix.size(); i++)
  {
    for (int j = 0; j < matrix[0].size(); j++)
    {
      if (matrix[i][j].length() > 40)
      {
        is_table_show_able = false;
      }
    }
  }

  if (is_table_show_able)
    show_as_table_vector(matrix);
  else
    cout << "It can't be shown as the table format, use JSON format" << endl;
}

// populate string should be like this
// <field>=<from_table>
// user=users
void Table::show_table_as_json(vector<string> populate)
{
  vector<string> rows = split_into_vector(database_ptr->get_table(table_name), '\n');
  vector<string> json_fields = split_into_vector(rows[1], ',');
  vector<map<string, string>> json_arr;

  for (int i = 2; i < rows.size() - 1; i++)
  {
    vector<string> current_row = split_into_vector(rows[i], ',');
    map<string, string> mp;

    for (int j = 0; j < current_row.size(); j++)
    {
      mp[json_fields[j]] = current_row[j];
    }

    json_arr.push_back(mp);
  }

  const string two_spaces = "  ";

  if (populate.size() == 0)
  {
    cout << '[' << '\n';
    for (int i = 0; i < json_arr.size(); i++)
    {
      cout << two_spaces << '{' << '\n';
      for (int j = 0; j < json_fields.size(); j++)
      {
        cout << two_spaces << two_spaces << json_fields[j] << ": " << json_arr[i][json_fields[j]] << ",\n";
      }
      cout << two_spaces << '}' << ',' << '\n';
    }
    cout << ']' << endl;
    return;
  }

  // also populate the table
  string new_field_in_parent = populate[0];
  string child_table = split_into_vector(populate[1], '.')[0];
  string child_table_field = split_into_vector(populate[1], '.')[1];
  string parent_referenced_in_child = split_into_vector(populate[1], '.')[2];

  vector<string> nested_rows = split_into_vector(database_ptr->get_table(child_table), '\n');
  vector<string> nested_json_fields = split_into_vector(nested_rows[1], ',');

  int which_child_field = -1;
  for (int i = 0; i < nested_json_fields.size(); i++)
  {
    if (child_table_field == nested_json_fields[i])
      which_child_field = i;
  }

  cout << '[' << '\n';
  for (int i = 0; i < json_arr.size(); i++)
  {
    // PRINTING
    cout << two_spaces << '{' << '\n';
    for (int j = 0; j < json_fields.size(); j++)
    {
      cout << two_spaces << two_spaces << json_fields[j] << ": " << json_arr[i][json_fields[j]] << ",\n";
    }

    cout << two_spaces << two_spaces << new_field_in_parent << ": [\n";

    for (int j = 2; j < nested_rows.size() - 1; j++)
    {
      vector<string> current_row = split_into_vector(nested_rows[j], ',');

      if (which_child_field != -1 && json_arr[i][parent_referenced_in_child] == current_row[which_child_field])
      {
        if (which_child_field != -1)
        {
          cout << two_spaces << two_spaces << "{\n";

          for (int k = 0; k < nested_json_fields.size(); k++)
          {
            cout << two_spaces << two_spaces << two_spaces << nested_json_fields[k] << ": " << current_row[k] << ",\n";
          }

          cout << two_spaces << two_spaces << "},\n";
        }
      }
    }

    cout << two_spaces << two_spaces << "],\n";
    cout << two_spaces << '}' << ',' << '\n';
  }
  cout << ']' << endl;
}
