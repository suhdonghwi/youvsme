#include <stdio.h>

#include "ScoreDisplay.h"
#include "SpriteResources.h"

extern int g_coco_score;
extern int g_dingding_score;

void after_render_score_display(GameObject* score_display, HDC main_dc) {
  ScoreDisplayData* data = (ScoreDisplayData*)score_display->data;

  SelectObject(main_dc, data->font);
  SetTextColor(main_dc, RGB(200, 0, 0));

  char score_str[100] = {'\0'};
  sprintf(score_str, "%d    %d", g_coco_score, g_dingding_score);
  TextOut(main_dc, score_display->pos.x + 45, score_display->pos.y + 50,
          score_str, strlen(score_str));
}

GameObject* create_score_display() {
  GameObject* score_display = init_game_object(score_board_sprites);
  score_display->scale = 0.1;

  ScoreDisplayData* data = malloc(sizeof(ScoreDisplayData));
  if (data == NULL) return NULL;
  data->font = CreateFont(50, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0,
                          VARIABLE_PITCH | FF_ROMAN, TEXT("µÕ±Ù¸ğ²Ã"));

  score_display->data = data;

  score_display->after_render = after_render_score_display;
  return score_display;
}