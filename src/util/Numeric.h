#pragma once
#include <util/String.h>
#include "../kernel/Kernel.h"

extern void itoa(int s, char* buffer);
extern void itoa(unsigned int s, char* buffer);
extern String to_string(unsigned int s);
extern String to_string(int s);
extern String to_string(float s);
extern String to_string(float s);
extern String to_string(double s);