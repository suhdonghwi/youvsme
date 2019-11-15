#include "Delay.h"

// delay_t 데이터를 기준으로 seconds 인수에 주어진 시간 (단위 : 초) 만큼
// 지났는지 지나지 않았는지 bool 형식으로 반환합니다.
bool after_delay(delay_t* delay, double seconds) {
  delay_t current = clock();

  if (((double)current - *delay) / CLOCKS_PER_SEC >= seconds) {
    *delay = current;
    return true;
  }

  return false;
}

// delay_t 데이터를 기준으로 현재 몇 초가 지났는지 double 형식으로 반환합니다.
double elapsed_time(delay_t delay) {
  delay_t current = clock();
  return ((double)current - delay) / CLOCKS_PER_SEC;
}
