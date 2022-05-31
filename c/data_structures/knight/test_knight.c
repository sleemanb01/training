#include <stdio.h>
#include <math.h>

#include "knight.h"

int main()
{
    position_ty start = {0,0};
    position_ty steps[BOARD_SIZE];
    return_ty status = FAIL;
    size_t i;

    for (start.col = 0, start.row = 0 ; start.row < sqrt(BOARD_SIZE);)
    {
        status = KnightTour(start, steps);

        if (SUCCESS == status)
        {
            for (i = 0 ; i < BOARD_SIZE ; ++i)
            {
                printf("%ld: %d - %d\n", i, steps[i].row, steps[i].col);
            }
            printf("path found for: %d - %d!\n", start.row, start.col);
        }
        else
        {
                printf("status - %d\n", status);
        }

        ++start.col;
        if(start.col >= sqrt(BOARD_SIZE))
        {
            start.col = 0;
            ++start.row;
        }
    }

    return 0;
}

