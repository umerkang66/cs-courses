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

    Array &push(T item)
    {
        check_and_increase_arr_size();

        arr[length++] = item;
        return *this;
    }

    Array &insert(int i, T item)
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
        T popped_item = arr[length];
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

    Array &sort()
    {
        // using the selection sort algorithm
        for (T i = 0; i < length; i++)
        {
            // find the smallest
            T smallest = i;
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

    T &operator[](T index)
    {
        if (index < 0 || index >= length)
        {
            throw "Index out of bounds";
        }
        check_and_increase_arr_size();
        return arr[index];
    }

    friend ostream &operator<<(ostream &cout, Array &array)
    {
        cout << "Size: " << array.size << " - "
             << "Length: " << array.length << " -> ";
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

    ~Array()
    {
        delete[] arr;
        arr = NULL;
    }
};

int main()
{
    Array<int> arr;
    arr.push(1).push(5).push(3).push(10).push(8);
    cout << arr << endl;

    return 0;
}
