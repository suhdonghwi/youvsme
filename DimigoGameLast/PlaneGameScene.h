#pragma once
#include "GameScene.h"

typedef struct tagPlaneGameData {
  int background_offset;
  GameObject *plane, *fallen_plane, *player;
} PlaneGameData;

GameScene* create_plane_game_scene(bool coco_turn, GameObject* fallen_plane);
