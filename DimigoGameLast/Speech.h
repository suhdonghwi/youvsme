#pragma once
#include <time.h>

#include "Delay.h"
#include "GameObject.h"

typedef struct tagSpeechData {
  delay_t show_delay;

  RECT speech_rect;

  int current_index;
  HBRUSH rect_brush;
  HBRUSH border_brush;

  wchar_t** text;
  int text_count;

  size_t current_cursor;
  clock_t last_move_clock;

  bool text_over;
} SpeechData;

GameObject* create_speech(wchar_t** text, int number, RECT rect);
