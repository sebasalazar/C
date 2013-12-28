#include "logger.h"

void initialize_log() {
    pthread_key_create(&logger_key, close_log);
}

void write_log(const char* message) {
    FILE* fp = (FILE*) pthread_getspecific(logger_key);
    if (fp != NULL) {
        fprintf(fp, "%s\n", message);
    }
}

void close_log(void* thread_log) {
    fclose((FILE*) thread_log);
}

void logger(int level, char* message) {
    char thread_log_filename[20];
    char text[1024];
    FILE* thread_log;

    /* Generate the filename for this thread’s log file. */
    //sprintf(thread_log_filename, "thread_%d.log", (int) pthread_self());

    if (level == INFO_LOG) {
        sprintf(thread_log_filename, "info.log");
    } else if (level == ERROR_LOG) {
        sprintf(thread_log_filename, "error.log");
    } else {
        sprintf(thread_log_filename, "debug.log");
    }

    /* Open the log file. */
    thread_log = fopen(thread_log_filename, "a+");
    /* Store the file pointer in thread-specific data under logger_key. */
    pthread_setspecific(logger_key, thread_log);

    memset(text, 0, sizeof (text));
    snprintf(text, 1023, "[%s] [%d] %s", str_now(), (int) pthread_self(), message);


    write_log(text);
}

