#pragma once
#include "GameObject.h"

typedef struct tagSpeechData {
  HFONT font;
  RECT speech_rect;

  int current_index;
  HBRUSH rect_brush;

  wchar_t** text;
  int text_count;
} SpeechData;

GameObject* create_speech(wchar_t** text, int number, RECT rect);
