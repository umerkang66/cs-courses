#include "utils.hpp"

int str_include_start(string str, string check)
{
  // this will return -1, if it doesn't include
  // the check string, otherwise it will return the index
  int check_length = check.length();
  bool all_chars_in_str[check_length];
  // initialize it with 0
  for (int i = 0; i < check_length; i++)
  {
    all_chars_in_str[i] = 0;
  }
  int check_starting_index = -1;

  for (int i = 0; str[i] != '\0'; i++)
  {
    // there is a chance that that table will exist
    for (int j = 0; j < check_length; j++)
    {
      if (str[i + j] == check[j])
      {
        all_chars_in_str[j] = 1;
      }
    }

    // check if the word is found
    bool is_word_found = true;
    for (int i = 0; i < check_length; i++)
    {
      if (all_chars_in_str[i] == 0)
      {
        is_word_found = false;
      }
    }

    // if all the characters are found
    if (is_word_found)
    {
      // store the starting index
      check_starting_index = i;
      // and break the loop
      break;
    }
    else
    {
      // reset the values
      for (int i = 0; i < check_length; i++)
      {
        all_chars_in_str[i] = 0;
      }
    }
  }

  return check_starting_index;
}

int str_include_end(int starting_index, string str, string check)
{
  int end = -1;
  int check_length = check.length();

  for (int i = starting_index; str[i] != '\0'; i++)
  {
    bool chars_of_check_found[check_length];
    for (int i = 0; i < check_length; i++)
    {
      // initialize every value with 0 means not found
      chars_of_check_found[i] = 0;
    }
    int chars_check_counter = 0;
    for (int j = i; j < i + check_length; j++)
    {
      if (str[j] == check[j - i])
      {
        chars_of_check_found[chars_check_counter] = 1;
        chars_check_counter++;
      }
    }
    bool is_found = true;
    for (int i = 0; i < check_length; i++)
    {
      if (chars_of_check_found[i] == 0)
      {
        is_found = false;
      }
    }
    if (is_found)
    {
      end = i + check_length - 1;
      break;
    }
  }
  return end;
}

// // This will split the string into an array by using the separator
string *split(const string &str, char delimeter)
{
  int arr_length = 0;
  for (int i = 0; str[i] != '\0'; i++)
  {
    if (str[i] == delimeter)
    {
      arr_length++;
    }
  }

  // make an array of that length in the HEAP memory
  // make sure the DEALLOCATE this memory after using it
  // +2: +1 is for there is one more word than separator
  // +1 is for terminator string character
  string *arr = new string[arr_length + 2];
  int arr_counter = 0;
  string one_string = "";
  for (int i = 0; str[i] != '\0'; i++)
  {
    if (str[i] == delimeter)
    {
      arr[arr_counter] = one_string;
      arr_counter++;
      // reset the string
      one_string = "";
    }
    else
    {
      if (str[i] == '"')
      {
        int j;
        for (j = i + 1; str[j] != '"' && str[j] != '\0'; j++)
        {
          one_string += str[j];
        }
        i = j;
      }
      else
      {
        one_string += str[i];
      }
    }
  }
  arr[arr_counter] = one_string;
  arr[arr_counter + 1] = "";

  return arr;
}

vector<string> split_into_vector(string str, char separator)
{
  vector<string> arr;
  string temp = "";
  for (int i = 0; i < str.length(); i++)
  {
    if (str[i] == separator)
    {
      arr.push_back(temp);
      temp = "";
    }
    else
    {
      temp += str[i];
    }
  }
  arr.push_back(temp);
  return arr;
}

string joins(vector<string> arr, string separator)
{
  string str = "";
  for (int i = 0; i < arr.size(); i++)
  {
    str += arr[i];
    if (i < arr.size() - 1)
    {
      str += separator;
    }
  }
  return str;
}

void clear()
{
  // if the operating system is windows
// then run this
#ifdef _WIN32
  system("cls");
#else
  // if operating system is unix or linux, run this
  system("clear");
#endif
}

string to_lower(string str)
{
  string answer = "";
  for (int i = 0; str[i] != '\0'; i++)
  {
    if (str[i] >= 65 && str[i] <= 92)
    {
      answer += (char)(str[i] + 32);
    }
    else
    {
      answer += str[i];
    }
  }
  return answer;
}

string to_upper(string str)
{
  string answer = "";
  for (int i = 0; str[i] != '\0'; i++)
  {
    if (str[i] >= 97 && str[i] <= 122)
    {
      answer += (char)(str[i] - 32);
    }
    else
    {
      answer += str[i];
    }
  }
  return answer;
}

