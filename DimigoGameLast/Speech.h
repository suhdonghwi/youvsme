#pragma once
#include <time.h>

#include "GameObject.h"

typedef struct tagSpeechData {
  HFONT font;
  RECT speech_rect;

  int current_index;
  HBRUSH rect_brush;

  wchar_t** text;
  int text_count;

  size_t current_cursor;
  clock_t last_move_clock;
} SpeechData;

GameObject* create_speech(wchar_t** text, int number, RECT rect);
