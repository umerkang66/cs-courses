#include <iostream>
using namespace std;

class Array
{
private:
    int size;
    int *arr;

    void create_and_update_arr(int size)
    {
        int *new_arr = new int[size];
        // copy every element of first array into second element
        for (int i = 0; i < length; i++)
        {
            new_arr[i] = arr[i];
        }
        delete[] arr;
        arr = new_arr;
        new_arr = NULL;
    }

    void increase_arr_size()
    {
        // make the array growable, now make the size double
        size *= 2;
        create_and_update_arr(size);
    }

    void decrease_arr_size()
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
        arr = new int[n];
        length = 0;
    }

    Array &push(int item)
    {
        if (length >= size)
        {
            increase_arr_size();
        }
        arr[length++] = item;
        return *this;
    }

    Array &insert(int i, int item)
    {
        if (length >= size)
        {
            increase_arr_size();
        }
        // now shift the elements
        for (int b_counter = length - 1; b_counter >= 1; b_counter--)
        {
            arr[b_counter + 1] = arr[b_counter];
        }
        arr[i] = item;
        length++;
        return *this;
    }

    int pop()
    {
        if (length == 0)
        {
            throw "Array is empty";
        }
        int popped_item = arr[length];
        // this isn't necessary because we are just decreasing the length
        arr[length--] = -1;
        // it should first check, if it is okay to decrease the size
        decrease_arr_size();
        return popped_item;
    }

    int remove(int i)
    {
        if (length == 0)
        {
            throw "Array is empty";
        }
        int removed_item = arr[i];
        // now shift the array items backward
        for (int c = i; c < length - 1; c++)
        {
            arr[c] = arr[c + 1];
        }
        length--;
        // it should first check, if it is okay to decrease the size
        decrease_arr_size();
        return removed_item;
    }

    void sort()
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
            int temp = arr[smallest];
            arr[smallest] = arr[i];
            arr[i] = temp;
        }
    }

    int linear_search(int item)
    {
        for (int i = 0; i < length; i++)
        {
            if (arr[i] == item)
            {
                return i;
            }
        }
        return -1;
    }

    // make sure the array is sorted
    int binary_search(int item)
    {
        int start = 0;
        int end = length - 1;
        while (start <= end)
        {
            int mid = start + (end - start) / 2;
            if (item > arr[mid])
            {
                start = mid + 1;
            }
            else if (item < arr[mid])
            {
                end = mid - 1;
            }
            else
            {
                return mid;
            }
        }
        return -1;
    }

    int &operator[](int index)
    {
        if (index >= length)
        {
            throw "Index out of bounds";
        }
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
    Array arr;
    arr.push(5).push(3).push(1).push(4).push(2);
    cout << arr << endl;
    cout << arr[2] << endl;

    return 0;
}
