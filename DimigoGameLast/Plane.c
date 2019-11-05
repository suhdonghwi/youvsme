#include "Plane.h"
#include "GameScene.h"
#include "SpriteResources.h"
#include "WaveAudio.h"

extern GameScene* g_current_scene;

typedef struct tagPlaneData {
  WaveData wave_data;
  bool is_flying;
  bool is_landed;
} PlaneData;

void on_render_plane(GameObject* plane, HDC main_dc) {
  PlaneData* plane_data = (PlaneData*)(plane->data);
  if (waveInUnprepareHeader(plane_data->wave_data.wave_in,
                            &plane_data->wave_data.wave_hdr,
                            sizeof(WAVEHDR)) == WAVERR_STILLPLAYING) {
    DWORD recorded = plane_data->wave_data.wave_hdr.dwBytesRecorded / 2;
    short int max = 0;

    if (recorded - 300 < 0) return;
    for (DWORD i = recorded - 300; i < recorded; i++) {
      short int data = plane_data->wave_data.sample_data[i];
      if (data > max) {
        max = data;
      }
    }

    double volume = max / 32767.0;

    if (plane_data->is_landed) return;

    if (volume > 0.4) {
      if (plane_data->is_flying) {
        plane->pos.x += 3;
      } else {
        plane_data->is_flying = true;
      }
    } else {
      if (plane_data->is_flying) {
        plane_data->is_flying = false;
        plane_data->is_landed = true;

        insert_game_object(create_plane(), g_current_scene);
      }
    }
  }
}

GameObject* create_plane() {
  GameObject* plane = init_game_object(plane_sprites);

  plane->on_render = on_render_plane;

  PlaneData* plane_data = malloc(sizeof(PlaneData));
  if (plane_data == NULL) return NULL;

  plane_data->is_flying = false;
  plane_data->is_landed = false;
  init_wave_data(&plane_data->wave_data);

  plane->data = plane_data;
  return plane;
}
