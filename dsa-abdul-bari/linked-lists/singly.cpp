#include <iostream>
using namespace std;

template <class T>
struct ListNode
{
    T data;
    ListNode<T> *next = NULL;
    ListNode(const T &data) { this->data = data; }

    friend ostream &operator<<(ostream &os, ListNode<T> &list_node)
    {
        os << "[";
        ListNode<T> *current_node = &list_node;
        while (current_node != NULL)
        {
            os << current_node->data;
            if (current_node->next != NULL)
            {
                os << " --> ";
            }
            current_node = current_node->next;
        }
        os << "]";
        return os;
    }
};

template <class T>
class LinkedList
{
    ListNode<T> *head;

public:
    LinkedList() { head = NULL; }
    LinkedList(const T &data) { head = new ListNode<T>(data); }
    ListNode<T> *get_head() { return head; }

    LinkedList<T> &append(const T &data)
    {
        if (head == NULL)
        {
            head = new ListNode(data);
            return *this;
        }

        ListNode<T> *current_node = head;
        while (current_node->next != NULL)
        {
            current_node = current_node->next;
        }
        current_node->next = new ListNode<T>(data);
        return *this;
    }

    LinkedList<T> &prepend(const T &data)
    {
        if (head == NULL)
        {
            head = new ListNode(data);
            return *this;
        }
        ListNode<T> *new_node = new ListNode<T>(data);
        new_node->next = head;
        head = new_node;
        return *this;
    }

    const T &remove(int index)
    {
        if (head == NULL)
        {
            throw "List is empty";
        }

        if (index < 0)
        {
            throw "Index out of bounds";
        }

        if (index == 0)
        {
            ListNode<T> *to_be_deleted = head;
            T data = head->data;
            head = head->next;

            delete to_be_deleted;
            return data;
        }

        int i = 0;
        ListNode<T> *current_node = head;
        while (current_node != NULL && i < index - 1)
        {
            current_node = current_node->next;
            i++;
        }

        // we are gonna actually delete the current_node->next one
        if (current_node == NULL || current_node->next == NULL)
        {
            throw "Index out of bounds";
        }

        T data = current_node->next->data;
        ListNode<T> *to_be_removed = current_node->next;

        current_node->next = to_be_removed->next;

        delete to_be_removed;
        return data;
    }

    int length()
    {
        int i = 0;
        ListNode<T> *current_node = head;
        while (current_node != NULL)
        {
            i++;
            current_node = current_node->next;
        }
        return i;
    }

    LinkedList<T> &insert(int index, const T &data)
    {
        if (index == 0 || head == NULL)
        {
            prepend(data);
            return *this;
        }
        int i = 0;
        ListNode<T> *current_node = head;
        for (int i = 0; i < index - 1; i++, current_node = current_node->next)
        {
            if (current_node == NULL || current_node->next == NULL)
            {
                append(data);
                return *this;
            }
        }
        ListNode<T> *new_node = new ListNode<T>(data);
        new_node->next = current_node->next;
        current_node->next = new_node;
        return *this;
    }

    LinkedList<T> &reverse()
    {
        if (head == NULL || head->next == NULL)
        {
            return *this;
        }
        ListNode<T> *previous = NULL;
        ListNode<T> *current = head;

        while (current != NULL)
        {
            ListNode<T> *next = current->next;
            current->next = previous;
            previous = current;
            current = next;
        }

        head = previous;

        return *this;
    }

    friend ostream &operator<<(ostream &os, LinkedList<T> &linked_list)
    {
        os << "[";
        ListNode<T> *current_node = linked_list.head;
        while (current_node != NULL)
        {
            os << current_node->data;
            if (current_node->next != NULL)
            {
                os << " --> ";
            }
            current_node = current_node->next;
        }
        os << "]";
        return os;
    }

    ~LinkedList()
    {
        ListNode<T> *current_node = head;
        while (current_node != NULL)
        {
            ListNode<T> *next = current_node->next;
            delete current_node;
            current_node = next;
        }
    }
};

int main()
{
    LinkedList<int> *l1 = new LinkedList<int>();
    l1->append(1).append(2);
    LinkedList<int> *l2 = new LinkedList<int>();
    l2->append(3).append(4);
    LinkedList<int> *l3 = new LinkedList<int>();
    l3->append(5).append(6);

    LinkedList<LinkedList<int>> linked_list;
    linked_list.append(*l1).append(*l2).append(*l3);

    cout << linked_list << endl;

    return 0;
}
