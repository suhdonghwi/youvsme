#pragma once
#include "GameScene.h"

typedef struct tagDiskGameData {
  int background_offset;
  GameObject *disk, *player;
  Pos fallen_pos;
} DiskGameData;

GameScene* create_disk_game_scene(bool coco_turn, Pos fallen_pos);
