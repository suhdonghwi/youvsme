#include "CapePlayer1.h"

#include "SpriteResources.h"
#include "WaveAudio.h"

WaveData g_wave_data;

void on_update_cape_player1(GameObject* cape_player1) {
  if (waveInUnprepareHeader(g_wave_data.wave_in, &g_wave_data.wave_hdr,
                            sizeof(WAVEHDR)) == WAVERR_STILLPLAYING) {
    Sleep(15);
    DWORD recorded = g_wave_data.wave_hdr.dwBytesRecorded / 2;
    short int max = 0;

    if (recorded - 300 < 0) return;
    for (DWORD i = recorded - 300; i < recorded; i++) {
      short int data = g_wave_data.sample_data[i];
      if (data > max) {
        max = data;
      }
    }

    double volume = max / 32767.0;

    if (volume > 0.8) {
      cape_player1->pos.y -= 20;
    } else if (volume > 0.6) {
      cape_player1->pos.y -= 15;
    } else if (volume > 0.4) {
      cape_player1->pos.y -= 10;
    } else {
      cape_player1->pos.y += 10;
    }

    if (cape_player1->pos.y > 700) {
      cape_player1->pos.y = 700;
    } else if (cape_player1->pos.y < 0) {
      cape_player1->pos.y = 0;
    }
  }
}

void on_destroy_cape_player1(GameObject* cape_player1) {
  deinit_wave_data(g_wave_data);
}

void on_collide_cape_player1(GameObject* cape_player1, GameObject* object) {}

GameObject* create_cape_player1() {
  init_wave_data(&g_wave_data);
  GameObject* cape_player1 = init_game_object();

  cape_player1->sprites = cape_player1_sprites;
  cape_player1->sprite_index = 0;
  cape_player1->pos = (Pos){60, 100};
  cape_player1->scale = 4;
  cape_player1->collidable = true;

  cape_player1->on_update = on_update_cape_player1;
  cape_player1->on_destroy = on_destroy_cape_player1;
  cape_player1->on_collide = on_collide_cape_player1;

  return cape_player1;
}