#pragma once
#include <Windows.h>

typedef void (*OnUpdateFunc)(struct tagGameObject*);

typedef struct tagPos {
  int x;
  int y;
} Pos;

typedef struct tagGameObject {
  HBITMAP* sprites;
  size_t sprite_index;
  Pos pos;

  double scale;

  OnUpdateFunc on_update;
} GameObject;

GameObject* init_game_object();
void render_game_object(GameObject* object, HDC main_dc);
