#pragma once
#include "GameObject.h"

typedef struct tagBird {
  GameObject base;
} Bird;

Bird make_bird();
