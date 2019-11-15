#include <time.h>

#include "CheeringPlayer.h"
#include "Delay.h"
#include "SpriteResources.h"

static clock_t last_change_clock;

// 신나하는 플레이어의 on_render 콜백입니다. 0.5초마다 팔을 흔들도록
// 스프라이트를 변경합니다.
void on_render_cheering_player(GameObject* cheering_player, HDC main_dc) {
  static delay_t last_change_clock;

  if (after_delay(&last_change_clock, 0.5)) {
    cheering_player->sprite_index = cheering_player->sprite_index == 0 ? 1 : 0;
    if (cheering_player->sprite_index == 0)
      cheering_player->pos.x += 13;
    else
      cheering_player->pos.x -= 13;
    last_change_clock = clock();
  }

  if (cheering_player->sprites == dingding_sprites) {
    render_bitmap(won_message_sprites[1], main_dc, (Pos){220, 50}, 20.25);
  } else {
    render_bitmap(won_message_sprites[0], main_dc, (Pos){220, 50}, 20.25);
  }
}

// 캐릭터를 받고 신나하는 플레이어를 생성하여 반환합니다.
GameObject* create_cheering_player(bool coco_won) {
  GameObject* cheering_player =
      init_game_object(coco_won ? coco_sprites : dingding_sprites);

  cheering_player->sprite_index = 0;
  cheering_player->scale = 20.25;

  cheering_player->on_render = on_render_cheering_player;

  return cheering_player;
}
