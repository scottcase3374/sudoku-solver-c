//
// Created by scott on 12/21/25.
//

#ifndef LIST_H
#define LIST_H

#include "shared.h"

struct List *listPtrCreate();
struct List *listGetNext(struct List *item);
int listLen(struct List *head);

void listCellAdd(struct List *head, struct Cell *cell);
struct Cell *listCellGet(struct List *item);
struct Cell *listCellNext(struct List *item);
void listCellFree(struct List *head);

void listIntAdd(struct List *head, int val);
bool listIntRemove(struct List *head, int val);
bool listIntContains(struct List *head, int val);
void listIntFree(struct List *head);
void listIntClear(struct List *head);
int listIntGetFirstVal(struct List *head);



struct Statuses *listStatusesCreate();


#endif //LIST_H
