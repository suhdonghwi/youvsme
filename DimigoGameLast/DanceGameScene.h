#pragma once
#include <time.h>

#include "Delay.h"
#include "GameScene.h"

typedef enum tagDanceGameSceneState {
  STATE_IMITATING,
  STATE_DINGDING_DANCING,
  STATE_COCO_DANCING,
} DanceGameSceneState;

typedef struct tagDanceGameSceneData {
  GameObject *coco, *dingding;

  DanceGameSceneState state;

  Pos background_pos;
  double background_scale;

  int previous_length;
  enum tagDanceDirection* to_imiate_queue;

  clock_t imitate_clock;
  double imitate_time;

  size_t dance_count;

  delay_t speedup_show_delay, speedup_blink_delay;
  bool show_speed_up;
} DanceGameSceneData;

GameScene* create_dance_game_scene();
