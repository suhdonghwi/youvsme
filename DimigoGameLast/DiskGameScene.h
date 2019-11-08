#pragma once
#include "GameScene.h"

typedef struct tagDiskGameData {
  int background_offset;
  GameObject *disk, *fallen_disk, *player;
} DiskGameData;

GameScene* create_disk_game_scene(bool coco_turn, GameObject* fallen_disk);
