#pragma once

#include <util/Doc.h>

extern void* malloc(unsigned int size);
extern void* realloc(void* data, unsigned int size);
extern void free(void* data);