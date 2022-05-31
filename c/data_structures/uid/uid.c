/***************************************************
* NAME          : SLEEMAN NABWANI
* EXERCISE NAME : UID
* REVIEWER NAME : ANTON
*****************************************************/

#include <stddef.h>
#include <unistd.h>
#include <time.h>        /* timestamp */ 

#include"uid.h"

const ilrd_uid_t g_BadUID = {0,0,0,1};

static unsigned int COUNTER = 0;

/***********************************************************************************
*  Description:     Generate UID
*  Errors:          malloc can return NULL if failed
*  Parameters:      data to insert to the list
*					pointer to sort list of type sort_list_t
*  Return value:    Returns inserted iterator on success, end iterator otherwise
*  Complexity:      O(1)
***********************************************************************************/
ilrd_uid_t UIDGenerate()
{
	ilrd_uid_t new;

	new.pid = getpid();
	new.count = COUNTER;
	++COUNTER;

	time(&new.timestamp);

	if ((-1) == new.timestamp)
	{
		new.bad = 1;
		return (new);
	}

	new.bad = 0;
	new.pid = getpid();
	new.count = COUNTER;
	COUNTER++;

	return new;
}

/***********************************************************************************
*  Description:     Compare UID
*  Errors:          
*  Parameters:      data to insert to the list
*					pointer to sort list of type sort_list_t
*  Return value:    1 if equal else 0 
*  Complexity:      O(1)
***********************************************************************************/
int UIDIsEqual(ilrd_uid_t UID1, ilrd_uid_t UID2)
{
	int isMatch = 1;

	isMatch = (UID1.pid == UID2.pid && UID1.timestamp == UID2.timestamp && UID1.count == UID2.count);

	if ((UID1.bad == 0) && (UID1.bad == UID2.bad) && (isMatch == 1))
	{
		return (1);
	}
	
	return (0);

}