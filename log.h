#ifndef _LOG_H
#define _LOG_H

extern log_file_open(const char *filename);
extern log_file_close(void);
extern log_begin(const char *fmt, ...);
extern log_continue(const char *fmt, ...);

#endif
