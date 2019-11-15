#pragma once
#include "GameScene.h"

typedef struct tagGameHelpData {
  HBITMAP help_message, logo;
  Pos logo_pos;
  GameScene* dest_scene;
  HFONT font;
} GameHelpData;

GameScene* create_game_help_scene(HBITMAP help_message, HBITMAP logo,
                                  Pos logo_pos, GameScene* game_scene);

GameScene* create_disk_help_scene();
GameScene* create_pull_help_scene();
GameScene* create_dance_help_scene();
