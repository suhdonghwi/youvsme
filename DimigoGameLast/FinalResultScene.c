#include <stdio.h>

#include "FinalResultScene.h"
#include "SetScore.h"
#include "SpriteResources.h"

void on_render_final_result_scene(GameScene* scene, HDC main_dc) {
  FinalResultSceneData* data = scene->data;

  render_bitmap(background_sprites[6], main_dc, (Pos){0, 0}, 5.1);

  SelectObject(main_dc, data->font);
  SetTextColor(main_dc, RGB(200, 200, 200));

  char score_str[100] = {'\0'};
  sprintf(score_str, "%d    %d", g_dingding_set_score, g_coco_set_score);
  TextOut(main_dc, 430, 270, score_str, strlen(score_str));
}
GameScene* create_final_result_scene() {
  GameScene* scene = init_scene();

  FinalResultSceneData* data = malloc(sizeof(FinalResultSceneData));
  if (data == NULL) return NULL;
  data->font = CreateFont(80, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0,
                          VARIABLE_PITCH | FF_ROMAN, TEXT("�ձٸ��"));

  scene->data = data;

  scene->on_render = on_render_final_result_scene;
  return scene;
}
