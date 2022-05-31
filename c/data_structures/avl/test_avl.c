#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

#include "tests.h"
#include "avl.h"
#include "dlist.h"

#define ARR_SIZE 11
#define UNUSED(x) (void)(x)

typedef enum {LEFT, RIGHT, CHILDREN_NUM} children_ty;

struct avl_node
{
    void *data;
    size_t height;
    avl_node_ty *children[CHILDREN_NUM];
};

struct data
{
    size_t key;
    int age;
    float grade;
    char letter;
};

typedef struct data data_ty;
static void RemoveMulti(void);
static void GetForEach(void);
void CreateDestroyTest(size_t *arr);
void InsertDestroyTest(size_t *arr);
void InsertRemoveTest(size_t *arr);
void FindTest(size_t *arr);
void ForEachTest(size_t *arr);
void CreateTree(avl_ty *avl, size_t *arr);
void CreateStructTree(avl_ty *avl, data_ty *arr);
static int CompareFunc(const void *data, const void *to_compare, const void *param);
static int ActionFuncAdd(void *data, void *params);
static int PrintNodes(void *data, void *params);
static int SpecialCompareFunc(const void *data, const void *to_compare, const void *param);
static int FindIf(const void *data, const void *to_compare, const void *params);

int main()
{
    size_t *arr = NULL;
    size_t runner = 0;
    
    arr = malloc(sizeof(size_t) * ARR_SIZE);
    if (!arr)
    {
        return (1);
    }
    for(runner = 0; ARR_SIZE > runner; ++runner )
    {
        arr[runner] = runner;
    }
    
    CreateDestroyTest(arr);
    InsertDestroyTest(arr);
    InsertRemoveTest(arr);
    ForEachTest(arr);
    GetForEach();
    RemoveMulti();
    PASS;
    free(arr);
    return (0);
}

void CreateDestroyTest(size_t *arr)
{
    avl_ty *this = NULL;
    UNUSED(arr);

    this = AVLCreate(CompareFunc, NULL);
    
    TEST("CreateDestroyEmpty()", AVLIsEmpty(this), 1);
    TEST("CreateDestroySize()", AVLSize(this), 0);
    TEST("CreateDestroyHeight()", AVLHeight(this), 0);

    AVLDestroy(this);
}

void InsertDestroyTest(size_t *arr)
{
    avl_ty *this = NULL;
    this = AVLCreate(CompareFunc, NULL);
    
    TEST("CreateDestroyEmpty()", AVLIsEmpty(this), 1);
    TEST("CreateDestroySize()", AVLSize(this), 0);
    TEST("CreateDestroyHeight()", AVLHeight(this), 0);

    CreateTree(this, arr);

    TEST("CreateDestroyEmpty()", AVLIsEmpty(this), 0);
    TEST("CreateDestroySize()", AVLSize(this), 11);
    TEST("CreateDestroyHeight()", AVLHeight(this), 4);

    AVLDestroy(this);
}

void InsertRemoveTest(size_t *arr)
{
    size_t runner = 0, *data = NULL;
    avl_ty *this = NULL;
    this = AVLCreate(CompareFunc, NULL);
    
    TEST("CreateDestroyEmpty()", AVLIsEmpty(this), 1);
    TEST("CreateDestroySize()", AVLSize(this), 0);
    TEST("CreateDestroyHeight()", AVLHeight(this), 0);

    CreateTree(this, arr);
    
    TEST("CreateDestroyEmpty()", AVLIsEmpty(this), 0);
    TEST("CreateDestroySize()", AVLSize(this), 11);
    TEST("CreateDestroyHeight()", AVLHeight(this), 4);

    for(runner = ARR_SIZE-1; runner < ARR_SIZE; --runner)
    {
        data = AVLFind(this, arr+runner);
        AVLRemove(this, data);
        TEST("AVLSize", AVLSize(this), runner);
    }

    TEST("CreateDestroyEmpty()", AVLIsEmpty(this), 1);

    AVLDestroy(this);
}

void ForEachTest(size_t *arr)
{
    size_t adder = 1;
    avl_ty *this = NULL;
    this = AVLCreate(CompareFunc, NULL);
    
    TEST("CreateDestroyEmpty()", AVLIsEmpty(this), 1);
    TEST("CreateDestroySize()", AVLSize(this), 0);
    TEST("CreateDestroyHeight()", AVLHeight(this), 0);

    CreateTree(this, arr);
    
    TEST("CreateDestroyEmpty()", AVLIsEmpty(this), 0);
    TEST("CreateDestroySize()", AVLSize(this), 11);
    TEST("CreateDestroyHeight()", AVLHeight(this), 4);

    printf("\n------------------before-add-------------------------\n");
    AVLForEach(this, PrintNodes, NULL, IN);
    printf("\n------------------after-add-------------------------\n");
    AVLForEach(this, ActionFuncAdd, &adder, POST);
    AVLForEach(this, PrintNodes, NULL, IN);

    AVLDestroy(this);
}

