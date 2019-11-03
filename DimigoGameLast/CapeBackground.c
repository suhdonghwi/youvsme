#include "CapeBackground.h"

#include "SpriteResources.h"

GameObject* create_cape_background() {
  GameObject* cape_background = init_game_object(cape_background_sprites);

  // cape_background->scale = 1.5;

  return cape_background;
}
