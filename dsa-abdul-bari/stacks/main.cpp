#include <iostream>
using namespace std;

template <class T>
class Stack
{
    T *data;
    int size;
    int length;

    void create_and_update_stack(int size)
    {
        T *new_stack = new T[size];
        // copy every element of first array into second element
        for (int i = 0; i < length; i++)
        {
            new_stack[i] = data[i];
        }
        delete[] data;
        data = new_stack;
        new_stack = NULL;
    }

    void check_and_increase_stack_size()
    {
        // make the stack growable, now make the size double
        if (length >= size)
        {
            size *= 2;
            create_and_update_stack(size);
        }
    }

    void check_and_decrease_stack_size()
    {
        if (length <= size / 2)
        {
            // now make the size half
            size /= 2;
            create_and_update_stack(size);
        }
    }

public:
    Stack(int n = 10)
    {
        size = n;
        data = new T[size];
        length = 0;
    }

    Stack &push(T n)
    {
        check_and_increase_stack_size();
        data[length++] = n;
        return *this;
    }

    T pop()
    {
        if (length == 0)
        {
            throw "Stack is empty";
        }
        T item = data[--length];
        check_and_decrease_stack_size();
        return item;
    }

    T peek()
    {
        // peek what is at the last
        return data[length - 1];
    }

    bool is_empty() { return length == 0; }
    bool is_full() { return length == size; }

    friend ostream &operator<<(ostream &cout, Stack &stack)
    {
        cout << '[';
        for (int i = 0; i < stack.length; i++)
        {
            cout << stack.data[i];
            if (i != stack.length - 1)
            {
                // not the last element
                cout << ", ";
            }
        }
        cout << ']';
        return cout;
    }

    ~Stack()
    {
        delete[] data;
    }
};

int main()
{
    return 0;
}
