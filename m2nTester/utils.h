/* 
 * File:   utils.h
 * Author: Sebastián Salazar Molina <ssalazar@orangepeople.cl>
 *
 * Created on December 27, 2013, 7:54 PM
 */

#ifndef UTILS_H
#define	UTILS_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

#define PANIC( a ) { fprintf(stderr,"%s", a ); }

    typedef unsigned char byte;

    int print_time(void);
    char* str_now();
    byte* get_data(char* data_file);
    char* hex2str(byte* hex, unsigned int len);
    byte* static_data();

#ifdef	__cplusplus
}
#endif

#endif	/* UTILS_H */
