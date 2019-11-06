#include "PlaneGameScene.h"
#include "BlowingPlayer.h"
#include "Plane.h"
#include "SpriteResources.h"

extern GameScene* g_new_scene;

void on_render_plane_game_scene(GameScene* scene, HDC main_dc) {
  PlaneGameData* data = (PlaneGameData*)scene->data;

  if (data->plane->pos.x >= 200) {
    data->plane->pos.x -= 3;
    if (data->fallen_plane != NULL) data->fallen_plane->pos.x -= 3;
    data->background_offset += 3;
  }

  if (data->plane->pos.y >= 550) {
    ((PlaneData*)data->plane->data)->state = PLANE_LANDED;

    if (data->plane->sprite_index == 0) {
      GameObject* fallen_plane = create_plane(true);
      fallen_plane->pos = data->plane->pos;
      fallen_plane->pos.x += data->background_offset;
      ((PlaneData*)fallen_plane->data)->state = PLANE_LANDED;

      GameScene* new_scene = create_plane_game_scene(false, fallen_plane);

      g_new_scene = new_scene;
    }
  }

  render_bitmap(background_sprites[1], main_dc,
                (Pos){-data->background_offset, 0}, 1);
  data->player->pos.x = 50 - data->background_offset;
}

GameScene* create_plane_game_scene(bool coco_turn, GameObject* fallen_plane) {
  GameScene* scene = init_scene();

  GameObject* plane = create_plane(coco_turn);
  plane->pos = (Pos){100, 500};
  insert_game_object(plane, scene);

  GameObject* player =
      create_blowing_player(coco_turn ? coco_sprites : dingding_sprites, plane);
  player->pos = (Pos){50, 490};
  player->scale = 2;
  insert_game_object(player, scene);

  insert_game_object(fallen_plane, scene);

  scene->sleep_duration = 30;
  scene->on_render = on_render_plane_game_scene;

  PlaneGameData* data = malloc(sizeof(PlaneGameData));
  if (data == NULL) return NULL;
  data->plane = plane;
  data->fallen_plane = fallen_plane;
  data->player = player;
  data->background_offset = 0;

  scene->data = data;

  return scene;
}