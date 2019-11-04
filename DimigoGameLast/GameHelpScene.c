#include "GameHelpScene.h"

#include "SpriteResources.h"

static HBITMAP help_image;
static GameScene* dest_game_scene;

extern bool g_pressed_map[0xFE];
extern GameScene* g_new_scene;

void on_render_game_help_scene(GameScene* scene, HDC main_dc) {
  render_bitmap(background_sprites[0], main_dc, (Pos){0, 0}, 1);
  render_bitmap(help_image, main_dc, (Pos){120, 70}, 1);

  if (g_pressed_map['s'] || g_pressed_map['S']) {
    g_new_scene = dest_game_scene;
  }
}

GameScene* create_game_help_scene(HBITMAP help_bitmap, GameScene* game_scene) {
  help_image = help_bitmap;
  dest_game_scene = game_scene;

  GameScene* scene = init_scene();
  scene->on_render = on_render_game_help_scene;
  scene->sleep_duration = 100;

  return scene;
}
