#include "CapeChar1.h"

#include "SpriteResources.h"
#include "WaveAudio.h"

WaveData wave_data;

void on_update_cape_char1(GameObject* cape_char1) {
  double volume;
  get_current_volume(wave_data, &volume);

  if (volume > 0.6) {
    cape_char1->pos.y -= 13;
  } else if (volume > 0.4) {
    cape_char1->pos.y -= 10;
  } else {
    cape_char1->pos.y += 10;
  }

  if (cape_char1->pos.y > 600) {
    cape_char1->pos.y = 600;
  } else if (cape_char1->pos.y < 0) {
    cape_char1->pos.y = 0;
  }
}

GameObject* create_cape_char1() {
  init_wave_data(&wave_data);

  GameObject* cape_char1 = init_game_object();

  cape_char1->sprites = cape_char1_sprites;
  cape_char1->sprite_index = 0;

  cape_char1->pos = (Pos){100, 100};

  cape_char1->on_update = on_update_cape_char1;

  return cape_char1;
}