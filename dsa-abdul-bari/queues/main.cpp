#include <iostream>
using namespace std;

template <class T>
struct Node
{
    T data;
    Node<T> *next = nullptr;

    Node(T data) : data(data) {}
};

template <class T>
class Queue
{
    Node<T> *first = nullptr;
    Node<T> *last = nullptr;

public:
    Queue &enqueue(const T &data)
    {
        Node<T> *node = new Node<T>(data);
        if (first == nullptr)
        {
            first = node;
            last = first;
            return *this;
        }

        // go to the end of queue
        last->next = node;
        last = node;

        return *this;
    }

    T dequeue()
    {
        T data = first->data;
        Node<T> *to_be_deleted = first;
        first = first->next;
        delete to_be_deleted;
        return data;
    }

    bool is_empty()
    {
        return first == nullptr;
    }

    T &peek()
    {
        return first->data;
    }
};

int main()
{
    Queue<int> queue;
    queue.enqueue(1).enqueue(2).enqueue(3);

    while (!queue.is_empty())
    {
        cout << queue.dequeue() << " ";
    }
    cout << endl;

    return 0;
}
