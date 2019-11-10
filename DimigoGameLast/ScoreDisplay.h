#pragma once
#include "GameObject.h"

typedef struct tagScoreDisplayData {
  HFONT font;
} ScoreDisplayData;

GameObject* create_score_display();
