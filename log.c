/*
 * Copyright © 2012 Martin Minarik
 *
 * Permission to use, copy, modify, distribute, and sell this software and
 * its documentation for any purpose is hereby granted without fee, provided
 * that the above copyright notice appear in all copies and that both that
 * copyright notice and this permission notice appear in supporting
 * documentation, and that the name of the copyright holders not be used in
 * advertising or publicity pertaining to distribution of the software
 * without specific, written prior permission.  The copyright holders make
 * no representations about the suitability of this software for any
 * purpose.  It is provided "as is" without express or implied warranty.
 *
 * THE COPYRIGHT HOLDERS DISCLAIM ALL WARRANTIES WITH REGARD TO THIS
 * SOFTWARE, INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND
 * FITNESS, IN NO EVENT SHALL THE COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER
 * RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF
 * CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
 * CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include <stdio.h>
#include <stdarg.h>
#include <sys/time.h>
#include <time.h>

static FILE *log_file = NULL;
static int cached_tm_mday = -1;

void log_file_open(const char *filename)
{
	if (filename != NULL)
		log_file = fopen(filename, "a");

	if (log_file == NULL)
		log_file = stderr;
	else
		setvbuf(log_file, NULL, _IOLBF, 256);
}

void log_file_close(void)
{
	if (log_file != NULL && log_file != stderr)
		fclose(log_file);
	log_file = stderr;
}

static int log_timestamp(void)
{
	int l;
	struct timeval tv;
	struct tm *tm;
	char s[128];

	gettimeofday(&tv, NULL);
	tm = localtime(&tv.tv_sec);

	if (tm->tm_mday != cached_tm_mday) {
		strftime(s, sizeof(s), "%Y:%m:%d %Z", tm);
		l = fprintf(log_file, "Date: %s\n", s);
		cached_tm_mday = tm->tm_mday;
	}

	strftime(s, sizeof(s), "%H:%M:%S", tm);
	l += fprintf(log_file, "[%s.%.03ld] ", s, tv.tv_usec/1000);

	return l;
}

static int vlog(const char *fmt, va_list ap)
{
	int l;

	l = log_timestamp();
	l += vfprintf(log_file, fmt, ap);

	return l;
}

static int vlog_continue(const char *fmt, va_list ap)
{
	int l;

	l = vfprintf(log_file, fmt, ap);

	return l;
}

int log_begin(const char *fmt, ...)
{
	int l;
	va_list ap;

	va_start(ap, fmt);
	l = vlog(fmt, ap);
	va_end(ap);

	return l;
}

int log_continue(const char *fmt, ...)
{
	int l;
	va_list ap;

	va_start(ap, fmt);
	l = vlog_continue(fmt, ap);
	va_end(ap);
}
