#pragma once
#include <stdbool.h>

#include <Windows.h>

typedef void (*OnDestroyFunc)(struct tagGameObject*);
typedef void (*OnCollideFunc)(struct tagGameObject*, struct tagGameObject*);
typedef void (*OnRender)(struct tagGameObject*, HDC);
typedef void (*AfterRender)(struct tagGameObject*, HDC);

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

  void* data;

  OnDestroyFunc on_destroy;
  OnCollideFunc on_collide;
  OnRender on_render;
  AfterRender after_render;
} GameObject;

GameObject* init_game_object(HBITMAP* sprites);
void deinit_game_object(GameObject* object);

void render_bitmap(HBITMAP bitmap, HDC main_dc, Pos pos, double scale);
void render_game_object(GameObject* object, HDC main_dc);

RECT get_game_object_rect(GameObject* object);
