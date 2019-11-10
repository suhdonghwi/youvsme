#pragma once
#include "GameObject.h"

typedef struct tagStringData {
  int coco_combo[3], dingding_combo[3];
  int coco_index, dingding_index;
  bool coco_pulling, dingding_pulling;
} StringData;

GameObject* create_string();
