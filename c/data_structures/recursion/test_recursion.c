#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "tests.h"
#include "recursion.h"
#include "stack.h"
#include "slist.h"

static void FlipListTest(void);
static void PrintList(slist_iter_t iter);
static void StrLenTest(void);
static void StrCmpTest(void);
static void StrCpyTest(void);
static void StrStrTest(void);
int main()
{
    TEST("Fib()", Fibbonacci(15), 610);
    FlipListTest();
    StrLenTest();
    StrCmpTest();
    StrCpyTest();
    StrStrTest();

    PASS;
    return (0);
}

static void FlipListTest()
{
    slist_iter_t head = NULL, runner = NULL;
    slist_t *list = NULL;
    int arr[5] = {1, 2, 3, 4, 5};
    int i = 0;
    list = SlistCreate();
    head = SlistBegin(list);
    for (i = 0; i < 5; ++i)
    {
        SlistInsert(head, &arr[i]);
        head = SlistNext(head);
    }
    head = SlistBegin(list);
    PrintList(head);
    head = FlipList(head);
    runner = SlistNext(head);
    PrintList(runner);
    SlistDestroy(list);
}

static void PrintList(slist_iter_t iter)
{
    int i = 0, data = 0;
    for (i = 0; i < 5; ++i)
    {
        data = *(int *)SlistGetData(iter);
        printf("\ndata = %d\n", data);
        iter = SlistNext(iter);
    }
}

static void StrLenTest()
{
    size_t res1 = 0, res2 = 0;
    char *str1 = "123456";
    char *str2 = "abcdefghisadf";
    char *str3 = "123456asdfg";
    char *str4 = "";
    
    res1 = StrLen(str1);
    res2 = strlen(str1);
    TEST("StrLen()", res1, res2);
    res1 = StrLen(str2);
    res2 = strlen(str2);
    TEST("StrLen()", res1, res2);
    res1 = StrLen(str3);
    res2 = strlen(str3);
    TEST("StrLen()", res1, res2);
    res1 = StrLen(str4);
    res2 = strlen(str4);
    TEST("StrLen()", res1, res2);
}

static void StrCmpTest()
{
    int res1 = 0, res2 = 0;
    char *str1 = "123456";
    char *str2 = "abcdefghisadf";
    char *str3 = "123456asdfg";
    char *str4 = "";
    char *str5 = "123456";
    
    res1 = StrCmp(str1, str2);
    res2 = strcmp(str1, str2);
    TEST("StrCmp()", res1, res2);
    printf("\nres1 = %d\nres2 = %d\n", res1, res2);
    res1 = StrCmp(str1, str5);
    res2 = strcmp(str1, str5);
    TEST("StrCmp()", res1, res2);
    printf("\nres1 = %d\nres2 = %d\n", res1, res2);
    res1 = StrCmp(str1, str3);
    res2 = strcmp(str1, str3);
    TEST("StrCmp()", res1, res2);
    printf("\nres1 = %d\nres2 = %d\n", res1, res2);
    res1 = StrCmp(str2, str4);
    res2 = strcmp(str2, str4);
    TEST("StrCmp()", res1, res2);
    printf("\nres1 = %d\nres2 = %d\n", res1, res2);
}


static void StrCpyTest()
{
    int res1 = 0, res2 = 0;
    char str1[7] = "123456";
    char *str2 = malloc(sizeof(char) * 7);
    char *str3 = malloc(sizeof(char) * 7);
    char *str4 = malloc(sizeof(char) * 5);
    StrCpy(str2, str1);
    strcpy(str3, str1);
    /*StrCpy(str4, str1);
*/
    res1 = StrCmp(str1, str2);
    res2 = StrCmp(str1, str3);
    TEST("StrCpy()", res1, res2);
    /*
    res1 = StrCmp(str1, str2);
    res2 = StrCmp(str1, str4);
    TEST("StrCpy()", res1, res2);
*/
    free(str2);
    free(str3);
    free(str4);
}

static void StrStrTest()
{
    size_t res1 = 0, res2 = 0;
    char *str1 = "123456";
    char *str2 = "abc123456sadf";
    char *str3 = "123456asdfg";
    char *str4 = "asdfg";
    char *str5 = "asasasfg";
    char *str6 = "";
    
    res1 = (size_t)StrStr(str2, str1);
    res2 = (size_t)strstr(str2, str1);
    TEST("StrStr()", res1, res2);
    res1 = (size_t)StrStr(str1, str2);
    res2 = (size_t)strstr(str1, str2);
    TEST("StrStr()", res1, res2);
    res1 = (size_t)StrStr(str3, str1);
    res2 = (size_t)strstr(str3, str1);
    TEST("StrStr()", res1, res2);
    res1 = (size_t)StrStr(str6, str4);
    res2 = (size_t)strstr(str6, str4);
    TEST("StrStr()", res1, res2);
    res1 = (size_t)StrStr(str5, str6);
    res2 = (size_t)strstr(str5, str6);
    TEST("StrStr()", res1, res2);
}
