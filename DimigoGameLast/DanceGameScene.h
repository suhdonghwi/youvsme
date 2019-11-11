#pragma once
#include "GameScene.h"

typedef struct tagDanceGameSceneData {
  GameObject *coco, *dingding;

  bool is_coco_turn;
} DanceGameSceneData;

GameScene* create_dance_game_scene();
