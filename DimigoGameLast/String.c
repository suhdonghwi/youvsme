#include "String.h"
#include "SpriteResources.h"

GameObject* create_string() {
  GameObject* string = init_game_object(string_sprites);
  string->scale = 15;
  string->pos = (Pos){250, 300};

  return string;
}