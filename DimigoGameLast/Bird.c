#include "Bird.h"

#include "SpriteResources.h"

GameObject* make_bird() {
  GameObject* bird = init_game_object();

  bird->sprites = bird_sprites;
  bird->sprite_index = 0;

  bird->pos = (Pos){100, 100};

  return bird;
}