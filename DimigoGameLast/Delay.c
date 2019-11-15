#include "Delay.h"

// delay_t �����͸� �������� seconds �μ��� �־��� �ð� (���� : ��) ��ŭ
// �������� ������ �ʾҴ��� bool �������� ��ȯ�մϴ�.
bool after_delay(delay_t* delay, double seconds) {
  delay_t current = clock();

  if (((double)current - *delay) / CLOCKS_PER_SEC >= seconds) {
    *delay = current;
    return true;
  }

  return false;
}

// delay_t �����͸� �������� ���� �� �ʰ� �������� double �������� ��ȯ�մϴ�.
double elapsed_time(delay_t delay) {
  delay_t current = clock();
  return ((double)current - delay) / CLOCKS_PER_SEC;
}
