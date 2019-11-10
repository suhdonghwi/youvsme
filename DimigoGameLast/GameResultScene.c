#include "GameResultScene.h"

#include "CheeringPlayer.h"
#include "GameScene.h"
#include "ScoreDisplay.h"
#include "SpriteResources.h"

extern int g_coco_score;
extern int g_dingding_score;

void on_render_game_result_scene(GameScene* scene, HDC main_dc) {
  render_bitmap(background_sprites[1], main_dc, (Pos){0, 0}, 20.25);
}

GameScene* create_game_result_scene(bool coco_won) {
  if (coco_won)
    g_coco_score++;
  else
    g_dingding_score++;

  GameScene* scene = init_scene();

  GameObject* cheering_player = create_cheering_player(coco_won);
  cheering_player->pos = (Pos){515, 320};
  insert_game_object(cheering_player, scene);

  GameObject* score = create_score_display();
  score->pos = (Pos){430, 500};
  insert_game_object(score, scene);

  scene->on_render = on_render_game_result_scene;
  scene->sleep_duration = 100;

  return scene;
}
