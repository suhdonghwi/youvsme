#include <stdbool.h>
#include <time.h>

#include "CapePlayer2.h"
#include "GameScene.h"
#include "Spit.h"
#include "SpriteResources.h"

extern bool g_pressed_map[0xFE];
extern GameScene* g_current_scene;

clock_t last_shot_clock;

void on_update_cape_player2(GameObject* cape_player2) {
  if (g_pressed_map[VK_UP]) {
    cape_player2->pos.y -= 15;
  } else if (g_pressed_map[VK_DOWN]) {
    cape_player2->pos.y += 15;
  } else if (g_pressed_map[VK_SPACE]) {
    clock_t current_clock = clock();
    if (((double)current_clock - last_shot_clock) / CLOCKS_PER_SEC > 0.5) {
      GameObject* spit = create_spit();
      spit->pos = cape_player2->pos;
      insert_game_object(spit, g_current_scene);

      last_shot_clock = clock();
    }
  }

  if (cape_player2->pos.y > 700) {
    cape_player2->pos.y = 700;
  } else if (cape_player2->pos.y < 0) {
    cape_player2->pos.y = 0;
  }
}

GameObject* create_cape_player2() {
  last_shot_clock = clock();

  GameObject* cape_player2 = init_game_object();

  cape_player2->sprites = cape_player2_sprites;
  cape_player2->sprite_index = 0;
  cape_player2->pos = (Pos){700, 100};
  cape_player2->scale = 4;

  cape_player2->on_update = on_update_cape_player2;

  return cape_player2;
}
