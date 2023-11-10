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

int main(void)
{
    node *list = NULL;

    // create a linkedList from 1 to n
    for (int i = 1; i <= 20; i++)
    {
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return 1;
        }
        n->number = i;
        n->next = list;
        list = n;
    }

    printList(list);
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
