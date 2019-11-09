#include "String.h"
#include "GameScene.h"
#include "SpriteResources.h"

extern bool g_pressed_map[0xFE];
extern GameScene* g_new_scene;

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

void on_collide_string(GameObject* string, GameObject* object) {
  if (strcmp(object->tag, "flag") == 0) {
    if (object->sprite_index == 0) {
      g_new_scene = create_game_result_scene(false);
    } else {
      g_new_scene = create_game_result_scene(true);
    }
  }
}

GameObject* create_string() {
  GameObject* string = init_game_object(string_sprites);
  string->scale = 8;
  string->pos = (Pos){170, 350};
  string->collidable = true;

  string->on_render = on_render_string;
  string->on_collide = on_collide_string;

  StringData* data = malloc(sizeof(StringData));
  if (data == NULL) return NULL;
  data->coco_pressed = false;
  data->dingding_pressed = false;

  string->data = data;

  return string;
}