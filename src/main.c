/*
 * main.c
 *
 *  Created on: Apr 13, 2014
 *      Author: rpoisel
 */

#include <stdlib.h>
#include <stdio.h>

#include "nonstdio.h"

#define MAX_STR_LEN 128

int main(void)
{
    char msg[MAX_STR_LEN] = { '\0' };

    /* create our string */
    non_sprintf(msg, "Hello World: %d. ", 1234);

    /* do something with our newly created string */
    /* in this case we are using stdio just to demonstration that they interact */
    printf("Resulting string: %s", msg);

    return EXIT_SUCCESS;
}
