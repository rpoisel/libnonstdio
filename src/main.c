/*
 * main.c
 *
 *  Created on: Apr 13, 2014
 *      Author: rpoisel
 */

#include <stdlib.h>
#include <stdio.h>

#include "nonstdio.h"

int main(void)
{
    printf("Return value: %d", func("Hello World", 1, 2, 3, -1));
    return EXIT_SUCCESS;
}
