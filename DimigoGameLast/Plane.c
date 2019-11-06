#include "Plane.h"

#include "GameScene.h"
#include "PlaneGameScene.h"
#include "SpriteResources.h"
#include "WaveAudio.h"

extern GameScene* g_current_scene;
extern GameScene* g_new_scene;

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

    switch (plane_data->state) {
      case PLANE_READY:
        if (volume > 0.6) {
          plane_data->state = PLANE_FLYING;
        }
        break;
      case PLANE_FLYING:
        if (volume > 0.1) {
          plane->pos.x += 3;
        } else {
          plane_data->state = PLANE_DESCENDING;
        }
        break;
      case PLANE_DESCENDING:
        plane->pos.x += 3;
        plane->pos.y += 3;

        break;
      case PLANE_LANDED:
        break;
    }
  }
}

GameObject* create_plane(bool coco_plane) {
  GameObject* plane = init_game_object(plane_sprites);
  if (!coco_plane) plane->sprite_index = 1;

  plane->scale = 2;
  plane->on_render = on_render_plane;

  PlaneData* plane_data = malloc(sizeof(PlaneData));
  if (plane_data == NULL) return NULL;

  plane_data->state = PLANE_READY;
  init_wave_data(&plane_data->wave_data, 300);

  plane->data = plane_data;
  return plane;
}
