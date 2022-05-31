#ifndef __UID_H__
#define __UID_H__

#include <stddef.h>
#include <sys/types.h>

struct uid
{
    pid_t pid;
    unsigned int count;
    time_t timestamp;
    int bad;
};

typedef struct uid ilrd_uid_t;

extern const ilrd_uid_t g_baduid;

/*
static unsigned int g_count;
*/

/*
*  Description:     Generate UID
*  Errors:          malloc can return NULL if failed
*  Parameters:      data to insert to the list
*					pointer to sort list of type sort_list_t
*  Return value:    Returns inserted iterator on success, end iterator otherwise
*  Complexity:      O(1)
*/
ilrd_uid_t UIDGenerate();

/*
*  Description:     Compare UID
*  Errors:          
*  Parameters:      data to insert to the list
*					pointer to sort list of type sort_list_t
*  Return value:    1 if equal else 0 
*  Complexity:      O(1)
*/
int UIDIsEqual(ilrd_uid_t UID1, ilrd_uid_t UID2);



#endif