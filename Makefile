CFLAGS = -g -Wall

all : t_log

t_log : t_log.c log.c log.h

clean:
	@rm -v t_log
