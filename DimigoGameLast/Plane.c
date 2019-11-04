#include "Plane.h"
#include "SpriteResources.h"
#include "WaveAudio.h"

static WaveData plane_wave_data;
static bool is_flying = false;
static bool is_landed = false;

void on_render_plane(GameObject* plane, HDC main_dc) {
  if (waveInUnprepareHeader(plane_wave_data.wave_in, &plane_wave_data.wave_hdr,
                            sizeof(WAVEHDR)) == WAVERR_STILLPLAYING) {
    DWORD recorded = plane_wave_data.wave_hdr.dwBytesRecorded / 2;
    short int max = 0;

    if (recorded - 300 < 0) return;
    for (DWORD i = recorded - 300; i < recorded; i++) {
      short int data = plane_wave_data.sample_data[i];
      if (data > max) {
        max = data;
      }
    }

    double volume = max / 32767.0;

    if (is_landed) return;

    if (volume > 0.4) {
      if (is_flying) {
        plane->pos.x += 1;
      } else {
        is_flying = true;
      }
    } else {
      if (is_flying) {
        is_flying = false;
        is_landed = true;
      }
    }
  }
}

GameObject* create_plane() {
  init_wave_data(&plane_wave_data);
  GameObject* plane = init_game_object(plane_sprites);

  plane->on_render = on_render_plane;
  return plane;
}