void CreateTree(avl_ty *avl, size_t *arr)
{
    AVLInsert(avl, arr+5);
    AVLInsert(avl, arr+8);
    AVLInsert(avl, arr+6);
    AVLInsert(avl, arr+7);
    AVLInsert(avl, arr+10);
    AVLInsert(avl, arr+9);
    AVLInsert(avl, arr+2);
    AVLInsert(avl, arr+4);
    AVLInsert(avl, arr+3);
    AVLInsert(avl, arr+0);
    AVLInsert(avl, arr+1);
}

void CreateStructTree(avl_ty *avl, data_ty *arr)
{
    AVLInsert(avl, arr+5);
    AVLInsert(avl, arr+8);
    AVLInsert(avl, arr+6);
    AVLInsert(avl, arr+7);
    AVLInsert(avl, arr+10);
    AVLInsert(avl, arr+9);
    AVLInsert(avl, arr+2);
    AVLInsert(avl, arr+4);
    AVLInsert(avl, arr+3);
    AVLInsert(avl, arr+0);
    AVLInsert(avl, arr+1);
}


static int CompareFunc(const void *data, const void *to_compare, const void *param)
{
    size_t data_key = 0, compare_key = 0;
    UNUSED(param);

    data_key = *(size_t *)data;
    compare_key = *(size_t *)to_compare;

    if (data_key > compare_key)
    {
        return (1);
    }
    else if (data_key < compare_key)
    {
        return (-1);
    }
    return (0);
}

static int ActionFuncAdd(void *data, void *params)
{
    size_t *node_data = (size_t *)data;
    *node_data += *(size_t*)params;
    return 0;
}

static int PrintNodes(void *data, void *params) /*in order*/
{
    UNUSED(params);
    printf("\nnode's data = %lu\n", *(size_t*)data);
    return (0);
}

static void GetForEach()
{
    size_t runner = 0;
    data_ty *data_arr = NULL, *data_ptr = NULL;
    dlist_t *list = NULL;
    avl_ty *avl = NULL;
    dlist_iter_t iter = NULL, end = NULL;
    char match = 'A';

    avl = AVLCreate(SpecialCompareFunc, NULL);
    list = DlistCreate();
    if (!list)
    {
        return;
    }
    data_arr = malloc(sizeof(data_ty) * ARR_SIZE);
    if (!data_arr)
    {
        return;
    }
    for(runner = 0; ARR_SIZE > runner; ++runner )
    {
        data_arr[runner].age = runner + 20;
        data_arr[runner].grade = 1.1 + (runner * 0.3);
        data_arr[runner].key = runner;
        data_arr[runner].letter = 65 + (runner % 2 == 0 ? 0 : (int)runner);
    }
    CreateStructTree(avl, data_arr);

    AVLRTreeForeach(avl, list, FindIf, &match, NULL);
    iter = DlistBegin(list);
    end = DlistEnd(list);
    while (iter != end)
    {
        data_ptr = (data_ty*)DlistGetData(iter);
        iter = DlistNext(iter);
        TEST("RTreeForEach",data_ptr->letter, match);
    }

    free(data_arr);
    DlistDestroy(list);
    AVLDestroy(avl);
}

static int SpecialCompareFunc(const void *data, const void *to_compare, const void *param)
{
    data_ty *data_FE = NULL, *compare_FE = NULL;
    UNUSED(param);

    data_FE = (data_ty *)data;
    compare_FE = (data_ty *)to_compare;

    if (data_FE->key > compare_FE->key)
    {
        return (1);
    }
    else if (data_FE->key < compare_FE->key)
    {
        return (-1);
    }
    return (0);
}

static int FindIf(const void *data, const void *to_compare, const void *params)
{
    data_ty *compare_FE = NULL;
    char data_FE = *(char *)data;
    UNUSED(params);
    compare_FE = (data_ty*)to_compare;
    if (compare_FE->letter == data_FE)
    {
        return (1);
    }
    return (0);
}

static void RemoveMulti()
{
    size_t runner = 0, counter = 0;
    data_ty *data_arr = NULL;
    dlist_t *list = NULL;
    avl_ty *avl = NULL;
    char match = 'A';

    avl = AVLCreate(SpecialCompareFunc, NULL);
    list = DlistCreate();
    if (!list)
    {
        return;
    }
    data_arr = malloc(sizeof(data_ty) * ARR_SIZE);
    if (!data_arr)
    {
        return;
    }
    for(runner = 0; ARR_SIZE > runner; ++runner )
    {
        data_arr[runner].age = runner + 20;
        data_arr[runner].grade = 1.1 + (runner * 0.3);
        data_arr[runner].key = runner;
        data_arr[runner].letter = 65 + (runner % 2 == 0 ? 0 : (int)runner);
    }
    CreateStructTree(avl, data_arr);
    
    counter = AVLRTreeRemoveMultiple(avl, FindIf, &match, NULL);

    AVLRTreeForeach(avl, list, FindIf, &match, NULL);
   
    TEST("RTreeForEach",DlistIsEmpty(list), 1);
    TEST("RTreeForEach",counter, 6);
    TEST("RTreeForEach",AVLSize(avl), (ARR_SIZE - 6));
    
    free(data_arr);
    DlistDestroy(list);
    AVLDestroy(avl);
}
