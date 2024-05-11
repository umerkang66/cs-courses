#ifndef QUEUE_HPP
#define QUEUE_HPP

template <class T>
struct ListNode
{
  T data;
  ListNode<T> *next = nullptr;

  ListNode(T data) : data(data) {}
};

// after using the queue, make sure to dequeue every element
template <class T>
class Queue
{
  ListNode<T> *first = nullptr;
  ListNode<T> *last = nullptr;

public:
  Queue &enqueue(const T &data)
  {
    ListNode<T> *node = new ListNode<T>(data);
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
    ListNode<T> *temp = first;
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
};

#endif
