#pragma once
#include "GameScene.h"

typedef struct tagGameHelpData {
  HBITMAP help_message, logo;
  GameScene* dest_scene;
} GameHelpData;

GameScene* create_game_help_scene(HBITMAP help_message, HBITMAP logo,
                                  GameScene* game_scene);
