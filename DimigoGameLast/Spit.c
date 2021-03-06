#include "Spit.h"

#include "SpriteResources.h"

void on_render_spit(GameObject* spit, HDC main_dc) {
  spit->pos.x -= 15;
  if (spit->pos.x < -10) {
    spit->alive = false;
  }
}

GameObject* create_spit() {
  GameObject* spit = init_game_object(spit_sprites);

  strncpy(spit->tag, "spit", 100);
  spit->pos = (Pos){700, 100};
  spit->scale = 6;
  spit->collidable = true;

  spit->on_render = on_render_spit;

  return spit;
}
