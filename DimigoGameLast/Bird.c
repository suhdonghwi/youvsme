#include "Bird.h"
#include "SpriteResources.h"
#include "WaveAudio.h"

WaveData wave_data;

void on_update_bird(GameObject* bird) {
  double volume;
  get_current_volume(wave_data, &volume);

  if (volume > 0.6) {
    bird->pos.y -= 13;
  } else if (volume > 0.4) {
    bird->pos.y -= 10;
  } else {
    bird->pos.y += 10;
  }

  if (bird->pos.y > 600) {
    bird->pos.y = 600;
  } else if (bird->pos.y < 0) {
    bird->pos.y = 0;
  }
}

GameObject* create_bird() {
  init_wave_data(&wave_data);

  GameObject* bird = init_game_object();

  bird->sprites = bird_sprites;
  bird->sprite_index = 0;

  bird->pos = (Pos){100, 100};

  bird->on_update = on_update_bird;

  return bird;
}