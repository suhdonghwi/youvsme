#include "GameResultScene.h"

#include "CheeringPlayer.h"
#include "GameScene.h"
#include "SpriteResources.h"

void on_render_game_result_scene(GameScene* scene, HDC main_dc) {
  render_bitmap(cape_background_sprites[0], main_dc, (Pos){0, 0}, 1.0);
}

GameScene* create_game_result_scene(bool player1_won) {
  GameScene* scene = init_scene();

  GameObject* cheering_player = create_cheering_player(player1_won);
  insert_game_object(cheering_player, scene);

  scene->on_render = on_render_game_result_scene;

  return scene;
}
