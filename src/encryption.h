#ifndef ENCRYPTION_H
#define ENCRYPTION_H
#include <unistd.h>
#include "common.h"
#include <limits.h>
#include <assert.h>

#define MAX_PWD_SIZE (30)

void encode(char *, char *, char*);

void decode(char *, char *, char*);

#endif // ENCRYPTION_H