#pragma once
#include "GameObject.h"

typedef struct tagStringData {
  int coco_combo[3], dingding_combo[3];
  int coco_index, dingding_index;
  HANDLE coco_thread;
  bool coco_pulling;
} StringData;

GameObject* create_string();
