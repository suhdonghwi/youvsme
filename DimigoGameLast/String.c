#include "String.h"
#include "GameResultScene.h"
#include "GameScene.h"
#include "SpriteResources.h"

extern SHORT g_pressed_map[256];
extern SHORT g_prev_pressed_map[256];
extern GameScene* g_new_scene;

bool is_pressed(int index) {
  return g_pressed_map[index] && !g_prev_pressed_map[index];
}

void add_to_combo(int i, int* buf) {
  for (int j = 0; j < 3; j++) {
    if (buf[j] == 0) {
      buf[j] = i;
      break;
    }
  }
}

void on_render_string(GameObject* string, HDC main_dc) {
  StringData* data = (StringData*)string->data;

  if (is_pressed(0x31)) {
    add_to_combo(1, data->coco_combo);
  } else if (is_pressed(0x32)) {
    add_to_combo(2, data->coco_combo);
  } else if (is_pressed(0x33)) {
    add_to_combo(3, data->coco_combo);
  }
}

void on_collide_string(GameObject* string, GameObject* object) {
  if (strcmp(object->tag, "flag") == 0) {
    if (object->sprite_index == 0) {
      g_new_scene = create_game_result_scene(true);
    } else {
      g_new_scene = create_game_result_scene(false);
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
  memset(data->coco_combo, 0, sizeof(data->coco_combo));
  memset(data->dingding_combo, 0, sizeof(data->dingding_combo));

  string->data = data;

  return string;
}