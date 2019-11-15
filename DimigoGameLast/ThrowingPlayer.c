#include "ThrowingPlayer.h"
#include "Disk.h"

typedef struct tagBlowingPlayerData {
  GameObject* disk;
} BlowingPlayerData;

// ������ ĳ������ on_render �ݹ��Դϴ�. ��ũ�� �������� ������ �������
// ��������Ʈ�� �����մϴ�.
void on_render_throwing_player(GameObject* blowing_player, HDC main_dc) {
  BlowingPlayerData* player_data = (BlowingPlayerData*)blowing_player->data;
  DiskData* disk_data = (DiskData*)player_data->disk->data;

  if (disk_data->state != DISK_READY) {
    blowing_player->sprite_index = 2;
  }
}

// ��������Ʈ�� ��ũ�� �ް� ������ ĳ���͸� �����Ͽ� ��ȯ�մϴ�.
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
