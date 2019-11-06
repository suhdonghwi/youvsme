#include "PlaneGameScene.h"
#include "BlowingPlayer.h"
#include "GameResultScene.h"
#include "Plane.h"
#include "ReadyStartScene.h"
#include "SpriteResources.h"

extern GameScene* g_new_scene;
extern int g_coco_score;
extern int g_dingding_score;

void on_render_plane_game_scene(GameScene* scene, HDC main_dc) {
  PlaneGameData* data = (PlaneGameData*)scene->data;

  if (data->plane->pos.x >= 200) {
    data->plane->pos.x -= 3;
    if (data->fallen_plane != NULL) data->fallen_plane->pos.x -= 3;
    data->background_offset += 3;
  }

  if (data->plane->pos.y >= 550) {
    ((PlaneData*)data->plane->data)->state = PLANE_LANDED;
    Sleep(1500);

    if (data->plane->sprite_index == 0) {
      GameObject* fallen_plane = create_plane(true);
      fallen_plane->pos = data->plane->pos;
      fallen_plane->pos.x += data->background_offset;
      ((PlaneData*)fallen_plane->data)->state = PLANE_LANDED;

      GameScene* plane_scene = create_plane_game_scene(false, fallen_plane);
      GameScene* new_scene = create_readystart_scene(
          plane_scene, dingding_turn_sprites, 3, (Pos){70, 100});

      g_new_scene = new_scene;
    } else {
      if (data->fallen_plane == NULL) return;
      if (data->fallen_plane->pos.x >= data->plane->pos.x) {
        g_new_scene = create_game_result_scene(false);
        g_dingding_score++;
      } else {
        g_new_scene = create_game_result_scene(true);
        g_coco_score++;
      }
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