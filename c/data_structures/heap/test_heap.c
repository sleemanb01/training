#include <stddef.h>
#include <stdlib.h>
#include <assert.h>

#include "heap.h"
#include "tests.h"

#define MAX_ARR 26
#define UNUSED(x) (void)x

char *names[MAX_ARR] = {"idan", "aviv", "nitzan", "daniel", "rotem", "farid", "gabriel", "barak", "carmel", "erez", "haim", "jonny", "kali", "lia", "mor", "ofir", "pan", "quill", "sif", "tal", "uri", "vadim", "will", "xandar", "yair", "zvi"};

struct test
{
    size_t age;
    float grade;
    char *name;
};

typedef struct test test_ty;


static int MaxCompare(const void *data, const void *to_match, void *param);
static void CreateDestroyTest(void);
static int PushTest(test_ty *arr);
static int Push(heap_ty *this, test_ty *arr);
static void PopTest(test_ty *arr);
static test_ty *InitTestArr(test_ty *arr);
static void PeekTest(test_ty *arr);
static int MatchOdd(const void *data, void *param);
static void RemoveTest(test_ty *arr);

int main()
{
    test_ty *arr = NULL;
    heap_ty *this = NULL;
    int result = 0;

    arr = malloc(sizeof(test_ty) * MAX_ARR);
    if (!arr)
    {
        return (1);
    }
    
    this = HeapCreate(MaxCompare, NULL);
    if (!this)
    {
        return (1);
    }

    arr = InitTestArr(arr);

    CreateDestroyTest();
    
    result = PushTest(arr);
    if (result)
    {
        return (result);
    }
    
    PopTest(arr);
    PeekTest(arr);    
    RemoveTest(arr);
    
    HeapDestroy(this);
    free(arr);
    PASS;
    return (0);
}

static void CreateDestroyTest()
{
    heap_ty *new = NULL;
    new = HeapCreate(MaxCompare, NULL);
    if (!new)
    {
        return;
    }
    TEST("Push", HeapSize(new), 0);
    TEST("Push", HeapIsEmpty(new), 1);
    HeapDestroy(new);
}

static int PushTest(test_ty *arr)
{
    heap_ty *new = NULL;
    int result = 0;

    new = HeapCreate(MaxCompare, NULL);
    if (!new)
    {
        return (1);
    }

    TEST("Push", HeapSize(new), 0);
    TEST("Push", HeapIsEmpty(new), 1);
    result = Push(new, arr);
    TEST("Push", HeapSize(new), MAX_ARR);
    TEST("Push", HeapIsEmpty(new), 0);

    HeapDestroy(new);
    return (result);
}

static int Push(heap_ty *this, test_ty *arr)
{
    size_t i = 0, result = 0;

    for (i = 0; i < MAX_ARR; ++i)
    {
        result = HeapPush(this, &arr[i]);
        if (result)
        {
            return (result);
        }
        TEST("HeapPush", HeapSize(this), (i + 1));
    }
    return (result);
}

static test_ty *InitTestArr(test_ty *arr)
{
    int i = 0;
    assert(arr);
    for (i = 0; i < MAX_ARR; ++i)
    {
        arr[i].age = 20 + (i * 3);
        arr[i].name = names[i];
        arr[i].grade = 0.1 + (i * 0.7);
    }
    return (arr);
}

static int MaxCompare(const void *data, const void *to_match, void *param)
{
    test_ty *data_ptr = NULL, *match_ptr = NULL;
    UNUSED(param);
    assert(data);
    assert(to_match);
    
    data_ptr = (test_ty*)data;
    match_ptr = (test_ty*)to_match;

    if (data_ptr->age > match_ptr->age)
    {
        return (1);
    }
    else if (data_ptr->age < match_ptr->age)
    {
        return (-1);
    }
    return (0);
}

static void PopTest(test_ty *arr)
{
    heap_ty *new = NULL;
    int result = 0;
    size_t i = 0;

    new = HeapCreate(MaxCompare, NULL);
    if (!new)
    {
        return;
    }

    TEST("Pop", HeapSize(new), 0);
    TEST("Pop", HeapIsEmpty(new), 1);
    result = Push(new, arr);
    if (result)
    {
        return;
    }
    TEST("Pop", HeapSize(new), MAX_ARR);
    TEST("Pop", HeapIsEmpty(new), 0);

    for (i = 0; i < MAX_ARR; ++i)
    {
        HeapPop(new);
        TEST("Pop", HeapSize(new), MAX_ARR - i - 1);
    }
    TEST("Pop", HeapIsEmpty(new), 1);
    HeapDestroy(new);
    return;
}

static void PeekTest(test_ty *arr)
{
    heap_ty *new = NULL;
    test_ty *test = NULL;
    int result = 0, i = 0;

    new = HeapCreate(MaxCompare, NULL);
    if (!new)
    {
        return;
    }

    TEST("Peek", HeapSize(new), 0);
    TEST("Peek", HeapIsEmpty(new), 1);
    result = Push(new, arr);
    if (result)
    {
        return;
    }
    TEST("Peek", HeapSize(new), MAX_ARR);
    TEST("Peek", HeapIsEmpty(new), 0);

    for (i = MAX_ARR - 1; i >= 0; --i)
    {
        test = HeapPeek(new);
        TEST("Peak", (int)(test->age), (20 + (i * 3)));
        HeapPop(new);
        TEST("Peek", (int)HeapSize(new), i);
    }
    TEST("Peek", HeapIsEmpty(new), 1);
    HeapDestroy(new);
    return;
}

static int MatchOdd(const void *data, void *param)
{
    test_ty *test = NULL;
    UNUSED(param);
    assert(data);

    test = (test_ty *)data;
    if ((test->age % 2) != 0)
    {
        return (1);
    }
    return (0);
}

static void RemoveTest(test_ty *arr)
{
    heap_ty *new = NULL;
    test_ty *test = NULL;
    int result = 0, i = 0;

    new = HeapCreate(MaxCompare, NULL);
    if (!new)
    {
        return;
    }

    TEST("Remove", HeapSize(new), 0);
    TEST("Remove", HeapIsEmpty(new), 1);
    result = Push(new, arr);
    if (result)
    {
        return;
    }
    TEST("Remove", HeapSize(new), MAX_ARR);
    TEST("Remove", HeapIsEmpty(new), 0);

    for (i = MAX_ARR - 1; i >= 0; --i)
    {
        test = HeapRemove(new, MatchOdd, NULL);
        if (test)
        {
            TEST("Remove", ((test->age % 2) != 0), 1);
        }
    }
    TEST("Remove", (int)HeapSize(new), 13);
    TEST("Remove", HeapIsEmpty(new), 0);
    HeapDestroy(new);
    return;
}
