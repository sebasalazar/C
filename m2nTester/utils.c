#include "utils.h"

int printTime(void) {
    struct timeval tv;
    struct timezone tz;
    time_t t;
    gettimeofday(&tv, &tz);
    t = tv.tv_sec;

    struct tm timeinfoL;
    localtime_r(&t, &timeinfoL);

    printf("%.2d/%.2d/%.2d", timeinfoL.tm_year + 1900, timeinfoL.tm_mon + 1, timeinfoL.tm_mday);
    printf("%.2d:%.2d:%.2d.%.6d ", timeinfoL.tm_hour, timeinfoL.tm_min, timeinfoL.tm_sec, (int) tv.tv_usec);
    return (t);
}

