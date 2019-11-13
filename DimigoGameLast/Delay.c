#include "Delay.h"

bool after_delay(delay_t* delay, double seconds) {
  delay_t current = clock();

  if (((double)current - *delay) / CLOCKS_PER_SEC >= seconds) {
    *delay = current;
    return true;
  }

  return false;
}

double elapsed_time(delay_t delay) {
  delay_t current = clock();
  return ((double)current - delay) / CLOCKS_PER_SEC;
}
