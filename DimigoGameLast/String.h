#pragma once
#include "GameObject.h"

typedef struct tagStringData {
  int coco_combo[3], dingding_combo[3];
} StringData;

GameObject* create_string();
