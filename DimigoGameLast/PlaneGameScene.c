#include "PlaneGameScene.h"
#include "BlowingPlayer.h"
#include "Plane.h"
#include "SpriteResources.h"

void on_render_plane_game_scene(GameScene* scene, HDC main_dc) {
  render_bitmap(background_sprites[1], main_dc, (Pos){0, 0}, 1);
}

GameScene* create_plane_game_scene(bool coco_turn) {
  GameScene* scene = init_scene();

  GameObject* plane = create_plane(coco_turn);
  plane->pos = (Pos){100, 500};
  insert_game_object(plane, scene);

  GameObject* player =
      create_blowing_player(coco_turn ? coco_sprites : dingding_sprites, plane);
  player->pos = (Pos){50, 490};
  player->scale = 2;
  insert_game_object(player, scene);

  scene->sleep_duration = 30;
  scene->on_render = on_render_plane_game_scene;

  return scene;
}