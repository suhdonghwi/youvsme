#pragma once
#include <Windows.h>

typedef void (*OnUpdateFunc)(struct tagGameObject*);

typedef struct tagPos {
  int x;
  int y;
} Pos;

typedef struct tagGameObject {
  HBITMAP* sprites;
  Pos pos;

  OnUpdateFunc on_update;
} GameObject;
