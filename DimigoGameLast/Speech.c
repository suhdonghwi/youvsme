#include "Speech.h"
#include "KeyInput.h"

// 말풍선의 on_render 콜백입니다. 대사를 한 자씩 출력하고, 모두 출력이 완료되면
// Enter키를 누를 수 있도록 한뒤, Enter 키가 눌리는 다음 대사로 넘어갑니다.
void on_render_speech(GameObject* speech, HDC main_dc) {
  SpeechData* data = speech->data;

  if (elapsed_time(data->show_delay) < 1) {
    return;
  }

  FillRect(main_dc, &data->speech_rect, data->rect_brush);

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
      } else {
        strcpy(speech->tag, "speech_end");
      }
    }
  }
}

// 말풍선의 on_first_render 콜백입니다. 말풍선 최초 생성 타이머의 기준 값을
// 현재로 설정합니다.
void on_first_render(GameObject* speech, HDC main_dc) {
  SpeechData* data = speech->data;
  data->show_delay = clock();
}

// 말풍선의 on_destroy 콜백입니다. 할당되어있는 대사를 해제합니다.
void on_destroy_speech(GameObject* speech) {
  SpeechData* data = speech->data;
  for (int i = 0; i < data->text_count; i++) {
    free(data->text[i]);
  }

  free(data->text);
}

// 대사와 대사의 개수, 말풍선의 위치와 크기를 담은 RECT 데이터를 받고 말풍선을
// 생성하여 반환합니다.
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
  data->font = CreateFont(30, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0,
                          VARIABLE_PITCH | FF_ROMAN, TEXT("둥근모꼴"));
  data->rect_brush = CreateSolidBrush(RGB(200, 200, 200));
  data->show_delay = 0;

  speech->data = data;

  return speech;
}
