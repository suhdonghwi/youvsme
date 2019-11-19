#include <stdio.h>

#include "FinalResultScene.h"
#include "HomeScene.h"
#include "KeyInput.h"
#include "SetScore.h"
#include "SpriteResources.h"
#include "StoryScene.h"

extern GameScene* g_new_scene;

extern HFONT g_font_bigger;

extern int g_coco_score;
extern int g_dingding_score;

// 최종 결과 화면의 on_render 콜백입니다. 최종 스코어를 칠판 위에 그려줍니다.
// 그리고 Enter 키가 눌리면 홈 화면으로, R 키가 눌리면 스토리 모드를
// 재시작합니다.
void on_render_final_result_scene(GameScene* scene, HDC main_dc) {
  render_bitmap(background_sprites[6], main_dc, (Pos){0, 0}, 5.1);

  SelectObject(main_dc, g_font_bigger);
  SetTextColor(main_dc, RGB(200, 200, 200));

  char score_str[100] = {'\0'};
  sprintf(score_str, "%d    %d", g_dingding_set_score, g_coco_set_score);
  TextOut(main_dc, 430, 270, score_str, strlen(score_str));

  if (is_pressed(VK_RETURN)) {
    g_new_scene = create_home_scene();
  } else if (is_pressed(0x52)) {
    g_new_scene = create_after_main_story();
  }
}

// 최종 결과 화면을 생성한 뒤 반환합니다.
GameScene* create_final_result_scene() {
  GameScene* scene = init_scene();

  g_coco_score = 0;
  g_dingding_score = 0;

  scene->on_render = on_render_final_result_scene;
  return scene;
}
