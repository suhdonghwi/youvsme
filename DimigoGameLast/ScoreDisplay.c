#include <stdio.h>

#include "ScoreDisplay.h"
#include "SpriteResources.h"

extern int g_coco_score;
extern int g_dingding_score;
extern HFONT g_font_big;

// ���� ���÷����� after_render �ݹ��Դϴ�. ������ ���� ������ �������մϴ�.
void after_render_score_display(GameObject* score_display, HDC main_dc) {
  SelectObject(main_dc, g_font_big);
  SetTextColor(main_dc, RGB(200, 0, 0));

  char score_str[100] = {'\0'};
  sprintf(score_str, "%d    %d", g_coco_score, g_dingding_score);
  TextOut(main_dc, score_display->pos.x + 45, score_display->pos.y + 50,
          score_str, strlen(score_str));
}

// �������� �����Ͽ� ��ȯ�մϴ�.
GameObject* create_score_display() {
  GameObject* score_display = init_game_object(score_board_sprites);
  score_display->scale = 0.1;

  score_display->after_render = after_render_score_display;
  return score_display;
}