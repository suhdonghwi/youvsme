#pragma once
#include "GameObject.h"

typedef struct tagStringData {
  bool coco_pressed, dingding_pressed;
} StringData;

GameObject* create_string();
