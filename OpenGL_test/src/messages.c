#include <stdarg.h>
#include "global.h"
#include <stdio.h>

void debug(char *message,...){
	va_list args;
	va_start(args, message);
	printf("# Debug: ");
	vprintf(message, args);
	printf("\n");
	va_end(args);
}

void error(char *message,...){
	va_list args;
	va_start(args, message);
	fprintf(stderr, "ERROR: ");
	vfprintf(stderr, message, args);
	fprintf(stderr,"\n");
	va_end(args);
	exit(1);
}

