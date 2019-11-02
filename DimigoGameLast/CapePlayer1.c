#include "CapePlayer1.h"

#include "SpriteResources.h"
#include "WaveAudio.h"

extern WaveData g_wave_data;

void on_update_cape_player1(GameObject* cape_player1) {
  if (waveInUnprepareHeader(g_wave_data.wave_in, &g_wave_data.wave_hdr,
                            sizeof(WAVEHDR)) == WAVERR_STILLPLAYING) {
    Sleep(15);
    DWORD recorded = g_wave_data.wave_hdr.dwBytesRecorded / 2;
    short int max = 0;

    if (recorded - 500 < 0) return;
    for (int i = recorded - 500; i < recorded; i++) {
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
  } else {
    printf("HELLO!");
  }
}

GameObject* create_cape_player1() {
  GameObject* cape_player1 = init_game_object();

  cape_player1->sprites = cape_player1_sprites;
  cape_player1->sprite_index = 0;
  cape_player1->pos = (Pos){60, 100};
  cape_player1->scale = 4;

  cape_player1->on_update = on_update_cape_player1;

  return cape_player1;
}