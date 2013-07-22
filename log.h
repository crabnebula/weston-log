#ifndef _LOG_H
#define _LOG_H

extern void log_file_open(const char *filename);
extern void log_file_close(void);
extern int log_begin(const char *fmt, ...);
extern int log_continue(const char *fmt, ...);

#endif
