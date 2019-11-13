#pragma once
#include <time.h>

#include "GameObject.h"

typedef enum tagDanceDirection {
  DANCE_UP,
  DANCE_RIGHT,
  DANCE_DOWN,
  DANCE_LEFT,
  DANCE_NONE,
} DanceDirection;

typedef struct tagDancerData {
  SHORT* move_keys;
  bool is_dancing;
  bool is_imitating;

  DanceDirection* dance_queue;
  int dance_max;

  clock_t last_dance_clock;

  HFONT font;
} DancerData;

bool is_dance_queue_full(DanceDirection* queue, int max);
int dance_queue_length(DanceDirection* queue, int max);

GameObject* create_dancer(bool coco, SHORT* move_keys);
