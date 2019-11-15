#include <stdbool.h>

#include "KeyInput.h"

SHORT g_pressed_map[256] = {
    false,
};
SHORT g_prev_pressed_map[256] = {
    false,
};

// 키 입력 정보를 담고 있는 배열을 갱신합니다.
void update_pressed_map() {
  memcpy(g_prev_pressed_map, g_pressed_map, sizeof(g_prev_pressed_map));
  for (int i = 0; i < 256; i++) {
    g_pressed_map[i] = GetAsyncKeyState(i);
  }
}

// 주어진 번호의 키가 눌려있는지를 bool 형식으로 반환합니다.
bool is_pressed(int index) {
  return g_pressed_map[index] && !g_prev_pressed_map[index];
}
