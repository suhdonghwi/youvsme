#include "BlowingPlayer.h"
#include "Plane.h"

typedef struct tagBlowingPlayerData {
  GameObject* plane;
} BlowingPlayerData;

void on_render_blowing_player(GameObject* blowing_player, HDC main_dc) {
  BlowingPlayerData* player_data = (BlowingPlayerData*)blowing_player->data;
  PlaneData* plane_data = (PlaneData*)player_data->plane->data;

  if (plane_data->state != PLANE_READY) {
    blowing_player->sprite_index = 3;
  }
}

GameObject* create_blowing_player(HBITMAP* sprites, GameObject* plane) {
  GameObject* blowing_player = init_game_object(sprites);
  blowing_player->sprite_index = 0;

  BlowingPlayerData* data = malloc(sizeof(BlowingPlayerData));
  if (data == NULL) return NULL;
  data->plane = plane;

  blowing_player->data = data;

  blowing_player->on_render = on_render_blowing_player;
  return blowing_player;
}
