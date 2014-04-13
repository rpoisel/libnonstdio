/*
 * nonstdio.c
 *
 *  Created on: Apr 13, 2014
 *      Author: rpoisel
 */

#include <stdio.h>

#include "nonstdio.h"

int func(const char* fmt, ...)
{
    int lReturn = 0;
    va_list arglist;

    va_start(arglist, fmt);
    lReturn = vfunc(fmt, arglist);
    va_end(arglist);
    return lReturn;
}

int vfunc(const char* fmt, va_list args)
{
    int i = 0;
    for (i = va_arg(args, int); i >= 0; i = va_arg(args, int))
    {
        printf("%d ", i);
    }
    return 0;
}
