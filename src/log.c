#include "../include/log.h"

#include <stdarg.h>
#include <time.h>

static const char *level_str[] = { "DEBUG", "INFO", "WARN", "ERROR" };

static FILE *log_file = NULL;

void log_init(const char *path) {
    log_file = fopen(path, "a");
}

void log_close(void) {
    if (log_file) { fclose(log_file); log_file = NULL; }
}

void log_write(LogLevel level, const char *file, int line, const char *fmt, ...) {
    FILE *out = log_file ? log_file : stderr;

    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    char ts[20];
    strftime(ts, sizeof(ts), "%Y-%m-%d %H:%M:%S", tm);

    fprintf(out, "[%s] [%-5s] (%s:%d) ", ts, level_str[level], file, line);

    va_list args;
    va_start(args, fmt);
    vfprintf(out, fmt, args);
    va_end(args);

    fprintf(out, "\n");
    fflush(out);
}