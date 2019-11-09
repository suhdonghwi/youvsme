#include "ReadyStartScene.h"

#include "SpriteResources.h"

extern GameScene* g_new_scene;

void on_render_readystart_scene(GameScene* scene, HDC main_dc) {
  ReadyStartData* data = (ReadyStartData*)scene->data;

  render_bitmap(background_sprites[0], main_dc, (Pos){0, 0}, 1);
  render_bitmap(data->slide_bitmaps[data->index], main_dc, data->render_pos, 1);

  data->index++;

  if (data->index >= data->slide_size) {
    g_new_scene = data->dest_scene;
    return;
  }
}

GameScene* create_readystart_scene(GameScene* dest_scene,
                                   HBITMAP* slide_bitmaps, int size, Pos pos) {
  GameScene* scene = init_scene();

  ReadyStartData* data = malloc(sizeof(ReadyStartData));
  if (data == NULL) return NULL;
  data->dest_scene = dest_scene;
  data->slide_bitmaps = slide_bitmaps;
  data->slide_size = size;
  data->render_pos = pos;
  data->index = 0;
  scene->data = data;

  scene->on_render = on_render_readystart_scene;
  scene->sleep_duration = 1000;

  return scene;
}