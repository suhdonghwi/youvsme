#include "Speech.h"
#include "KeyInput.h"

extern HFONT g_font_medium;

// ��ǳ���� on_render �ݹ��Դϴ�. ��縦 �� �ھ� ����ϰ�, ��� ����� �Ϸ�Ǹ�
// EnterŰ�� ���� �� �ֵ��� �ѵ�, Enter Ű�� ������ ���� ���� �Ѿ�ϴ�.
void on_render_speech(GameObject* speech, HDC main_dc) {
  SpeechData* data = speech->data;

  if (elapsed_time(data->show_delay) < 1) {
    return;
  }

  FillRect(main_dc, &data->speech_rect, data->rect_brush);

  RECT border_rect = data->speech_rect;
  for (int i = 0; i < 3; i++) {
    FrameRect(main_dc, &border_rect, data->border_brush);
    border_rect.left -= 1;
    border_rect.right += 1;
    border_rect.top -= 1;
    border_rect.bottom += 1;
  }

  wchar_t* current_text = data->text[data->current_index];

  RECT draw_rect;
  draw_rect.top = data->speech_rect.top + 25;
  draw_rect.bottom = data->speech_rect.bottom - 25;
  draw_rect.left = data->speech_rect.left + 25;
  draw_rect.right = data->speech_rect.right - 25;

  static delay_t last_move_delay, text_show_delay;
  if (after_delay(&last_move_delay, 0.05) && !data->text_over) {
    if (data->current_cursor < wcslen(current_text) - 1) {
      do {
        data->current_cursor++;
      } while (current_text[data->current_cursor] == ' ');
      text_show_delay = clock();
    } else {
      if (after_delay(&text_show_delay, 0.25)) {
        data->text_over = true;
      }
    }
  }

  wchar_t* draw_text = malloc(sizeof(wchar_t) * 100);
  if (draw_text == NULL) return;
  wcscpy(draw_text, current_text);
  draw_text[data->current_cursor + 1] = '\0';

  SelectObject(main_dc, g_font_medium);
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
      } else {
        strcpy(speech->tag, "speech_end");
      }
    }
  }
}

// ��ǳ���� on_first_render �ݹ��Դϴ�. ��ǳ�� ���� ���� Ÿ�̸��� ���� ����
// ����� �����մϴ�.
void on_first_render(GameObject* speech, HDC main_dc) {
  SpeechData* data = speech->data;
  data->show_delay = clock();
}

// ��ǳ���� on_destroy �ݹ��Դϴ�. �Ҵ�Ǿ��ִ� ��縦 �����մϴ�.
void on_destroy_speech(GameObject* speech) {
  SpeechData* data = speech->data;
  for (int i = 0; i < data->text_count; i++) {
    free(data->text[i]);
  }

  free(data->text);
}

// ���� ����� ����, ��ǳ���� ��ġ�� ũ�⸦ ���� RECT �����͸� �ް� ��ǳ����
// �����Ͽ� ��ȯ�մϴ�.
GameObject* create_speech(wchar_t** text, int number, RECT rect) {
  GameObject* speech = init_game_object(NULL);

  speech->on_render = on_render_speech;
  speech->on_first_render = on_first_render;
  speech->on_destroy = on_destroy_speech;
  strcpy(speech->tag, "speech_normal");

  SpeechData* data = malloc(sizeof(SpeechData));
  if (data == NULL) return NULL;
  data->speech_rect = rect;
  data->current_index = 0;
  data->current_cursor = 0;
  data->text = text;
  data->text_count = number;
  data->text_over = false;
  data->rect_brush = CreateSolidBrush(RGB(220, 220, 220));
  data->border_brush = CreateSolidBrush(RGB(20, 20, 20));
  data->show_delay = 0;

  speech->data = data;

  return speech;
}
