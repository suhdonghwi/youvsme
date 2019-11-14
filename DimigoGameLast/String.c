#pragma warning(disable : 6001 6385)
#include <stdlib.h>
#include <time.h>

#include "DanceGameScene.h"
#include "GameResultScene.h"
#include "GameScene.h"
#include "KeyInput.h"
#include "SpriteResources.h"
#include "StoryScene.h"
#include "String.h"

extern SHORT g_pressed_map[256];
extern SHORT g_prev_pressed_map[256];
extern GameScene* g_new_scene;
extern int g_coco_score;

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

DWORD WINAPI dingding_pull(LPVOID param) {
  srand((unsigned int)time(NULL));
  GameObject* string = (GameObject*)param;
  StringData* data = (StringData*)string->data;

  data->dingding_pulling = true;
  for (int i = 0; i < 10; i++) {
    string->pos.x += 3;
    Sleep(10);
  }
  data->dingding_pulling = false;

  data->dingding_index = 0;
  randomize_combo(data->dingding_combo);
  return 0;
}

void on_render_string(GameObject* string, HDC main_dc) {
  StringData* data = (StringData*)string->data;

  SHORT coco_pressed[3] = {is_pressed(0x31), is_pressed(0x32),
                           is_pressed(0x33)};
  SHORT dingding_pressed[3] = {is_pressed(0x37), is_pressed(0x38),
                               is_pressed(0x39)};

  for (int i = 0; i < 3; i++) {
    if (coco_pressed[i] && !data->coco_pulling) {
      if (data->coco_combo[data->coco_index] == i + 1) {
        data->coco_index++;
        if (data->coco_index >= 3) {
          HANDLE thread =
              CreateThread(NULL, 0, coco_pull, (LPVOID)string, 0, NULL);
          if (thread) CloseHandle(thread);
        }
      } else {
        data->coco_index = 0;
      }
    }

    if (dingding_pressed[i] && !data->dingding_pulling) {
      if (data->dingding_combo[data->dingding_index] == i + 1) {
        data->dingding_index++;
        if (data->dingding_index >= 3) {
          HANDLE thread =
              CreateThread(NULL, 0, dingding_pull, (LPVOID)string, 0, NULL);
          if (thread) CloseHandle(thread);
        }
      } else {
        data->dingding_index = 0;
      }
    }
  }

  for (int i = 0; i < 3; i++) {
    Pos coco_pos = {string->pos.x + 23 + i * 43, string->pos.y - 40},
        dingding_pos = {string->pos.x + 640 + i * 43, string->pos.y - 40};

    render_bitmap(key_sprites[data->coco_combo[i] - 1], main_dc, coco_pos, 5);
    if (i < data->coco_index)
      render_bitmap(sign_sprites[0], main_dc, coco_pos, 5);

    render_bitmap(key_sprites[3 + data->dingding_combo[i] - 1], main_dc,
                  dingding_pos, 5);
    if (i < data->dingding_index)
      render_bitmap(sign_sprites[0], main_dc, dingding_pos, 5);
  }
}

void on_collide_string(GameObject* string, GameObject* object) {
  StringData* data = (StringData*)string->data;
  if (strcmp(object->tag, "flag") == 0 && !data->coco_pulling &&
      !data->dingding_pulling) {
    Sleep(1000);
    g_new_scene = create_after_pull_story(object->sprite_index == 0);
  }
}

GameObject* create_string() {
  GameObject* string = init_game_object(string_sprites);
  string->scale = 6;
  string->pos = (Pos){170, 350};
  string->collidable = true;

  string->on_render = on_render_string;
  string->on_collide = on_collide_string;

  StringData* data = malloc(sizeof(StringData));
  if (data == NULL) return NULL;
  randomize_combo(data->coco_combo);
  randomize_combo(data->dingding_combo);

  data->coco_index = 0;
  data->dingding_index = 0;

  data->coco_pulling = false;
  data->dingding_pulling = false;

  string->data = data;

  return string;
}