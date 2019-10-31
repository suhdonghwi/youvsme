#include "Bird.h"

#include "SpriteResources.h"

GameObject make_bird() {
  GameObject result;
  result.sprites = bird_sprites;
  result.sprite_index = 0;
  result.pos = (Pos){100, 100};
  return result;
}