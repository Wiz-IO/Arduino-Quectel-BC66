/*
 * libraries
 *
 *  Created on: 02.10.2018
 *      Author: Georgi Angelov
 */

#include <stddef.h>
#include "ql_system.h"
#include "ql_stdlib.h"

/* need for quectel lib bss */
extern void *memset(void *dst, int c, size_t n)
{
	if (n)
	{
		char *d = dst;
		do
		{
			*d++ = c;
		} while (--n);
	}
	return dst;
}


//https://opensource.apple.com/source/Libc/Libc-167/string.subproj/strtok.c.auto.html
char *wiz_strtok(char *s, const char *delim)
{
	char *spanp;
	int c, sc;
	char *tok;
	static char *last;
	if (s == NULL && (s = last) == NULL)
		return (NULL);

/*
 * Skip (span) leading delimiters (s += strspn(s, delim), sort of).
 */
cont:
	c = *s++;
	for (spanp = (char *)delim; (sc = *spanp++) != 0;)
	{
		if (c == sc)
			goto cont;
	}

	if (c == 0)
	{ /* no non-delimiter characters */
		last = NULL;
		return (NULL);
	}
	tok = s - 1;
/*
 * Scan token (scan for delimiters: s += strcspn(s, delim), sort of).
 * Note that delim must have one NUL; we stop if we see that, too.
 */
	for (;;)
	{
		c = *s++;
		spanp = (char *)delim;
		do
		{
			if ((sc = *spanp++) == c)
			{
				if (c == 0)
					s = NULL;
				else
					s[-1] = 0;
				last = s;
				return (tok);
			}
		} while (sc != 0);
	}
	/* NOTREACHED */
	return 0;
}

//https://opensource.apple.com/source/xnu/xnu-1228.7.58/bsd/libkern/strsep.c
char *wiz_strsep(char **stringp, const char *delim)
{
	char *s;
	const char *spanp;
	int c, sc;
	char *tok;
	if ((s = *stringp) == NULL)
		return (NULL);
	for (tok = s;;)
	{
		c = *s++;
		spanp = delim;
		do
		{
			if ((sc = *spanp++) == c)
			{
				if (c == 0)
					s = NULL;
				else
					s[-1] = 0;
				*stringp = s;
				return (tok);
			}
		} while (sc != 0);
	}
	/* NOTREACHED */
	return 0;
}
