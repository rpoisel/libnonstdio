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

typedef enum
{
    FALSE, TRUE
} non_boolean;

#define WRITE_BUF_PRINTD(value) do { \
    (**buf) = (value); \
    (*buf)++; \
    (*size)--; \
    } while(0);

#define GENERATE_PRINTX(name, type) \
    static int print##name(char** buf, size_t* size, type number) \
    { \
        char num_buf[NUM_BUF_LEN] = { '\0' }; \
        int cnt = 0; \
        int i = 0; \
        if (0 == number) \
        { \
            if (*size > 1) \
            { \
                WRITE_BUF_PRINTD('0'); \
            } \
            else \
            { \
                return 0; \
            } \
        } \
        else if (number < 0) \
        { \
            WRITE_BUF_PRINTD('-'); \
        } \
     \
        /* obtain numbers in reverse order */ \
        while (number != 0) \
        { \
            num_buf[cnt] = '0' + (number < 0 ? number * -1 : number) % 10; \
            cnt++; \
            number /= 10; \
        } \
     \
        /* write reverse numbers in reverse order into the buffer */ \
        for (i = cnt - 1; i >= 0 && *size > 1; i--) \
        { \
            WRITE_BUF_PRINTD(num_buf[i]); \
        } \
     \
        return cnt - 1 - i; \
    } \

GENERATE_PRINTX(d, int)
GENERATE_PRINTX(u, unsigned)

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
    int lReturn = 0;
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
                lReturn++;
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
                    lReturn += printd(&buf, &size, va_arg(args, int));
                    break;
                case 'u':
                    /* process unsigned integer */
                    lReturn += printu(&buf, &size, va_arg(args, unsigned));
                    break;
                default:
                    /* conversion specifier unknown => ignore*/
                    break;
            }
            state = NONE;
        }
    }
    *buf = '\0';
    lReturn++; /* consider trailing '\0' */

    return lReturn;
}

