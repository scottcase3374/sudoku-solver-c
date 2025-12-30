//
// Created by scott on 12/19/25.
//

#ifndef FUNCS_H
#define FUNCS_H
#include "shared.h"
#include "list.h"





void init(struct Coordinator *coordinator, struct Cell (*data)[SIZE]);
void setupRowColToBlockCell(struct Coordinator *coordinator, int row, int col, struct Cell (*data)[SIZE]);
void setupBlockViews(struct Coordinator *coordinator, struct Cell (*data)[SIZE]);
void setupRowViews(struct Coordinator *coordinator, struct Cell (*data)[SIZE]);
void setupColViews(struct Coordinator *coordinator, struct Cell (*data)[SIZE]);
bool load(const char *path, struct Cell (*data)[SIZE], struct Coordinator *coordinator);
enum Status test(struct Coordinator *coordinator, int row, int col);
enum Status filtStatus(struct Coordinator *coordinator, struct Statuses *stats);

enum Status validateView(struct Cell **viewItems);

void displayBoard(struct Cell (*data)[SIZE], bool includeRemainingValidVals);
int formatValidVal(char *outStr, struct List *validVals);

struct Pair peekProposal(struct Cell *cell);
void setProposedVal(struct Cell *cell, int val);
void setAcceptedVal(struct Cell *cell, int val);
void clearValidVals(struct Cell *data);  // remove remaining vals
void removedUsedVal(struct Coordinator *coordinator, int val, int row, int col);  // remove val from views
struct List *getValidVals(struct Cell *data);
enum Status reject(struct Cell *cell);
enum Status getStatus(struct Cell *cell);

bool onlyOneValidValStrategy(struct Cell (*fullSrc)[SIZE], struct Coordinator *coordinator);
bool serialStrategy(struct Cell (*fullSrc)[SIZE], struct Coordinator *coordinator);
enum Status serialStrategyImpl(struct Cell (*fullSrc)[SIZE], struct Coordinator *coordinator, int row, int col);

struct Pair *makePair(int val, enum Status status);
struct Cell **rowColToBlock(struct Coordinator *coordinator, int row, int col);
int rowColToBlockInt( int row, int col);
#endif //FUNCS_H
