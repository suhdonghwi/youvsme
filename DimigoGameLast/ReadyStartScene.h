#pragma once
#include "GameScene.h"

typedef struct tagReadyStartData {
  int index;
  int slide_size;
  GameScene* dest_scene;
  HBITMAP* slide_bitmaps;
  Pos render_pos;
} ReadyStartData;

GameScene* create_readystart_scene(GameScene* scene, HBITMAP* slides, int size,
                                   Pos pos);
