#ifndef __RECURSION_H__
#define __RECURSION_H__

#include <stddef.h>  /* size_t */

#include "stack.h"
#include "slist.h"

typedef struct slist_node
{
    void *data;
    slist_node_t *next;
}Node;

/************************************************************************************************
*                   FIBONACCI     
*  Parameters:      number
*  Return    :      value of n'th number in fibonacci
*  Complexity:      O(n)
************************************************************************************************/

int Fibbonacci(int n);

/************************************************************************************************
*                   FLIPLIST     
*  Parameters:      node pointer (head)
*  Return    :      reverse the list
*  Complexity:      O(n)
************************************************************************************************/

Node* FlipList(Node* node);

/************************************************************************************************
*                   SORTSTACK     
*  Parameters:      stack pointer
*  Return    :      sorted stack
*  Complexity:      O(n)
************************************************************************************************/

void SortStack(stack_t *stk);

/************************************************************************************************
*                   STRLEN     
*  Parameters:      string pointer
*  Return    :      string length without '/0'
*  Complexity:      O(n)
************************************************************************************************/

size_t StrLen(char* str);

/************************************************************************************************
*                   STRCMP     
*  Parameters:      2 strings
*  Return    :      if equal 1 else difference
*  Complexity:      O(n)
************************************************************************************************/

int StrCmp (const char* str1, const char* str2);

/************************************************************************************************
*                   STRCPY     
*  Parameters:      2 strings
*  Return    :      copy first string to second
*  Complexity:      O(n)
************************************************************************************************/

char* StrCpy(char* destination, const char* source);

/************************************************************************************************
*                   STRCAT     
*  Parameters:      2 strings
*  Return    :      concatenates the strings
*  Complexity:      O(n)
************************************************************************************************/

char *StrCat(char *destination, const char *source);

/************************************************************************************************
*                   STRSTR     
*  Parameters:      2 strings
*  Return    :      pointer to first common char
*  Complexity:      O(n)
************************************************************************************************/

char *StrStr(const char *haystack, const char *needle);

#endif