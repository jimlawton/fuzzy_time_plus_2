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
// 5:01-03   gone      five      o'clock
// 5:04      nearly    five past five
// 5:05                five past five
// 5:06-08   after     five past five
// 5:09      nearly    ten past  five
// 5:10                ten past  five
// ..
// 5:44      quarter   to        six
// 5:45      quarter   to        six
// 5:46-48   quarter   to        six
// 5:49      nearly    ten to    six
// 5:50                ten to    six

void fuzzy_time(int hours, int minutes, char* line1, char* line2, char* line3) {

    if (minutes % 5 >= 1 && minutes % 5 < 4) {
        strcpy(line1, "gone");
    }

    if (minutes % 5 == 4) {
        strcpy(line1, "nearly");
    }

    if (minutes >= 34) {
        hours += 1;
    }

    if (hours > 12)
        hours -= 12;

    if (minutes == 0) {
        strcpy(line1, "it's");
        strcpy(line2, HOURS[hours]);
        strcpy(line3, "o'clock");
    } else if (minutes >= 1 && minutes < 4) {
        strcpy(line2, HOURS[hours]);
        strcpy(line3, "o'clock");
    } else if (minutes >= 4 && minutes < 9) {
        strcpy(line2, "5 past");
        strcpy(line3, HOURS[hours]);
    } else if (minutes >= 9 && minutes < 14) {
        strcpy(line2, "10 past");
        strcpy(line3, HOURS[hours]);
    } else if (minutes >= 14 && minutes < 19) {
        strcpy(line1, "quarter");
        strcpy(line2, "past");
        strcpy(line3, HOURS[hours]);
    } else if (minutes >= 19 && minutes < 24) {
        strcpy(line2, "20 past");
        strcpy(line3, HOURS[hours]);
    } else if (minutes >= 24 && minutes < 29) {
        strcpy(line2, "25 past");
        strcpy(line3, HOURS[hours]);
    } else if (minutes >= 29 && minutes < 34) {
        strcpy(line1, "half");
        strcpy(line2, "past");
        strcpy(line3, HOURS[hours]);
    } else if (minutes >= 34 && minutes < 39) {
        strcpy(line2, "25 to");
        strcpy(line3, HOURS[hours]);
    } else if (minutes >= 39 && minutes < 44) {
        strcpy(line2, "20 to");
        strcpy(line3, HOURS[hours]);
    } else if (minutes >= 44 && minutes < 49) {
        strcpy(line1, "quarter");
        strcpy(line2, "to");
        strcpy(line3, HOURS[hours]);
    } else if (minutes >= 49 && minutes < 54) {
        strcpy(line2, "10 to");
        strcpy(line3, HOURS[hours]);
    } else if (minutes >= 54 && minutes < 59) {
        strcpy(line2, "5 to");
        strcpy(line3, HOURS[hours]);
    } else if (minutes == 59) {
        strcpy(line2, HOURS[hours]);
        strcpy(line3, "o'clock");
    }
}
