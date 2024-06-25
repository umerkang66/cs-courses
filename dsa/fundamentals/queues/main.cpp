#include <iostream>
using namespace std;

template <class T>
struct Node
{
    T data;
    Node<T> *next = nullptr;

    Node(T data) : data(data) {}
};

// after using the queue, make sure to dequeue every element
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

        last->next = node;
        last = node;

        return *this;
    }

    T dequeue()
    {
        T data = first->data;
        Node<T> *temp = first;
        first = first->next;
        delete temp;
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

    friend ostream &operator<<(ostream &cout, Queue &queue)
    {
        cout << "{ ";
        Node<T> *current = queue.first;
        while (current != nullptr)
        {
            cout << current->data;
            if (current->next != nullptr)
            {
                // not the last element
                cout << " <- ";
            }
            current = current->next;
        }
        cout << " }";
        return cout;
    }
};

int main()
{
    Queue<int> *q1 = new Queue<int>();
    q1->enqueue(1).enqueue(2).enqueue(3);

    Queue<int> *q2 = new Queue<int>();
    q2->enqueue(4).enqueue(5).enqueue(6);

    Queue<Queue<int>> queue;
    queue.enqueue(*q1).enqueue(*q2);

    cout << queue << endl;

    for (int i = 1; !queue.is_empty(); i++)
    {
        Queue<int> inner_queue = queue.dequeue();
        cout << "Queue #" << i << ": ";
        while (!inner_queue.is_empty())
        {
            cout << inner_queue.dequeue() << " ";
        }
        cout << endl;
    }

    return 0;
}
