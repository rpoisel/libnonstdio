/*
 * nonstdio.c
 *
 *  Created on: Apr 13, 2014
 *      Author: rpoisel
 */

#include <stdio.h>

#include "nonstdio.h"

#define NUM_BUF_LEN 10

typedef enum
{
    NONE, PERCENT, STRING, DECIMAL, HEX
} state_input;

static int printd(char** buf, size_t* size, int number);

int non_snprintf(char* buf, size_t size, const char* fmt, ...)
{
    int lReturn = 0;
    va_list arglist;

    va_start(arglist, fmt);
    lReturn = non_vsnprintf(buf, size, fmt, arglist);
    va_end(arglist);
    return lReturn;
}

int non_vsnprintf(char* buf, size_t size, const char* fmt, va_list args)
{
    state_input state = NONE;
    for (; *fmt != '\0' && size > 1; fmt++)
    {
        if (NONE == state)
        {
            if (*fmt == '%')
            {
                state = PERCENT;
            }
            else
            {
                *buf = *fmt;
                buf++;
                size--;
            }
        }
        else if (PERCENT == state)
        {
            switch (*fmt)
            {
                case 's':
                    /* process string */
                    break;
                case 'd':
                    /* process integer */
                    printf("printd-result: %d\n", printd(&buf, &size, va_arg(args, int)));
                    break;
                default:
                    /* conversion specifier unknown => ignore*/
                    break;
            }
            state = NONE;
        }
    }
    *buf = '\0';

    return 0;
}

static int printd(char** buf, size_t* size, int number)
{
    char num_buf[NUM_BUF_LEN] = { '\0' };
    int cnt = 0;
    int i = 0;

    /* obtain numbers in reverse order */
    while (number > 0)
    {
        num_buf[cnt] = '0' + number % 10;
        cnt++;
        number /= 10;
    }

    /* write reverse numbers in reverse order into the buffer */
    for (i = cnt - 1; i >= 0 && *size > 1; i--)
    {
        **buf = num_buf[i];
        (*buf)++;
        (*size)--;
    }

    return cnt - 1 - i;
}
