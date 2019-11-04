#include "BitmapDisplay.h"

int sleep_duration;

void after_render_bitmap_display(GameObject* bitmap_display, HDC main_dc) {
  Sleep(sleep_duration);
  bitmap_display->alive = false;
}

GameObject* create_bitmap_display(HBITMAP* bitmap, int duration) {
  GameObject* bitmap_display = init_game_object(bitmap);
  bitmap_display->after_render = after_render_bitmap_display;
  sleep_duration = duration;

  return bitmap_display;
}
