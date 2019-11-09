#include "DiskGameScene.h"
#include "Disk.h"
#include "GameResultScene.h"
#include "ReadyStartScene.h"
#include "SpriteResources.h"
#include "ThrowingPlayer.h"

extern GameScene* g_new_scene;
extern int g_coco_score;
extern int g_dingding_score;

void on_render_disk_game_scene(GameScene* scene, HDC main_dc) {
  DiskGameData* data = (DiskGameData*)scene->data;

  if (data->disk->pos.x >= 200) {
    data->disk->pos.x -= 5;
    if (data->fallen_disk != NULL) data->fallen_disk->pos.x -= 5;
    data->background_offset += 5;
  }

  if (((DiskData*)data->disk->data)->state == DISK_LANDED) {
    Sleep(1500);

    if (data->disk->sprite_index == 0) {
      GameObject* fallen_disk = create_disk(true, data->disk->pos);
      fallen_disk->pos.x += data->background_offset;
      ((DiskData*)fallen_disk->data)->state = DISK_LANDED;
      ((DiskData*)fallen_disk->data)->shadow_pos.y = data->disk->pos.y;

      GameScene* disk_scene = create_disk_game_scene(false, fallen_disk);
      GameScene* new_scene = create_readystart_scene(
          disk_scene, dingding_turn_sprites, 3, (Pos){70, 100});

      g_new_scene = new_scene;
    } else {
      if (data->fallen_disk == NULL) return;
      if (data->fallen_disk->pos.x >= data->disk->pos.x) {
        g_new_scene = create_game_result_scene(false);
        g_coco_score++;
      } else {
        g_new_scene = create_game_result_scene(true);
        g_dingding_score++;
      }
    }
  }

  render_bitmap(background_sprites[0], main_dc,
                (Pos){-data->background_offset, 0}, 24);

  if (data->player->sprites == coco_sprites) {
    render_bitmap(dingding_sprites[0], main_dc,
                  (Pos){60 - data->background_offset, 400}, 24);
  } else {
    render_bitmap(coco_sprites[0], main_dc,
                  (Pos){60 - data->background_offset, 100}, 24);
  }

  data->player->pos.x = 50 - data->background_offset;
}

GameScene* create_disk_game_scene(bool coco_turn, GameObject* fallen_disk) {
  GameScene* scene = init_scene();

  GameObject* disk =
      create_disk(coco_turn, coco_turn ? (Pos){140, 180} : (Pos){140, 480});
  insert_game_object(disk, scene);

  GameObject* player =
      create_throwing_player(coco_turn ? coco_sprites : dingding_sprites, disk);
  if (coco_turn) {
    player->pos = (Pos){100, 140};
  } else {
    player->pos = (Pos){100, 440};
  }
  player->scale = 24;
  insert_game_object(player, scene);

  insert_game_object(fallen_disk, scene);

  scene->sleep_duration = 30;
  scene->on_render = on_render_disk_game_scene;

  DiskGameData* data = malloc(sizeof(DiskGameData));
  if (data == NULL) return NULL;
  data->disk = disk;
  data->fallen_disk = fallen_disk;
  data->player = player;
  data->background_offset = 0;

  scene->data = data;

  return scene;
}