#pragma once
#include <time.h>

#include "GameObject.h"
#include "WaveAudio.h"

typedef enum tagDiskState {
  DISK_READY,
  DISK_FLYING,
  DISK_DESCENDING,
  DISK_LANDED
} DiskState;

typedef struct tagDiskData {
  int speed;

  WaveData wave_data;
  bool initialized_wave;

  DiskState state;
  int descend_count;
  int shadow_y_pos;

  clock_t last_turn_clock;
} DiskData;

GameObject* create_disk(bool coco_disk, Pos pos, int speed);
