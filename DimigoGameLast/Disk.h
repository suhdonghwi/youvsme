#pragma once
#include "GameObject.h"
#include "WaveAudio.h"

typedef enum tagDiskState {
  DISK_READY,
  DISK_FLYING,
  DISK_DESCENDING,
  DISK_LANDED
} DiskState;

typedef struct tagDiskData {
  WaveData wave_data;
  DiskState state;
  int descend_count;
} DiskData;

GameObject* create_disk(bool coco_disk);
