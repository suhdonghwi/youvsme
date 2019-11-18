#pragma once
#include "GameScene.h"

typedef struct tagGameResultSceneData {
  GameScene* next_scene;
} GameResultSceneData;

GameScene* create_game_result_scene(bool coco_won, GameScene* next_scene);
