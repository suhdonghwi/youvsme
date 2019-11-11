#pragma once
#include "GameScene.h"

typedef struct tagDanceGameSceneData {
  GameObject *coco, *dingding;
} DanceGameSceneData;

GameScene* create_dance_game_scene();
