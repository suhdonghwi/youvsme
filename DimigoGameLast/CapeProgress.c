#include "WaveAudio.h"

#include "CapeProgress.h"
#include "SpriteResources.h"

extern WaveData g_wave_data;

void on_update_cape_progress(GameObject* cape_progress) {
  double progress = (double)g_wave_data.wave_hdr.dwBytesRecorded /
                    g_wave_data.wave_hdr.dwBufferLength;
  cape_progress->pos.x = 200 + 450 * progress;
}

GameObject* create_cape_progress() {
  GameObject* cape_progress = init_game_object();

  cape_progress->sprites = player1_sprites;
  cape_progress->sprite_index = 2;
  cape_progress->pos = (Pos){200, 20};

  cape_progress->on_update = on_update_cape_progress;

  return cape_progress;
}
