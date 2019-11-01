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

  OnUpdateFunc on_update;
} GameObject;

void init_game_object(GameObject* object);
void render_game_object(GameObject object, HDC main_dc);
