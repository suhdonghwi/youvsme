#include <stdlib.h>

#include "GameResultScene.h"
#include "GameScene.h"
#include "SpriteResources.h"
#include "String.h"

extern SHORT g_pressed_map[256];
extern SHORT g_prev_pressed_map[256];
extern GameScene* g_new_scene;

bool is_pressed(int index) {
  return g_pressed_map[index] && !g_prev_pressed_map[index];
}

void randomize_combo(int* combo) {
  for (int i = 0; i < 3; i++) combo[i] = 1 + rand() % 3;
}

DWORD WINAPI coco_pull(LPVOID param) {
  srand((unsigned int)time(NULL));
  GameObject* string = (GameObject*)param;
  StringData* data = (StringData*)string->data;

  data->coco_pulling = true;
  for (int i = 0; i < 10; i++) {
    string->pos.x -= 3;
    Sleep(10);
  }
  data->coco_pulling = false;

  data->coco_index = 0;
  randomize_combo(data->coco_combo);
  return 0;
}

void on_render_string(GameObject* string, HDC main_dc) {
  StringData* data = (StringData*)string->data;

  SHORT coco_pressed[3] = {is_pressed(0x31), is_pressed(0x32),
                           is_pressed(0x33)};

  for (int i = 0; i < 3; i++) {
    if (coco_pressed[i] && !data->coco_pulling) {
      if (data->coco_combo[data->coco_index] == i + 1) {
        data->coco_index++;
        if (data->coco_index >= 3) {
          data->coco_thread =
              CreateThread(NULL, 0, coco_pull, (LPVOID)string, 0, NULL);
          CloseHandle(data->coco_thread);
        }
      } else {
        data->coco_index = 0;
      }
    }
  }

  for (int i = 0; i < 3; i++) {
    render_bitmap(key_sprites[data->coco_combo[i] - 1], main_dc,
                  (Pos){string->pos.x + 38 + i * 43, string->pos.y - 40}, 5);
    if (i < data->coco_index)
      render_bitmap(sign_sprites[0], main_dc,
                    (Pos){string->pos.x + 38 + i * 43, string->pos.y - 40}, 5);
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
  data->coco_combo[0] = 1;
  data->coco_combo[1] = 3;
  data->coco_combo[2] = 2;

  data->coco_index = 0;
  data->dingding_index = 0;

  data->coco_thread = NULL;
  data->coco_pulling = false;

  string->data = data;

  return string;
}