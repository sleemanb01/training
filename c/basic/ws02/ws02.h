#ifndef __WS_2__
#define __WS_2__

#include <stddef.h> /* for size_t */

size_t StrLen(const char *s);

char *StrCpy(char *dest, const char *src);

char *StrnCpy(char *dest, const char *src, size_t n);

int StrCmp(const char *s1, const char *s2);

int StrnCmp(const char *s1, const char *s2, size_t n);

int StrCaseCmp(const char *s1, const char *s2);

char *StrChr(const char *s, int c);

char *StrDup(const char *s); /* Look up man for strdup to see how to use */

char *StrCat(char *dest, const char *src);

char *StrnCat(char *dest, const char *src, size_t n);

char *StrStr(const char *haystack, const char *needle);

size_t StrSpn(const char *s, const char *accept);

char *StrTok(char *str, const char *delim);


#endif
