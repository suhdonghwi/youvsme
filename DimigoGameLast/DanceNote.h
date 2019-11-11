#pragma once
#include "Dancer.h"
#include "GameObject.h"

typedef struct tagDanceNoteData {
  int speed;
} DanceNoteData;

GameObject* create_dance_note(DanceDirection dir, HBITMAP* sprites, int speed);
