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


#define PANIC( a ) { fprintf(stderr,"%s", a ); }

    int printTime(void);


#ifdef	__cplusplus
}
#endif

#endif	/* UTILS_H */

