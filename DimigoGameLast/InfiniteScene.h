#pragma once
#include "GameScene.h"

typedef struct tagInfiniteSceneData {
  int index;
  HFONT font;
} InfiniteSceneData;

GameScene* create_infinite_scene();
