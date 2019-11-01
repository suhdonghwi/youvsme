#include "Bird.h"

#include "SpriteResources.h"

void make_bird(GameObject* bird) {
  init_game_object(bird);

  bird->sprites = bird_sprites;
  bird->sprite_index = 0;

  bird->pos = (Pos){100, 100};
}