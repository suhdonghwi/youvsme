#include "GameHelpScene.h"

#include "SpriteResources.h"

HBITMAP help_image;

void on_render_game_help_scene(GameScene* scene, HDC main_dc) {
  render_bitmap(cape_background_sprites[0], main_dc, (Pos){0, 0}, 1);
  render_bitmap(help_image, main_dc, (Pos){120, 70}, 1);
}

GameScene* create_game_help_scene(HBITMAP help_bitmap) {
  help_image = help_bitmap;

  GameScene* scene = init_scene();
  scene->on_render = on_render_game_help_scene;
  scene->sleep_duration = 100;

  return scene;
}
