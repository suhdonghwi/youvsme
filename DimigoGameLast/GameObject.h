#pragma once
#include <stdbool.h>

#include <Windows.h>

typedef void (*OnUpdateFunc)(struct tagGameObject*);
typedef void (*OnDestroyFunc)(struct tagGameObject*);
typedef void (*OnCollideFunc)(struct tagGameObject*, struct tagGameObject*);

typedef struct tagPos {
  int x;
  int y;
} Pos;

typedef struct tagGameObject {
  bool alive;
  bool collidable;

  char tag[100];

  HBITMAP* sprites;
  size_t sprite_index;
  Pos pos;

  double scale;

  OnUpdateFunc on_update;
  OnDestroyFunc on_destroy;
  OnCollideFunc on_collide;
} GameObject;

GameObject* init_game_object();
void deinit_game_object(GameObject* object);
void render_game_object(GameObject* object, HDC main_dc);

RECT get_game_object_rect(GameObject* object);
