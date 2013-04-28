/*
 * test.c
 * Simple host tester for fuzzy time.
 *
 * Compile with:
 *   # gcc -o fuzzy_time_test ./test.c ./english_time.c 
 *
 *  Created on: 28 Apr 2013
 *      Author: jiml
 */

#include <stdio.h>
#include <string.h>

#include "english_time.h"

#define LINE_BUFFER_SIZE 50

int main()
{
    int hour, minute;
    char line1[LINE_BUFFER_SIZE];
    char line2[LINE_BUFFER_SIZE];
    char line3[LINE_BUFFER_SIZE];

    printf("| HH:MM | %-16s | %-16s | %-16s |\n", "Line 1", "Line 2", "Line 3");
    for (hour=0; hour <24; hour++) {
        for (minute=0; minute<60; minute++) {
            fuzzy_time(hour, minute, line1, line2, line3);
            printf("| %02d:%02d | %-16s | %-16s | %-16s |\n", hour, minute, line1, line2, line3);
        }
    }
}
