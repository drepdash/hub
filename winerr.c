#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <varargs.h>
#include "winerr.h"

/*
** FIXME: Doesn't do what err(3) does.
*/
void
err(int eval, const char *fmt, ...)
{
    va_list args;

    va_start(args, fmt);
    fprintf(stderr, "Fatal Error: ");
    fprintf(stderr, fmt, args);
    fprintf(stderr, "\n", args);
    va_end(args);
	exit(eval);
}

void
errx(int eval, const char *fmt, ...)
{
    va_list args;

    va_start(args, fmt);
    fprintf(stderr, "Fatal Error: ");
    fprintf(stderr, fmt, args);
    fprintf(stderr, "\n", args);
    va_end(args);
    exit(eval);
}
