/***************************************************
* NAME          : SLEEMAN NABWANI
* EXERCISE NAME : RECURSION
* REVIEWER NAME : SHAHR
*****************************************************/

#include "recursion.h"

/***********************************************************************************************
*                                    EXTRA FUNCS                                               *
************************************************************************************************/



/************************************************************************************************
*                   FIBONACCI     
*  Parameters:      number
*  Return    :      value of n'th number in fibonacci
*  Complexity:      O(n)
************************************************************************************************/

int Fibbonacci(int n)
{
   if(n == 0)
   {
      return 0;
   }
   else if(n == 1) 
   {
      return 1;
   } 
   else 
   {
      return (Fibbonacci(n-1) + Fibbonacci(n-2));
   }
}

/************************************************************************************************
*                   FLIPLIST     
*  Parameters:      node pointer (head)
*  Return    :      reverse the list
*  Complexity:      O(n)
************************************************************************************************/

Node* FlipList(Node* node)
{
    Node *rest;

   if(NULL == node->next || NULL == node)
   {
       return node;
   }

    rest = FlipList(node->next);
    node->next->next = node;
    node->next = NULL;

    return rest;
}

/************************************************************************************************
*                   SORTSTACK     
*  Parameters:      stack pointer
*  Return    :      sorted stack
*  Complexity:      O(n)
************************************************************************************************/

void sortedInsert(struct stack** s, int *x)
{
    int *temp;
    if (StackIsEmpty(*s) || *x > *(int*)StackPeek(*s)) {
        StackPush(*s, (void*)x);
        return;
    }
 
    temp = (int*)StackPeek(*s);

    sortedInsert(s, x);
    StackPop(*s);
    StackPush(*s, (void*)temp);
}
 
void SortStack(stack_t *stk)
{
    int *x;
    if (!StackIsEmpty(stk)) 
    {
        x = (int*)StackPeek(stk);
        StackPop(stk);
        SortStack(stk);
 
        sortedInsert(&stk, x);
    }
}

/************************************************************************************************
*                   STRLEN     
*  Parameters:      string pointer
*  Return    :      string length without '/0'
*  Complexity:      O(n)
************************************************************************************************/

size_t StrLen(char* str)
{
    if (*str == '\0')
    {
        return 0;
    }
    else
    {
        return 1 + StrLen(++str);
    }
}

/************************************************************************************************
*                   STRCMP     
*  Parameters:      2 strings
*  Return    :      if equal 1 else difference
*  Complexity:      O(n)
************************************************************************************************/

int StrCmp (const char* str1, const char* str2)
{
  return (*str1 == *str2 && *str2 == '\0')? 0 : (*str1 == *str2)? StrCmp(++str1, ++str2): *str1 - *str2;
} 

/************************************************************************************************
*                   STRCPY     
*  Parameters:      2 strings
*  Return    :      copy first string to second
*  Complexity:      O(n)
************************************************************************************************/

char* StrCpy(char* destination, const char* source)
{
   *destination = *source;
    if('\0' != *source)
    {
      return StrCpy(destination + 1, source + 1);
    }
    else
    {
      return destination;
    }
}

/************************************************************************************************
*                   STRCAT     
*  Parameters:      2 strings
*  Return    :      concatenates the strings
*  Complexity:      O(n)
************************************************************************************************/

char *StrCat(char *destination, const char *source)
{
  return (*destination)? StrCat(++destination, source): (*destination++ = *source++)? StrCat(destination, source): 0 ;
}

/************************************************************************************************
*                   STRSTR     
*  Parameters:      2 strings
*  Return    :      pointer to first common char
*  Complexity:      O(n)
************************************************************************************************/

char *StrStr(const char *haystack, const char *needle)
{
     if(*needle == 0)
        return (char *)haystack;

    if(*haystack == 0)
        return NULL;

    if(*haystack == *needle &&
        StrStr(haystack + 1, needle + 1) == haystack + 1)
        return (char *)haystack;

    return StrStr(haystack + 1, needle);
}
