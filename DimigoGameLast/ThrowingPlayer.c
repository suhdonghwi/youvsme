#include "ThrowingPlayer.h"
#include "Disk.h"

typedef struct tagBlowingPlayerData {
  GameObject* disk;
} BlowingPlayerData;

// 던지는 캐릭터의 on_render 콜백입니다. 디스크가 던져지면 던지는 모습으로
// 스프라이트를 변경합니다.
void on_render_throwing_player(GameObject* blowing_player, HDC main_dc) {
  BlowingPlayerData* player_data = (BlowingPlayerData*)blowing_player->data;
  DiskData* disk_data = (DiskData*)player_data->disk->data;

  if (disk_data->state != DISK_READY) {
    blowing_player->sprite_index = 2;
  }
}

// 스프라이트와 디스크를 받고 던지는 캐릭터를 생성하여 반환합니다.
GameObject* create_throwing_player(HBITMAP* sprites, GameObject* disk) {
  GameObject* throwing_player = init_game_object(sprites);
  throwing_player->sprite_index = 0;

  BlowingPlayerData* data = malloc(sizeof(BlowingPlayerData));
  if (data == NULL) return NULL;
  data->disk = disk;

  throwing_player->data = data;

  throwing_player->on_render = on_render_throwing_player;
  return throwing_player;
}
