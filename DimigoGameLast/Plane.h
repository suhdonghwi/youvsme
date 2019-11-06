#pragma once
#include "GameObject.h"
#include "WaveAudio.h"

typedef enum tagPlaneState {
  PLANE_READY,
  PLANE_FLYING,
  PLANE_DESCENDING,
  PLANE_LANDED
} PlaneState;

typedef struct tagPlaneData {
  WaveData wave_data;
  PlaneState state;
} PlaneData;

GameObject* create_plane(bool coco_plane);
