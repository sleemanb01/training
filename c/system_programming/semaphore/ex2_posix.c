#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <semaphore.h>
#include <stdio.h>/* printf() */
#include <stdlib.h>/* atoi() */
#include <string.h>/* strcmp() */


int main(int argc, char *argv[])
{
    sem_t *semaphore = NULL;
    int undo_num = 0;
    int i = 0;
    char input[80];

    (void)argc;
    semaphore = sem_open(argv[1], O_CREAT, 0777, 1);
    if (NULL == semaphore)
    {
        return 0;
    }

    do
    {
        int n = 0;
        int is_undo = 0;

        fgets(input, 80, stdin);

        if (((strlen(input) - 4) > 0)
        && (strstr(input, "undo")))
        {
            is_undo = 1;
        }

        switch (*input)
        {
        case 'D':
            n = (int)atoi(&input[2]);
            if (is_undo)
            {
                undo_num += n;
            }
            
            for (i = 0 ; i < n ; ++i)
            {
                sem_wait(semaphore);
            }
            break;

        case 'I':
            n = (int)atoi(&input[2]);
            if (is_undo)
            {
                undo_num -= n;
            }

            for (i = 0 ; i < n ; ++i)
            {
                sem_post(semaphore);
            }
            break;

        case 'V':
            
            n = 0;
            sem_getvalue(semaphore, &n);
            printf("current value is - %d\n", n);
            break;

        default:
            break;
        }

    } while ('X' != *input);

    if(undo_num < 0)
    {
        undo_num = -undo_num;

        for (i = 0 ; i < undo_num ; ++i)
        {
            sem_wait(semaphore);
        }
    }
    else
    {
        for (i = 0 ; i < undo_num ; ++i)
        {
            sem_post(semaphore);
        }
    }

    sem_getvalue(semaphore, &undo_num);
    printf("current value is - %d\n", undo_num);

    sem_unlink(argv[1]);
    
    return 0;
}
