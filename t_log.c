#include <stdio.h>
#include "log.h"

int main(int argc, char *argv[])
{
	if (argc > 1)
		log_file_open(NULL);
	else
		log_file_open("test.log");

	log_begin("initializ test program\n");
	log_begin("check every module ");
	log_continue("first second three ...\n");
	log_begin("test program run successfully\n");
	log_file_close();

	return 0;
}
