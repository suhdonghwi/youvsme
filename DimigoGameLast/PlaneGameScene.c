#include "PlaneGameScene.h"
#include "Plane.h"
#include "SpriteResources.h"

void on_render_plane_game_scene(GameScene* scene, HDC main_dc) {
  render_bitmap(background_sprites[1], main_dc, (Pos){0, 0}, 1);
}

GameScene* create_plane_game_scene() {
  GameScene* scene = init_scene();

  GameObject* plane = create_plane(true);
  plane->pos = (Pos){100, 450};
  insert_game_object(plane, scene);

  scene->sleep_duration = 30;
  scene->on_render = on_render_plane_game_scene;

  return scene;
}