#ifndef __LINKED_LIST_H__
#define __LINKED_LIST_H__

#include <stdbool.h>
#include <stdlib.h>

/* TODO: Give nodes a UUID and connect that to a UUID in the entity */
typedef struct Node
{
    void *value;
    struct Node *next;
} Node;

typedef struct LinkedList
{
    Node *head;
    Node *tail;
} LinkedList;

void LL_Create(LinkedList *list);

void LL_Insert(void *value, LinkedList *list);

void LL_Remove(Node *node, LinkedList *list);

void LL_RemoveByValue(void *value, LinkedList *list);

#endif
