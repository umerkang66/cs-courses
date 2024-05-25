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

// This will split the string into an array by using the separator
string *split(string str, char separator)
{
  int arr_length = 0;
  for (int i = 0; str[i] != '\0'; i++)
  {
    if (str[i] == separator)
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
    if (str[i] == separator)
    {
      arr[arr_counter] = one_string;
      arr_counter++;
      // reset the string
      one_string = "";
    }
    else
    {
      one_string += str[i];
    }
  }
  arr[arr_counter] = one_string;
  arr[++arr_counter][0] = '\0';

  return arr;
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