#ifndef __WS_1__
#define __WS_1__

#include <stddef.h> /* for size_t */

void SwapInt(int *a, int *b);

/*array_a and array_b should be the same size */
void CopyArray(int *array_a, int *array_b, size_t array_size);

void SwapT(size_t *a, size_t *b);

size_t StrLen(const char *s);

int StrCmp(const char *s1,const char *s2);

#endif
