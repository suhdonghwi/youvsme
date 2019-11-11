#include <stdbool.h>

#include "KeyInput.h"

SHORT g_pressed_map[256] = {
    false,
};
SHORT g_prev_pressed_map[256] = {
    false,
};

void update_pressed_map() {
  memcpy(g_prev_pressed_map, g_pressed_map, sizeof(g_prev_pressed_map));
  for (int i = 0; i < 256; i++) {
    g_pressed_map[i] = GetAsyncKeyState(i);
  }
}

bool is_pressed(int index) {
  return g_pressed_map[index] && !g_prev_pressed_map[index];
}
