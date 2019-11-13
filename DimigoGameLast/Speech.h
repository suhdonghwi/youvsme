#pragma once
#include "GameObject.h"

typedef struct tagSpeechData {
  HFONT font;
  RECT speech_rect;

  int current_index;
  HBRUSH rect_brush;

  char** text;
  int text_count;
} SpeechData;

GameObject* create_speech(char* text[], int number, RECT rect);
