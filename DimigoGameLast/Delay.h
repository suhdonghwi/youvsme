#pragma once
#include <stdbool.h>
#include <time.h>

typedef clock_t delay_t;

bool after_delay(delay_t* delay, double seconds);
double elapsed_time(delay_t delay);
