#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <time.h>
#include "funcs.h"
#include "list.h"

typedef bool (*Processors)(struct Cell (*fullSrc)[SIZE], struct Coordinator *coordinator);

int main(int argc, char *argv[])
{
    Processors processors[] = {onlyOneValidValStrategy, serialStrategy};

    if (argc == 2)
    {
        char *dirStr = argv[1];
        int dirLen = strlen(dirStr);
        struct dirent *en;
        DIR *dr = opendir(dirStr);
        if (dr)
        {
            while ((en = readdir(dr)) != NULL )
            {
                if (DT_REG == en->d_type)
                {
                    struct Cell data[SIZE][SIZE];
                    struct Coordinator coordinator;
                    init(&coordinator, data);

                    char buffer[1024] = "\0";
                    strcat(buffer, dirStr);
                    if (dirStr[dirLen-1] != '/')
                        strcat(buffer, "/");
                    strcat(buffer, en->d_name);

                    load( buffer, data, &coordinator);

                    clock_t begin = clock();
                    for (int i=0; i < sizeof(processors) / sizeof(Processors); i++)
                        processors[i](data, &coordinator);
                    clock_t end = clock();

                    printf("Processing time (seconds): %f\n", (double)(end-begin)/ CLOCKS_PER_SEC);
                    displayBoard(data, true);
                }
            }
            closedir(dr); // Close the directory
        }
    }
    return 0;
}
