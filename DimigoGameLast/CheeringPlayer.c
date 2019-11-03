#include <time.h>

#include "CheeringPlayer.h"
#include "SpriteResources.h"

clock_t last_change_clock;

void on_render_cheering_player(GameObject* cheering_player, HDC main_dc) {
  clock_t current_clock = clock();
  if (((double)current_clock - last_change_clock) / CLOCKS_PER_SEC > 0.5) {
    cheering_player->sprite_index = cheering_player->sprite_index == 0 ? 1 : 0;
    if (cheering_player->sprite_index == 0)
      cheering_player->pos.x += 13;
    else
      cheering_player->pos.x -= 13;
    last_change_clock = clock();
  }
}

GameObject* create_cheering_player(bool player1_won) {
  GameObject* cheering_player =
      init_game_object(player1_won ? player1_sprites : player2_sprites);

  cheering_player->sprite_index = 0;
  cheering_player->pos = (Pos){400, 400};
  cheering_player->scale = 5;

  cheering_player->on_render = on_render_cheering_player;

  return cheering_player;
}
