/* 
 * File:   logger.h
 * Author: seba
 *
 * Created on 28 de diciembre de 2013, 12:12 PM
 */

#ifndef LOGGER_H
#define	LOGGER_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <malloc.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

#define INFO_LOG 0
#define ERROR_LOG 1
#define DEBUG_LOG 2

    /* The key used to associate a log file pointer with each thread.
     */
    static pthread_key_t logger_key;

    void initialize_log();
    void write_log(const char* message);
    void close_log(void* thread_log);
    void logger(int level, char* message);

#ifdef	__cplusplus
}
#endif

#endif	/* LOGGER_H */

