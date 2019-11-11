#include "DanceGameScene.h"
#include "SpriteResources.h"

void on_render_dance_game_scene(GameScene* scene, HDC main_dc) {
  render_bitmap(background_sprites[3], main_dc, (Pos){0, 0}, 20.25);
}

GameScene* create_dance_game_scene() {
  GameScene* scene = init_scene();

  scene->on_render = on_render_dance_game_scene;
  return scene;
}