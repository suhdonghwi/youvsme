#include <stdio.h>

#include "ScoreDisplay.h"
#include "SpriteResources.h"

extern int g_coco_score;
extern int g_dingding_score;

void on_render_score_display(GameObject* score_display, HDC main_dc) {
  char score_str[100] = {'\0'};
  sprintf(score_str, "%d : %d", g_coco_score, g_dingding_score);
  TextOut(main_dc, 350, 600, score_str, strlen(score_str));

  render_bitmap(coco_sprites[0], main_dc, (Pos){270, 600}, 1);
  render_bitmap(dingding_sprites[0], main_dc, (Pos){560, 600}, 1);
}

GameObject* create_score_display() {
  GameObject* score_display = init_game_object(NULL);

  score_display->on_render = on_render_score_display;
}