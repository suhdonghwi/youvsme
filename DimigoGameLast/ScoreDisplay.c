#include <stdio.h>

#include "ScoreDisplay.h"
#include "SpriteResources.h"

extern int g_coco_score;
extern int g_dingding_score;
extern HFONT g_font_big;

// 점수 디스플레이의 after_render 콜백입니다. 점수판 위에 점수를 렌더링합니다.
void after_render_score_display(GameObject* score_display, HDC main_dc) {
  SelectObject(main_dc, g_font_big);
  SetTextColor(main_dc, RGB(200, 0, 0));

  char score_str[100] = {'\0'};
  sprintf(score_str, "%d    %d", g_coco_score, g_dingding_score);
  TextOut(main_dc, score_display->pos.x + 45, score_display->pos.y + 50,
          score_str, strlen(score_str));
}

// 점수판을 생성하여 반환합니다.
GameObject* create_score_display() {
  GameObject* score_display = init_game_object(score_board_sprites);
  score_display->scale = 0.1;

  score_display->after_render = after_render_score_display;
  return score_display;
}