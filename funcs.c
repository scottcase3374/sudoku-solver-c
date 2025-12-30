//
// Created by scott on 12/19/25.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "funcs.h"
#include "list.h"

void init(struct Coordinator *coordinator, struct Cell data[SIZE][SIZE])
{
    for (int r=0; r<SIZE; r++)
    {
        for (int c=0; c<SIZE; c++)
        {
            data[r][c].pair = makePair(0, UNKNOWN);
            data[r][c].validVals = listPtrCreate();
            for (int i=1; i<=SIZE; i++)
            {
                listIntAdd(data[r][c].validVals, i);
            }
        }
    }
    setupBlockViews(coordinator, data);
    setupRowViews(coordinator, data);
    setupColViews(coordinator, data);
}

void setupBlockViews(struct Coordinator *coordinator, struct Cell (*data)[SIZE])
{
    for (int r=0; r < SIZE; r++)
        for (int c=0; c < SIZE; c++)
        {
            setupRowColToBlockCell(coordinator, r, c, data);
        }
}

void setupRowColToBlockCell(struct Coordinator *coordinator, int row, int col, struct Cell data[SIZE][SIZE])
{
    struct Cell **item = rowColToBlock(coordinator, row, col);
    switch(rowColToBlockInt(row, col)) {
        case 0:
        item[0] = &data[0][0];
        item[1] = &data[0][1];
        item[2] = &data[0][2];
        item[3] = &data[1][0];
        item[4] = &data[1][1];
        item[5] = &data[1][2];
        item[6] = &data[2][0];
        item[7] = &data[2][1];
        item[8] = &data[2][2];
        break;

        case 1:
        item[0] = &data[0][3];
        item[1] = &data[0][4];
        item[2] = &data[0][5];
        item[3] = &data[1][3];
        item[4] = &data[1][4];
        item[5] = &data[1][5];
        item[6] = &data[2][3];
        item[7] = &data[2][4];
        item[8] = &data[2][5];
        break;

        case 2:
        item[0] = &data[0][6];
        item[1] = &data[0][7];
        item[2] = &data[0][8];
        item[3] = &data[1][6];
        item[4] = &data[1][7];
        item[5] = &data[1][8];
        item[6] = &data[2][6];
        item[7] = &data[2][7];
        item[8] = &data[2][8];
        break;

        case 3:
        item[0] = &data[3][0];
        item[1] = &data[3][1];
        item[2] = &data[3][2];
        item[3] = &data[4][0];
        item[4] = &data[4][1];
        item[5] = &data[4][2];
        item[6] = &data[5][0];
        item[7] = &data[5][1];
        item[8] = &data[5][2];
        break;

        case 4:
        item[0] = &data[3][3];
        item[1] = &data[3][4];
        item[2] = &data[3][5];
        item[3] = &data[4][3];
        item[4] = &data[4][4];
        item[5] = &data[4][5];
        item[6] = &data[5][3];
        item[7] = &data[5][4];
        item[8] = &data[5][5];
        break;

        case 5:
        item[0] = &data[3][6];
        item[1] = &data[3][7];
        item[2] = &data[3][8];
        item[3] = &data[4][6];
        item[4] = &data[4][7];
        item[5] = &data[4][8];
        item[6] = &data[5][6];
        item[7] = &data[5][7];
        item[8] = &data[5][8];
        break;

        case 6:
        item[0] = &data[6][0];
        item[1] = &data[6][1];
        item[2] = &data[6][2];
        item[3] = &data[7][0];
        item[4] = &data[7][1];
        item[5] = &data[7][2];
        item[6] = &data[8][0];
        item[7] = &data[8][1];
        item[8] = &data[8][2];
        break;

        case 7:
        item[0] = &data[6][3];
        item[1] = &data[6][4];
        item[2] = &data[6][5];
        item[3] = &data[7][3];
        item[4] = &data[7][4];
        item[5] = &data[7][5];
        item[6] = &data[8][3];
        item[7] = &data[8][4];
        item[8] = &data[8][5];
        break;

        case 8:
        item[0] = &data[6][6];
        item[1] = &data[6][7];
        item[2] = &data[6][8];
        item[3] = &data[7][6];
        item[4] = &data[7][7];
        item[5] = &data[7][8];
        item[6] = &data[8][6];
        item[7] = &data[8][7];
        item[8] = &data[8][8];
        break;
    }

}

void setupRowViews(struct Coordinator *coordinator, struct Cell (*data)[SIZE])
{
    for (int r=0; r < SIZE; r++)
        for (int c=0; c < SIZE; c++)
        {
            coordinator->rowViews[r][c] =  &data[r][c];
        }
}

void setupColViews(struct Coordinator *coordinator, struct Cell (*data)[SIZE])
{
    for (int c=0; c < SIZE; c++)
        for (int r=0; r < SIZE; r++)
        {
            coordinator->colViews[c][r] = &data[r][c];
        }
}