bool str_includes(const string &str, const string &substr)
{
  if (substr.empty())
  {
    return true;
  }
  if (str.size() < substr.size())
  {
    return false;
  }

  for (int i = 0; i <= str.size() - substr.size(); ++i)
  {
    int j = 0;
    while (j < substr.size() && str[i + j] == substr[j])
    {
      ++j;
    }
    if (j == substr.size())
    {
      return true;
    }
  }
  return false;
}

// Function to generate a random ID of given length
string generateRandomID(int length)
{
  auto generateRandomNumber = [](int min, int max) -> int
  {
    return min + (rand() % (max - min + 1));
  };

  // Characters to use for generating the random ID
  const string characters = "0123456789ABCDEFabcdef";
  string randomID;

  // Seed the random number generator
  srand(time(0));

  // Generate the random ID
  for (int i = 0; i < length; ++i)
  {
    int randomIndex = generateRandomNumber(0, characters.size() - 1);
    randomID += characters[randomIndex];
  }

  return randomID;
}

void show_as_table(string **matrix, int rows, int cols)
{
  // Calculate the maximum length of strings in each column
  int max_col_lengths[cols];
  for (int i = 0; i < cols; i++)
  {
    max_col_lengths[i] = 0;
    for (int j = 0; j < rows; j++)
    {
      int len = matrix[j][i].length();
      if (len > max_col_lengths[i])
      {
        max_col_lengths[i] = len;
      }
    }
  }

  // Display the table
  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++)
    {
      cout << "+-";
      for (int k = 1; k <= max_col_lengths[j]; k++)
      {
        cout << "-";
      }
      cout << "-";
    }
    cout << "+" << endl;

    for (int j = 0; j < cols; j++)
    {
      cout << "| " << matrix[i][j];
      for (int k = 1; k <= max_col_lengths[j] - (matrix[i][j]).length(); k++)
      {
        cout << ' ';
      }
      cout << " ";
    }
    cout << "|" << endl;
  }

  // Bottom border of the table
  for (int j = 0; j < cols; j++)
  {
    cout << "+-";
    for (int k = 1; k <= max_col_lengths[j]; k++)
    {
      cout << '-';
    }
    cout << "-";
  }
  cout << "+" << endl;
}

void show_as_table_vector(vector<vector<string>> matrix)
{
  int rows = matrix.size();
  int cols = matrix[0].size();

  // Calculate the maximum length of strings in each column
  int max_col_lengths[cols];
  for (int i = 0; i < cols; i++)
  {
    max_col_lengths[i] = 0;
    for (int j = 0; j < rows; j++)
    {
      int len = matrix[j][i].length();
      if (len > max_col_lengths[i])
      {
        max_col_lengths[i] = len;
      }
    }
  }

  // Display the table
  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++)
    {
      cout << "+-";
      for (int k = 1; k <= max_col_lengths[j]; k++)
      {
        cout << "-";
      }
      cout << "-";
    }
    cout << "+" << endl;

    for (int j = 0; j < cols; j++)
    {
      cout << "| " << matrix[i][j];
      for (int k = 1; k <= max_col_lengths[j] - (matrix[i][j]).length(); k++)
      {
        cout << ' ';
      }
      cout << " ";
    }
    cout << "|" << endl;
  }

  // Bottom border of the table
  for (int j = 0; j < cols; j++)
  {
    cout << "+-";
    for (int k = 1; k <= max_col_lengths[j]; k++)
    {
      cout << '-';
    }
    cout << "-";
  }
  cout << "+" << endl;
}

string split_long_line(string longLine, int maxLength)
{
  string result;
  int start = 0;

  while (start < longLine.length())
  {
    // Find the end position of the current chunk
    int end = start + maxLength;

    // If the end position is within the bounds of the string
    if (end < longLine.length())
    {
      // Move end back to the last space before the maxLength boundary
      while (end > start && longLine[end] != ' ')
      {
        --end;
      }
      // If no space was found, keep the word whole and use the original maxLength boundary
      if (end == start)
      {
        end = start + maxLength;
      }
    }
    else
    {
      // If the end position is out of bounds, move it to the end of the string
      end = longLine.length();
    }

    // Take a substring from start to end
    string chunk = longLine.substr(start, end - start);
    result += chunk;

    // If this is not the last chunk, add a newline character
    if (end < longLine.length())
    {
      result += '\n';
    }

    // Move the start position to the end position + 1 to skip the space
    start = end + 1;
  }

  return result;
}
