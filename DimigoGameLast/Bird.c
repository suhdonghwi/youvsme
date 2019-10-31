#include "Bird.h"

#include "SpriteResources.h"

Bird make_bird() {
  Bird result;
  result.base.sprites = bird_sprites;
  return result;
}