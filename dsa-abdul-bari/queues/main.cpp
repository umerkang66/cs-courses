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
    Node<T> *queue = nullptr;

public:
    Queue &enqueue(const T &data)
    {
        Node<T> *node = new Node<T>(data);
        if (queue == nullptr)
        {
            queue = node;
            return *this;
        }

        node->next = queue;
        queue = node;
        return *this;
    }

    T dequeue()
    {
        T data = queue->data;
        Node<T> *to_be_deleted = queue;
        queue = queue->next;
        delete to_be_deleted;
        return data;
    }

    bool is_empty()
    {
        return queue == nullptr;
    }

    T peek()
    {
        return queue->data;
    }
};

int main()
{
    Queue<int> queue;
    queue.enqueue(1).enqueue(2).enqueue(3);

    while (!queue.is_empty())
    {
        cout << queue.dequeue() << endl;
    }

    return 0;
}
