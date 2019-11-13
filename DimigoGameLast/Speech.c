#include "Speech.h"
#include "Delay.h"
#include "KeyInput.h"

void on_render_speech(GameObject* speech, HDC main_dc) {
  SpeechData* data = speech->data;

  FillRect(main_dc, &data->speech_rect, data->rect_brush);

  wchar_t* current_text = data->text[data->current_index];

  RECT draw_rect;
  draw_rect.top = data->speech_rect.top + 25;
  draw_rect.bottom = data->speech_rect.bottom - 25;
  draw_rect.left = data->speech_rect.left + 25;
  draw_rect.right = data->speech_rect.right - 25;

  static delay_t last_move_delay;
  if (after_delay(&last_move_delay, 0.05) && !data->text_over) {
    if (data->current_cursor < wcslen(current_text) - 1) {
      do {
        data->current_cursor++;
      } while (current_text[data->current_cursor] == ' ');
    } else {
      static delay_t text_show_delay;
      if (after_delay(&text_show_delay, 0.5)) data->text_over = true;
    }
  }

  wchar_t* draw_text = malloc(sizeof(wchar_t) * 100);
  if (draw_text == NULL) return;
  wcscpy(draw_text, current_text);
  draw_text[data->current_cursor + 1] = '\0';

  SelectObject(main_dc, data->font);
  SetTextColor(main_dc, RGB(0, 0, 0));
  DrawTextW(main_dc, draw_text, wcslen(draw_text), &draw_rect,
            DT_EXTERNALLEADING | DT_WORDBREAK);
  free(draw_text);

  if (data->text_over) {
    char enter_text[] = "Enter >";

    SetTextColor(main_dc, RGB(100, 100, 100));
    TextOut(main_dc, draw_rect.right - 100, draw_rect.bottom - 20, enter_text,
            strlen(enter_text));

    if (is_pressed(VK_RETURN)) {
      if (data->current_index < data->text_count - 1) {
        data->current_index++;
        data->current_cursor = 0;
        data->text_over = false;
      }
    }
  }
}

void on_destroy_speech(GameObject* speech) {
  SpeechData* data = speech->data;
  for (int i = 0; i < data->text_count; i++) {
    free(data->text[i]);
  }

  free(data->text);
}

GameObject* create_speech(wchar_t** text, int number, RECT rect) {
  GameObject* speech = init_game_object(NULL);

  speech->on_render = on_render_speech;
  speech->on_destroy = on_destroy_speech;

  SpeechData* data = malloc(sizeof(SpeechData));
  if (data == NULL) return NULL;
  data->speech_rect = rect;
  data->current_index = 0;
  data->current_cursor = 0;
  data->text = text;
  data->text_count = number;
  data->text_over = false;
  data->font = CreateFont(30, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0,
                          VARIABLE_PITCH | FF_ROMAN, TEXT("µÕ±Ù¸ğ²Ã"));
  data->rect_brush = CreateSolidBrush(RGB(200, 200, 200));

  speech->data = data;

  return speech;
}
