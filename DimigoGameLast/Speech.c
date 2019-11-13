#include "Speech.h"

void on_render_speech(GameObject* speech, HDC main_dc) {
  SpeechData* data = speech->data;

  FillRect(main_dc, &data->speech_rect, data->rect_brush);

  char* current_text = data->text[data->current_index];

  SelectObject(main_dc, data->font);
  RECT draw_rect;
  draw_rect.top = data->speech_rect.top + 25;
  draw_rect.bottom = data->speech_rect.bottom - 25;
  draw_rect.left = data->speech_rect.left + 25;
  draw_rect.right = data->speech_rect.right - 25;
  DrawText(main_dc, current_text, strlen(current_text), &draw_rect,
           DT_EXTERNALLEADING | DT_WORDBREAK);
}

void on_destroy_speech(GameObject* speech) {
  SpeechData* data = speech->data;
  for (int i = 0; i < data->text_count; i++) {
    free(data->text[i]);
  }

  free(data->text);
}

GameObject* create_speech(char* text[], int number, RECT rect) {
  GameObject* speech = init_game_object(NULL);

  speech->on_render = on_render_speech;
  speech->on_destroy = on_destroy_speech;

  SpeechData* data = malloc(sizeof(SpeechData));
  if (data == NULL) return NULL;
  data->speech_rect = rect;
  data->current_index = 0;
  data->text = text;
  data->text_count = number;
  data->font = CreateFont(30, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0,
                          VARIABLE_PITCH | FF_ROMAN, TEXT("µÕ±Ù¸ğ²Ã"));
  data->rect_brush = CreateSolidBrush(RGB(200, 200, 200));

  speech->data = data;

  return speech;
}
