#include <stdio.h>
#include <stdlib.h>

// we have to add a name here as well, to get accessed in line 10, then rename this structure
typedef struct node
{
    int number;
    // if next element is itself a node,
    // so next is the pointer of that node
    // this would be the address of a node
    struct node *next;
}
node;

void printList(node *list);
void freeList(node *list);

// we can't use binary search on linked list, because elements are not consecutive in memory
int main(void)
{
    node *list = NULL;
    // create a linkedList from 1 to n
    for (int i = 1; i <= 20; i++)
    {
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            // BUG: if the malloc error happens in other than first iteration of loop, then previous mallocated would be memory-leaked, because we just return it.
            return 1;
        }
        n->number = i;
        n->next = list;
        list = n;
    }
    printList(list);
    freeList(list);
}

void printList(node *list)
{
    node *currentNode = list;
    while (currentNode != NULL)
    {
        if (currentNode->next == NULL)
        {
            printf("%i\n", currentNode->number);
        }
        else
        {
            printf("%i -> ", currentNode->number);
        }
        currentNode = currentNode->next;
    }
}

void freeList(node *list)
{
    node *currentNode = list;
    while (currentNode != NULL)
    {
        node *tempNext = currentNode->next;
        free(currentNode);
        currentNode = tempNext;
    }
}
