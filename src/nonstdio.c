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

static int printd(char** buf, int number);

int non_sprintf(char* buf, const char* fmt, ...)
{
    int lReturn = 0;
    va_list arglist;

    va_start(arglist, fmt);
    lReturn = non_vsprintf(buf, fmt, arglist);
    va_end(arglist);
    return lReturn;
}

int non_vsprintf(char* buf, const char* fmt, va_list args)
{
    state_input state = NONE;
    for (; *fmt != '\0'; fmt++)
    {
        if (state == NONE)
        {
            if (*fmt == '%')
            {
                state = PERCENT;
            }
            else
            {
                *buf = *fmt;
                buf++;
            }
        }
        else if (state == PERCENT)
        {
            switch (*fmt)
            {
                case 's':
                    /* process string */
                    break;
                case 'd':
                    /* process integer */
                    /* TODO check return value of printd and pass
                     * along number of characters that could be processed
                     */
                    printd(&buf, va_arg(args, int));
                    break;
                default:
                    /* conversion specifier unknown */
                    break;
            }
            state = NONE;
        }
    }
    buf = '\0';

    return 0;
}

static int printd(char** buf, int number)
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
    for (i = cnt - 1; i >= 0; i--)
    {
        **buf = num_buf[i];
        (*buf)++;
    }

    return cnt;
}
