#pragma once
#include "GameScene.h"

typedef struct tagHomeSceneData {
  size_t index;
} HomeSceneData;

GameScene* create_home_scene();
