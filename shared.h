//
// Created by scott on 12/29/25.
//

#ifndef SHARED_H
#define SHARED_H

#define SIZE 9
#define DEFAULT_VAL 0

enum Status { ACCEPT, REJECT, UNKNOWN };

struct Pair
{
    int val;
    enum Status status;
};

struct List
{
    void *val;
    struct List *next;
};

struct Cell
{
    struct Pair *pair;
    struct List *validVals;
};

struct Coordinator
{
    struct Cell *colViews[SIZE][SIZE];
    struct Cell *rowViews[SIZE][SIZE];
    struct Cell *blockViews[SIZE][SIZE];
};


struct Statuses
{
    enum Status val;
    struct Statuses *next;
};


#endif //SHARED_H
