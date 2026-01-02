//
// Created by scott on 12/21/25.
//
#include <stdlib.h>
#include <stdio.h>
#include "list.h"


struct Statuses *listStatusesCreate()
{
    struct Statuses *head = (struct Statuses*)malloc(sizeof(struct Statuses));
    struct Statuses *it = head;
    it->next = (struct Statuses*)malloc(sizeof(struct Statuses));
    it = it->next;
    it->next = (struct Statuses*)malloc(sizeof(struct Statuses));
    it = it->next;
    it->next = NULL;
    return head;
}

struct List *listPtrCreate()
{
    struct List *head = (struct List*)malloc(sizeof(struct List));
    head->next = NULL;
    head->val = NULL;
    return head;
}

void listCellAdd(struct List *head, struct Cell *cell)
{
    struct List *it = head;
    if (it == NULL)
        return;

    while (it->next != NULL)
    {
        it = it->next;
    }

    it->next = listPtrCreate();
    it = it->next;
    it->next = NULL;
    it->val = cell;
}

void listCellFree(struct List *head)
{
    struct List *it = head;

    while (it->next != NULL)
    {
        struct List *last = it;
        it = it->next;
        free(last);
    }
}

void listIntAdd(struct List *head, int val)
{
    struct List *it = head;
    while (it->next != NULL)
    {
        it = it->next;
    }

    it->next = listPtrCreate();
    it = it->next;
    it->val = (int *)malloc(sizeof(int));
    *((int*)it->val) = val;

    //printf("listIntAdd - val[%d]  next->val [%d]\n", val, *((int*)next->val));
}

int listIntGet(struct List *item)
{
    return *(int *)item->val;
}

bool listIntRemove(struct List *head, int val)
{
    if (head == NULL)
        return false;

    struct List *it = head;
    struct List *prev = NULL;
    bool contains = false;
    while (it != NULL)
    {
        if (it->val != NULL )
        {
            if (*(int *)it->val == val)
            {
                contains = true;
                prev->next = it->next;
                free(it->val);
                free(it);

                break;
            }
        }
        prev = it;
        it = it->next;
    }
    return contains;
}

bool listIntContains(struct List *head, int val)
{
    if (head == NULL)
        return false;

    struct List *next = head;
    bool contains = false;
    while (next != NULL)
    {
        if (next->val != NULL && *(int *)next->val == val)
        {
            contains = true;
            break;
        }
        next = next->next;
    }
    return contains;
}

void listIntFree(struct List *head)
{
    if (head == NULL)
        return;

    struct List *next = head;

    while (next != NULL)
    {
        struct List *last = next;
        next = next->next;
        free(last->val);
        free(last);
    }
}

void listIntClear(struct List *head)
{
    if (head == NULL)
        return;

    if (head->next != NULL)
    {
        listIntFree(head->next);
        head->next = NULL;
    }

    if (head->val != NULL)
    {
        free(head->val);
        head->val = NULL;
    }
}

int listLen(struct List *head)
{
    int cnt = 0;
    struct List *next = head;
    while (next != NULL)
    {
        if (next->val != NULL)
            cnt++;
        next = next->next;
    }

    return cnt;
}

int listIntGetFirstVal(struct List *item)
{
    if (item == NULL)
        return 0;

    struct List *next = item;

    while (next != NULL)
    {
        if (next->val != NULL)
        {
            return *(int *)next->val;
        }
        next = next->next;
    }
    return 0;
}