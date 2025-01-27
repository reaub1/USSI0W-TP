#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

void forkYourself();
void redirectionStandard(const char* command);
void redirectionPipe(void);

#endif