bool load(const char *path, struct Cell (*data)[SIZE], struct Coordinator *coordinator)
{
    printf("Loading %s\n", path);
    FILE *file = fopen(path, "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }
    size_t len = 50;
    char *buffer = (char *)malloc(len * sizeof(char));
    buffer[0] = '\0';
    ssize_t read;

    int row = -1;
    int col = 0;

    while (file != NULL && (read = getline(&buffer, &len, file)) != -1)
    {
        if (read > 0)
        {
            char *nl = strstr(buffer, "\n");
            if (nl != NULL)
            {
                *nl = '\0';
            }
        }

        //printf("line %s\n", buffer);

        char *token = strtok(buffer, " ");
        while (token != NULL)
        {
            col %= SIZE;
            int cTmp = col++;
            if (cTmp == 0)
            {
                row++;
            }

            if (strstr(token, "x") == NULL)
            {
                int val = atoi(token);
                setAcceptedVal(&data[row][cTmp], val);
                clearValidVals(&data[row][cTmp]);  // remove remaining vals for cell
                removedUsedVal(coordinator, val, row, cTmp);  // remove val from views
            }
            token = strtok(NULL, " ");
        }
    }
    fclose(file);
    return true;
}

void displayBoard(struct Cell (*data)[SIZE], bool includeRemainingValidVals)
{
    char boardText[4096] = "\0";
    char extraOutput[4096] = "\0";
    char boardWithExtra[4096] = "\0";
    char boardWithExtra1[4096] = "\0";

    for (int r=0; r < SIZE; r++)
    {
        for (int c=0; c < SIZE; c++)
        {
            struct Cell *col = &data[r][c];
            char tmp[4096];
            sprintf(tmp, "%d ", peekProposal(col).val);
            strcat(boardText, tmp);

            char fmtString[] = "%-19s";
            {
                char buffer[1024];
                sprintf(buffer, fmtString, tmp);
                strcat(boardWithExtra, buffer); // board - formated
            }
            {
                char tmpStr[1024] = "\0";
                formatValidVal(tmpStr, getValidVals(col));

                char buffer[1024];
                sprintf(buffer, fmtString, tmpStr);
                strcat(boardWithExtra1, buffer); // valid vals - formatted
            }
        }

        strcat(boardText, "\n");

        strcat(extraOutput, boardWithExtra);
        strcat(extraOutput, "\n");
        strcat(extraOutput, boardWithExtra1);
        strcat(extraOutput, "\n");

        boardWithExtra1[0] = '\0';
        boardWithExtra[0] = '\0';
    }

    printf("%s\n\n\n\n", boardText);

    if (includeRemainingValidVals)
        printf("%s\n", extraOutput);
}

struct List *getValidVals(struct Cell *data)
{
    return data->validVals;
}

struct Pair peekProposal(struct Cell *cell)
{
    return *cell->pair;
}

void setProposedVal(struct Cell *cell, int val)
{
    if (ACCEPT != cell->pair->status)
    {
        cell->pair = makePair(val, UNKNOWN);
    }
}

void setAcceptedVal(struct Cell *cell, int val)
{
    free(cell->pair);
    cell->pair = makePair(val, ACCEPT);
}

void clearValidVals(struct Cell *data)  // remove remaining vals
{
    listIntClear(data->validVals);
}

void removeVal(struct Cell** item, int val)
{
    for (int i=0; i<SIZE; i++)
    {
        listIntRemove(item[i]->validVals, val);
    }
}

void removedUsedVal(struct Coordinator *coordinator, int val, int row, int col)  // remove val from views
{
    removeVal(coordinator->colViews[col], val);
    removeVal(coordinator->rowViews[row], val);
    removeVal(rowColToBlock(coordinator, row, col), val);
}

struct Pair* makePair(int val, enum Status status)
{
    struct Pair *p = (struct Pair *)malloc(sizeof(struct Pair));
    p->val = val;
    p->status = status;
}

int rowColToBlockInt( int row, int col) {
    int item = 0;
    if (row < 3 && col < 3)
        item = 0;
    else if (row < 3 && col < 6)
        item = 1;
    else if (row < 3 && col < 9)
        item = 2;
    else if (row < 6 && col < 3)
        item = 3;
    else if (row < 6 && col < 6)
        item = 4;
    else if (row < 6 && col < 9)
        item = 5;
    else if (row < 9 && col < 3)
        item = 6;
    else if (row < 9 && col < 6)
        item = 7;
    else
        item = 8;
    return item;
}

struct Cell **rowColToBlock(struct Coordinator *coordinator, int row, int col)
{
    int item = rowColToBlockInt(row, col) ;
    return coordinator->blockViews[item];
}

int formatValidVal(char *outStr, struct List *validVals)
{
    struct List *cur = validVals;
    strcat(outStr, "[");
    while (cur != NULL)
    {
        if (cur->val != NULL)
        {
            char tmpStr[50] = "\0";
            if (cur->next != NULL)
            {
                sprintf(tmpStr, "%d,", *(int*)cur->val);
            }
            else
            {
                sprintf(tmpStr, "%d", *(int*)cur->val);
            }
            strcat(outStr, tmpStr);
        }
        cur = cur->next;
    }
    strcat(outStr, "]");
    return strlen(outStr);
}

bool onlyOneValidValStrategy(struct Cell (*fullSrc)[SIZE], struct Coordinator *coordinator)
{
    bool retVal = false;
    for (int r=0; r<SIZE; r++)
    {
        for (int c=0; c<SIZE; c++)
        {
            struct Cell *col = &fullSrc[r][c];
            if (listLen(getValidVals(col)) == 1)  // Only 1 possible value remaining
            {
                setAcceptedVal(col, listIntGetFirstVal(getValidVals(col)));
                clearValidVals(col);  // clear the valid values data once we used that value.
                retVal = true;
            }
        }
    }
    return retVal;
}

bool serialStrategy(struct Cell (*fullSrc)[SIZE], struct Coordinator *coordinator)
{
    return serialStrategyImpl(fullSrc, coordinator, 0, -1) != REJECT;
}

enum Status serialStrategyImpl(struct Cell (*fullSrc)[SIZE], struct Coordinator *coordinator, int row, int col)
{
	//  *******************
	//  Row/col # handling
	// ********************
	// prep cur row/col info
	int tmpCol = col;
	col = tmpCol + 1;
	col %= SIZE;

	if (col < tmpCol)
	{
		row++;
	}

	//*******************************
	// Terminate deeper traversal and start unwinding the recursive calls
	//*******************************
	if (row == SIZE) {
		return ACCEPT;
	}
	// *************************************
	// Traversal prep - this data is manipulated on non-Accept cells/returns
	// *************************************
	// Get current row/col data - prepare before depth first traversal
	struct Cell *cell = &fullSrc[row][col];
	enum Status curCellStatus = getStatus(cell);

	if (ACCEPT == curCellStatus) {
		return serialStrategyImpl(fullSrc, coordinator, row, col);
	}
	else if (UNKNOWN == curCellStatus) {
		auto it = getValidVals(cell);

		while (it != NULL)
		{
		    if (it->val != NULL)
		    {
		        int tmpVal = *(int *)it->val;
		        setProposedVal(cell, tmpVal);

		        enum Status curGroupStatus = test(coordinator, row, col);
		        if (REJECT !=  curGroupStatus)
		        {
		            // process next cell since this cell is currently ACCEPT or UNKNOWN.
		            enum Status curProcessStatus = serialStrategyImpl(fullSrc, coordinator, row, col);

		            // if we have ACCEPT; start unwinding the recursive calls.
		            if (ACCEPT == curProcessStatus) {
		                return curProcessStatus;
		            }
		        }
		    }
			it = it->next;
		}
	}

	return reject(cell);
}

enum Status getStatus(struct Cell *cell)
{
    return cell->pair->status;
}

enum Status reject(struct Cell *cell)
{
    if (ACCEPT != getStatus(cell))
        cell->pair = makePair(DEFAULT_VAL, UNKNOWN);
    return REJECT;
}

enum Status test(struct Coordinator *coordinator, int row, int col)
{
    auto stats = listStatusesCreate();
    stats->val = validateView(coordinator->colViews[col]);
    auto it = stats->next;
    it->val = validateView(coordinator->rowViews[row]);
    it = it->next;
    it->val = validateView(rowColToBlock(coordinator, row, col));
    return filtStatus(coordinator, stats);
}

enum Status filtStatus(struct Coordinator *coordinator, struct Statuses *stats)
{
    enum Status retStatus = ACCEPT;

    auto it = stats;
    while (it != NULL)
    {
        auto status = it->val;
        if (REJECT == status)
        {
            //  no need to check further.
            retStatus = REJECT;
            break;
        }
        else if (UNKNOWN == status)
        {
            // If unknown then we should continue
            // to make sure it isn't a reject
            retStatus = UNKNOWN;
        }
        // Fall through (default if no changes) is ACCEPT .
        it = it->next;
    }
    return retStatus;
}

enum Status validateView(struct Cell **viewItems)
{
    struct Cell **it = viewItems;
    int USED_VALS[] = {0,0,0,0,0,0,0,0,0,0};
    for (int i=0; i<SIZE; i++)
    {
        USED_VALS[peekProposal(it[i]).val]++;
    }

    enum Status status = ACCEPT;
    for(int i=1; i<= SIZE; i++)
    {
        if ( USED_VALS[i] == 1)
        {
            continue;
        }
        else if (USED_VALS[i] > 1)
        {
            status = REJECT;
            break;
        }
        status = UNKNOWN;
    }

    return status;
}
