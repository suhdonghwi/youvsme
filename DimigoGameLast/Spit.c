#include "Spit.h"

#include "SpriteResources.h"

void on_update_spit(GameObject* spit) { spit->pos.x -= 20; }

GameObject* create_spit() {
  GameObject* spit = init_game_object();

  spit->sprites = spit_sprites;
  spit->pos = (Pos){700, 100};
  spit->scale = 5;

  spit->on_update = on_update_spit;

  return spit;
}
