#include "fuzzy_time.h"
#include "string.h"

static const char* const HOURS[] = {
    "twelve",
    "one",
    "two",
    "three",
    "four",
    "five",
    "six",
    "seven",
    "eight",
    "nine",
    "ten",
    "eleven",
    "twelve",
};

// Time      line1     line2     line3
// ----      --------  --------  --------
// 5:00      it's      five      o'clock
// 5:01      just gone five      o'clock
// 5:02-03             gone      five
// 5:04      nearly    five past five
// 5:05                five past five
// 5:06      just gone five past five
// 5:07-08   gone      five past five
// 5:09      nearly    ten past  five
// 5:10                ten past  five
// ..
// 5:44      nearly    quarter to six
// 5:45                quarter to six
// 5:46      just gone quarter to six
// 5:47-48   gone      quarter to six
// 5:49      nearly    ten to    six
// 5:50                ten to    six

void fuzzy_time(int hours, int minutes, char* line1, char* line2, char* line3) {
    // Line 1
    strcpy(line1, "");
    if (minutes == 0) {
        strcat(line1, "it's");
    } else if (minutes % 5 == 1) {
        strcat(line1, "just gone");
    } else if (minutes % 5 > 1 && minutes % 5 < 4) {
        strcat(line1, "gone");
    } else if (minutes % 5 == 4) {
        strcat(line1, "nearly");
    }

    if (hours > 12)
        hours -= 12;

    // Line 2
    strcpy(line2, "");
    if (minutes == 59 || (minutes >= 0 && minutes < 4)) {
        if (minutes == 59) {
            hours += 1;
            if (hours > 12)
                hours -= 12;
        }
        strcat(line2, HOURS[hours]);
    } else {
        if ((minutes >= 4 && minutes < 9) || (minutes >= 54 && minutes < 59)) {
            strcat(line2, "five");
        } else if ((minutes >= 9 && minutes < 14) || (minutes >= 49 && minutes < 54)) {
            strcat(line2, "ten");
        } else if ((minutes >= 14 && minutes < 19) || (minutes >= 44 && minutes < 49)) {
            strcat(line2, "quarter");
        } else if ((minutes >= 19 && minutes < 24) || (minutes >= 39 && minutes < 44)) {
            strcat(line2, "twenty");
        } else if ((minutes >= 24 && minutes < 29) || (minutes >= 34 && minutes < 39)) {
            strcat(line2, "twenty five");
        } else if (minutes >= 29 && minutes < 34) {
            strcat(line2, "half");
        }
        if (minutes < 34) {
            strcat(line2, " past");
        } else {
            hours += 1;
            if (hours > 12)
                hours -= 12;
            strcat(line2, " to");
        }
    }

    // Line 3
    strcpy(line3, "");
    if (minutes == 59 || (minutes >= 0 && minutes < 4)) {
        strcat(line3, "o'clock");
    } else {
        strcat(line3, HOURS[hours]);
    }
}
