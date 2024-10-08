#include <iostream>
using namespace std;

struct ListNode
{
    int data;
    ListNode *next = NULL;
    ListNode *prev = NULL;

    ListNode(int data) { this->data = data; }

    friend ostream &operator<<(ostream &os, ListNode &list_node)
    {
        os << "[";
        ListNode *current_node = &list_node;
        while (current_node != NULL)
        {
            os << current_node->data;
            if (current_node->next != NULL)
            {
                os << " <--> ";
            }
            current_node = current_node->next;
        }
        os << "]";
        return os;
    }
};

class DoublyLinkedList
{
    ListNode *head;

public:
    DoublyLinkedList() { head = NULL; }
    DoublyLinkedList(int data) { head = new ListNode(data); }
    ListNode *get_head() { return head; }

    DoublyLinkedList &append(int data)
    {
        if (head == NULL)
        {
            head = new ListNode(data);
            return *this;
        }

        ListNode *current_node = head;
        while (current_node->next != NULL)
        {
            current_node = current_node->next;
        }
        current_node->next = new ListNode(data);
        current_node->next->prev = current_node;
        return *this;
    }

    DoublyLinkedList &prepend(int data)
    {
        if (head == NULL)
        {
            head = new ListNode(data);
            return *this;
        }
        ListNode *new_node = new ListNode(data);
        new_node->next = head;
        head->prev = new_node;
        head = new_node;
        return *this;
    }

    int remove(int index)
    {
        if (head == NULL || index < 0)
        {
            return -1;
        }

        if (index == 0)
        {
            ListNode *to_be_deleted = head;
            int data = head->data;
            head = head->next;

            if (head)
            {
                // check if list is not empty
                head->prev = NULL;
            }

            delete to_be_deleted;
            return data;
        }

        int i = 0;
        ListNode *current_node = head;
        while (current_node != NULL && i < index - 1)
        {
            current_node = current_node->next;
            i++;
        }

        // we are gonna actually delete the current_node->next one
        if (current_node == NULL || current_node->next == NULL)
        {
            return -1;
        }

        int data = current_node->next->data;
        ListNode *to_be_removed = current_node->next;

        current_node->next = to_be_removed->next;

        to_be_removed->prev = current_node;

        delete to_be_removed;
        return data;
    }

    int length()
    {
        int i = 0;
        ListNode *current_node = head;
        while (current_node != NULL)
        {
            i++;
            current_node = current_node->next;
        }
        return i;
    }

    DoublyLinkedList &insert(int index, int data)
    {
        if (index == 0 || head == NULL)
        {
            prepend(data);
            return *this;
        }
        int i = 0;
        ListNode *current_node = head;
        for (int i = 0; i < index - 1; i++, current_node = current_node->next)
        {
            if (current_node == NULL || current_node->next == NULL)
            {
                append(data);
                return *this;
            }
        }
        ListNode *new_node = new ListNode(data);
        new_node->next = current_node->next;
        current_node->next->prev = new_node;
        current_node->next = new_node;
        new_node->prev = current_node;
        return *this;
    }

    DoublyLinkedList &reverse()
    {
        if (head == NULL || head->next == NULL)
        {
            return *this;
        }

        ListNode *current = head;
        while (current != NULL)
        {
            ListNode *temp = current->next;
            current->next = current->prev;
            current->prev = temp;
            // previous has come at forward position
            current = current->prev;

            if (current != NULL && current->next == NULL)
            {
                head = current;
            }
        }

        return *this;
    }

    friend ostream &operator<<(ostream &os, DoublyLinkedList &linked_list)
    {
        os << "[";
        ListNode *current_node = linked_list.head;
        while (current_node != NULL)
        {
            os << current_node->data;
            if (current_node->next != NULL)
            {
                os << " <-> ";
            }
            current_node = current_node->next;
        }
        os << "]";
        return os;
    }

    ~DoublyLinkedList()
    {
        ListNode *current_node = head;
        while (current_node != NULL)
        {
            ListNode *next = current_node->next;
            delete current_node;
            current_node = next;
        }
    }
};

int main()
{
    DoublyLinkedList linked_list;
    linked_list.append(1).append(2).prepend(0);

    cout << linked_list << endl;

    linked_list.reverse();

    cout << linked_list << endl;
    return 0;
}
