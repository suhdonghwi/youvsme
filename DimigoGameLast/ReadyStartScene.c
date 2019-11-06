#include "ReadyStartScene.h"

#include "SpriteResources.h"

extern GameScene* g_new_scene;

static int current_index = 0;
static int slide_size;
static GameScene* dest_scene;
static HBITMAP* slide_bitmaps;
static Pos render_pos;

void on_render_readystart_scene(GameScene* scene, HDC main_dc) {
  if (current_index >= slide_size) {
    g_new_scene = dest_scene;
    return;
  }

  render_bitmap(background_sprites[0], main_dc, (Pos){0, 0}, 1);
  render_bitmap(slide_bitmaps[current_index], main_dc, render_pos, 1);
  Sleep(1000);

  current_index++;
}

GameScene* create_readystart_scene(GameScene* ready_scene, HBITMAP* slides,
                                   int size, Pos pos) {
  GameScene* scene = init_scene();

  dest_scene = ready_scene;
  slide_bitmaps = slides;
  slide_size = size;
  render_pos = pos;

  scene->on_render = on_render_readystart_scene;
  scene->sleep_duration = 20;

  return scene;
}