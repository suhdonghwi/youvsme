#pragma once
#include <stdbool.h>

#include <Windows.h>

typedef void (*OnUpdateFunc)(struct tagGameObject*);

typedef struct tagPos {
  int x;
  int y;
} Pos;

typedef struct tagGameObject {
  bool alive;

  HBITMAP* sprites;
  size_t sprite_index;
  Pos pos;

  double scale;

  OnUpdateFunc on_update;
} GameObject;

GameObject* init_game_object();
void deinit_game_object(GameObject* object);
void render_game_object(GameObject* object, HDC main_dc);
