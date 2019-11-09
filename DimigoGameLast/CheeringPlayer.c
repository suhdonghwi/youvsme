#include <time.h>

#include "CheeringPlayer.h"
#include "SpriteResources.h"

static clock_t last_change_clock;

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

  if (cheering_player->sprites == dingding_sprites) {
    render_bitmap(won_message_sprites[1], main_dc, (Pos){330, 50}, 1);
  } else {
    render_bitmap(won_message_sprites[0], main_dc, (Pos){330, 50}, 1);
  }
}

GameObject* create_cheering_player(bool coco_won) {
  GameObject* cheering_player =
      init_game_object(coco_won ? coco_sprites : dingding_sprites);

  cheering_player->sprite_index = 0;
  cheering_player->pos = (Pos){580, 400};
  cheering_player->scale = 25;

  cheering_player->on_render = on_render_cheering_player;

  return cheering_player;
}
