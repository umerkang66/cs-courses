#include <iostream>

using namespace std;

template <class T>
class Array
{
private:
    int size;
    T *arr;

    void create_and_update_arr(int size)
    {
        T *new_arr = new T[size];
        // copy every element of first array into second element
        for (int i = 0; i < length; i++)
        {
            new_arr[i] = arr[i];
        }
        delete[] arr;
        arr = new_arr;
        new_arr = NULL;
    }

    void check_and_increase_arr_size()
    {
        // make the array growable, now make the size double
        if (length >= size)
        {
            size *= 2;
            create_and_update_arr(size);
        }
    }

    void check_and_decrease_arr_size()
    {
        if (length <= size / 2)
        {
            // now make the size half
            size /= 2;
            create_and_update_arr(size);
        }
    }

public:
    int length;

    Array(int n = 10)
    {
        size = n;
        arr = new T[size];
        length = 0;
    }

    Array &push(const T &item)
    {
        check_and_increase_arr_size();

        arr[length++] = item;
        return *this;
    }

    Array &insert(int i, const T &item)
    {
        check_and_increase_arr_size();
        // now shift the elements
        for (int b_counter = length - 1; b_counter >= 1; b_counter--)
        {
            arr[b_counter + 1] = arr[b_counter];
        }
        arr[i] = item;
        length++;
        return *this;
    }

    T pop()
    {
        if (length == 0)
        {
            throw "Array is empty";
        }
        T popped_item = arr[length - 1];
        // this isn't necessary because we are just decreasing the length
        arr[length--] = -1;
        // it should first check, if it is okay to decrease the size
        check_and_decrease_arr_size();
        return popped_item;
    }

    T remove(int i)
    {
        if (length == 0)
        {
            throw "Array is empty";
        }
        T removed_item = arr[i];
        // now shift the array items backward
        for (int c = i; c < length - 1; c++)
        {
            arr[c] = arr[c + 1];
        }
        length--;
        // it should first check, if it is okay to decrease the size
        check_and_decrease_arr_size();
        return removed_item;
    }

    // to sort an array of objects, we have to overload this < operator
    Array &sort()
    {
        // using the selection sort algorithm
        for (int i = 0; i < length; i++)
        {
            // find the smallest
            int smallest = i;
            for (int j = i + 1; j < length; j++)
            {
                if (arr[j] < arr[smallest])
                {
                    smallest = j;
                }
            }
            // smallest is found, swap with the current element
            T temp = arr[smallest];
            arr[smallest] = arr[i];
            arr[i] = temp;
        }
        return *this;
    }

    Array &fill(const T &item)
    {
        for (int i = 0; i < size; i++)
        {
            arr[i] = item;
            length++;
        }
        return *this;
    }

    Array &reverse()
    {
        for (int i = 0, j = length - 1; i <= j; i++, j--)
        {
            T temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
        return *this;
    }

    T &operator[](int index)
    {
        if (index < 0 || index >= length)
        {
            throw "Index out of bounds";
        }
        check_and_increase_arr_size();
        return arr[index];
    }

    // if it is an array of complex object, make sure that complex object also has operator<< for cout overloaded
    friend ostream &operator<<(ostream &cout, Array<T> &array)
    {
        cout << '[';
        for (int i = 0; i < array.length; i++)
        {
            cout << array.arr[i];
            if (i != array.length - 1)
            {
                // not the last element
                cout << ", ";
            }
        }
        cout << ']';
        return cout;
    }
};

int main()
{
    Array<Array<int>> *parent_array = new Array<Array<int>>(5);

    parent_array->fill((new Array<int>(2))->fill(25));
    cout << *parent_array << endl;

    return 0;
}
