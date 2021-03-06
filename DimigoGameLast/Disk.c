#include "Disk.h"

#include "Delay.h"
#include "DiskGameScene.h"
#include "GameScene.h"
#include "SpriteResources.h"
#include "WaveAudio.h"

extern GameScene* g_current_scene;
extern GameScene* g_new_scene;

// 디스크의 on_render 콜백입니다. 마이크에서 입력을 받고 그에 따라 자신의 상태를
// 변경합니다.
void on_render_disk(GameObject* disk, HDC main_dc) {
  DiskData* disk_data = (DiskData*)(disk->data);

  if (!disk_data->initialized_wave) {
    init_wave_data(&disk_data->wave_data, 100);
    disk_data->initialized_wave = true;
  }

  if (waveInUnprepareHeader(disk_data->wave_data.wave_in,
                            &disk_data->wave_data.wave_hdr,
                            sizeof(WAVEHDR)) == WAVERR_STILLPLAYING) {
    DWORD recorded = disk_data->wave_data.wave_hdr.dwBytesRecorded / 2;
    short int max = 0;

    if (recorded - 300 < 0) return;
    for (DWORD i = recorded - 300; i < recorded; i++) {
      short int data = disk_data->wave_data.sample_data[i];
      if (data > max) {
        max = data;
      }
    }

    double volume = max / 32767.0;

    switch (disk_data->state) {
      case DISK_READY:
        if (volume > 0.6) {
          disk_data->state = DISK_FLYING;
        }
        break;
      case DISK_FLYING: {
        static delay_t last_turn_delay;
        if (after_delay(&last_turn_delay, 0.2)) {
          disk->sprite_index = (disk->sprite_index + 1) % 4;
          disk_data->last_turn_clock = clock();
        }
        if (volume > 0.1) {
          disk->pos.x += disk_data->speed;
        } else {
          disk_data->state = DISK_DESCENDING;
        }
        break;
      }
      case DISK_DESCENDING:
        disk->pos.x += disk_data->speed;
        disk->pos.y += disk_data->speed;
        disk_data->descend_count++;

        if (disk_data->descend_count * disk_data->speed >= 65) {
          disk->pos.y = disk_data->shadow_y_pos;
          disk_data->state = DISK_LANDED;
        }
        break;
      case DISK_LANDED:
        break;
    }
  } else {
    disk_data->state = DISK_DESCENDING;
  }

  render_bitmap(disk_shadow_sprites[0], main_dc,
                (Pos){disk->pos.x, disk_data->shadow_y_pos}, 20.25);
}

// 디스크의 on_destroy 콜백입니다. 자신이 해제될 때 음성 데이터 자원 또한
// 해제시킵니다.
void on_destroy_disk(GameObject* disk) {
  DiskData* disk_data = (DiskData*)(disk->data);
  deinit_wave_data(&disk_data->wave_data);
}

// 캐릭터, 위치, 속도를 받고 디스크 생성하여 반환합니다.
GameObject* create_disk(bool coco_disk, Pos pos, int speed) {
  GameObject* disk =
      init_game_object(coco_disk ? coco_disk_sprites : dingding_disk_sprites);

  disk->scale = 6;
  disk->pos = pos;
  disk->on_render = on_render_disk;
  disk->on_destroy = on_destroy_disk;

  DiskData* disk_data = malloc(sizeof(DiskData));
  if (disk_data == NULL) return NULL;

  disk_data->state = DISK_READY;
  disk_data->initialized_wave = false;
  disk_data->descend_count = 0;
  disk_data->shadow_y_pos = pos.y + 65;
  disk_data->speed = speed;
  disk_data->last_turn_clock = clock();

  disk->data = disk_data;
  return disk;
}
