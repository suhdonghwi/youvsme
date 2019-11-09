#include "String.h"
#include "SpriteResources.h"

extern bool g_pressed_map[0xFE];

void on_render_string(GameObject* string, HDC main_dc) {
  StringData* data = (StringData*)string->data;

  if ((GetAsyncKeyState(0x41) & 0x8001) && !data->coco_pressed) {
    string->pos.x -= 10;
    data->coco_pressed = true;
  } else if (GetAsyncKeyState(0x41) == 0) {
    data->coco_pressed = false;
  }

  if ((GetAsyncKeyState(0x4C) & 0x8001) && !data->dingding_pressed) {
    string->pos.x += 10;
    data->dingding_pressed = true;
  } else if (GetAsyncKeyState(0x4C) == 0) {
    data->dingding_pressed = false;
  }
}

GameObject* create_string() {
  GameObject* string = init_game_object(string_sprites);
  string->scale = 5;
  string->pos = (Pos){250, 420};
  string->on_render = on_render_string;

  StringData* data = malloc(sizeof(StringData));
  if (data == NULL) return NULL;
  data->coco_pressed = false;
  data->dingding_pressed = false;
  string->data = data;

  return string;
}