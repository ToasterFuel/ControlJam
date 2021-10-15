#include <stdbool.h>
#include <stdlib.h>

#include "LinkedList.h"

/* TODO: Create a function to free the linked list in its entirety */

void LL_Create(LinkedList *list)
{
    list->head = NULL;
    list->tail = NULL;
}

void LL_Insert(void *value, LinkedList *list)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->value = value;
    node->next = NULL;

    if (list->head == NULL)
    {
        list->head = node;
        list->tail = node;
    }
    else
    {
        list->tail->next = node;
        list->tail = node;
    }
}

void LL_Remove(Node *node, LinkedList *list)
{
    if (list->head == node)
    {
        list->head = node->next;
        if (list->tail == node)
        {
            list->tail = NULL;
        }
    }

    Node *temp = list->head;
    while (temp->next != NULL && temp->next != node)
    {
        temp = temp->next;
    }
    temp->next = NULL;

    if (list->tail == node)
    {
        list->tail = temp;
    }

    node->next = NULL;
    free(node->value);
    free(node->next);
    free(node);
}

void LL_RemoveByValue(void *value, LinkedList *list) {
    Node *node;

    if (list->head->value == value)
    {
        node = list->head;
        if (list->tail == list->head)
        {
            list->tail = NULL;
        }
        list->head = list->head->next;

        node->next = NULL;
        free(node->value);
        free(node->next);
        free(node);
        return;
    }

    Node *temp = list->head;
    while (temp->next != NULL && temp->next->value != value)
    {
        temp = temp->next;
    }
    if (temp->next == NULL) {
        /* Did not find value */
        return;
    }

    node = temp->next;
    temp->next = NULL;

    if (list->tail->value == value)
    {
        list->tail = temp;
    }

    node->next = NULL;
    free(node->value);
    free(node->next);
    free(node);
}