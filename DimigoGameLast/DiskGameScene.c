#include "DiskGameScene.h"
#include "Disk.h"
#include "GameResultScene.h"
#include "PullGameScene.h"
#include "ReadyStartScene.h"
#include "SpriteResources.h"
#include "StoryScene.h"
#include "ThrowingPlayer.h"

extern GameScene* g_new_scene;

void on_render_disk_game_scene(GameScene* scene, HDC main_dc) {
  DiskGameData* data = (DiskGameData*)scene->data;
  DiskData* disk_data = (DiskData*)data->disk->data;

  if (data->disk->pos.x >= 200) {
    data->disk->pos.x -= disk_data->speed;

    if (!(data->fallen_pos.x == 0 && data->fallen_pos.y == 0))
      data->fallen_pos.x -= disk_data->speed;

    data->background_offset += disk_data->speed;
    data->player->pos.x -= disk_data->speed;
  }

  if (disk_data->state == DISK_LANDED) {
    Sleep(1500);

    if (data->disk->sprites == coco_disk_sprites) {
      GameScene* disk_scene = create_disk_game_scene(
          false, (Pos){data->disk->pos.x + data->background_offset,
                       data->disk->pos.y});
      GameScene* new_scene = create_readystart_scene(
          disk_scene, dingding_disk_ready_sprites, 3, (Pos){560, 300});

      g_new_scene = new_scene;
    } else {
      g_new_scene =
          create_after_disk_story(data->fallen_pos.x >= data->disk->pos.x);
    }
  }

  render_bitmap(background_sprites[0], main_dc,
                (Pos){-data->background_offset, 0}, 20.25);

  if (data->player->sprites == coco_sprites) {
    render_bitmap(dingding_sprites[0], main_dc, (Pos){data->player->pos.x, 410},
                  20.25);
  }

  if (!(data->fallen_pos.x == 0 && data->fallen_pos.y == 0)) {
    render_bitmap(coco_disk_sprites[0], main_dc, data->fallen_pos, 6);
    render_bitmap(
        disk_line_sprites[data->disk->pos.x >= data->fallen_pos.x ? 1 : 0],
        main_dc, (Pos){data->fallen_pos.x + 80, 166}, 20.25);

    if (data->disk->pos.x >= data->fallen_pos.x) {
      render_bitmap(disk_line_sprites[1], main_dc,
                    (Pos){data->fallen_pos.x + 80, 166}, 20.25);
      render_bitmap(coco_sprites[3], main_dc,
                    (Pos){data->fallen_pos.x + 77, 30}, 16);
    } else {
      render_bitmap(coco_sprites[0], main_dc,
                    (Pos){data->fallen_pos.x + 77, 30}, 16);
      render_bitmap(ment_sprites[0], main_dc,
                    (Pos){data->fallen_pos.x + 152, 10}, 1);
    }
  }
}

GameScene* create_disk_game_scene(bool coco_turn, Pos fallen_pos) {
  GameScene* scene = init_scene();

  GameObject* disk =
      create_disk(coco_turn, coco_turn ? (Pos){140, 180} : (Pos){140, 430}, 7);
  insert_game_object(disk, scene);

  GameObject* player =
      create_throwing_player(coco_turn ? coco_sprites : dingding_sprites, disk);
  if (coco_turn) {
    player->pos = (Pos){50, 140};
  } else {
    player->pos = (Pos){50, 410};
  }
  player->scale = 20.25;
  insert_game_object(player, scene);

  scene->sleep_duration = 20;
  scene->on_render = on_render_disk_game_scene;

  DiskGameData* data = malloc(sizeof(DiskGameData));
  if (data == NULL) return NULL;
  data->disk = disk;
  data->fallen_pos = fallen_pos;
  data->player = player;
  data->background_offset = 0;

  scene->data = data;

  return scene;
}