#include "CapePlayer1.h"

#include "GameResultScene.h"
#include "SpriteResources.h"
#include "WaveAudio.h"

extern GameScene* g_new_scene;

typedef struct tagCapePlayer1Data {
  WaveData wave_data;

  RECT bar_rect;
  HBRUSH bar_brush, fill_brush;
} CapePlayer1Data;

void on_render_cape_player1(GameObject* cape_player1, HDC main_dc) {
  CapePlayer1Data* player_data = (CapePlayer1Data*)(cape_player1->data);

  double progress = (double)player_data->wave_data.wave_hdr.dwBytesRecorded /
                    player_data->wave_data.wave_hdr.dwBufferLength;

  RECT fill_rect;
  fill_rect.top = 20;
  fill_rect.bottom = 20 + 30;
  fill_rect.left = 190;
  fill_rect.right = (LONG)(240 + 450 * progress);

  FillRect(main_dc, &player_data->bar_rect, player_data->bar_brush);
  FillRect(main_dc, &fill_rect, player_data->fill_brush);

  render_bitmap(finish_flag_sprites[0], main_dc, (Pos){700, 15}, 0.5);

  if (waveInUnprepareHeader(player_data->wave_data.wave_in,
                            &player_data->wave_data.wave_hdr,
                            sizeof(WAVEHDR)) == WAVERR_STILLPLAYING) {
    DWORD recorded = player_data->wave_data.wave_hdr.dwBytesRecorded / 2;
    short int max = 0;

    if (recorded - 300 < 0) return;
    for (DWORD i = recorded - 300; i < recorded; i++) {
      short int data = player_data->wave_data.sample_data[i];
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

    if (cape_player1->pos.y > 650) {
      cape_player1->pos.y = 650;
    } else if (cape_player1->pos.y < 0) {
      cape_player1->pos.y = 0;
    }
  } else {
    g_new_scene = create_game_result_scene(true);
  }
}

void on_destroy_cape_player1(GameObject* cape_player1) {
  CapePlayer1Data* player_data = (CapePlayer1Data*)(cape_player1->data);

  deinit_wave_data(player_data->wave_data);
  DeleteObject(player_data->bar_brush);
  DeleteObject(player_data->fill_brush);
}

void on_collide_cape_player1(GameObject* cape_player1, GameObject* object) {
  if (strcmp(object->tag, "spit") == 0) {
    g_new_scene = create_game_result_scene(false);
  }
}

GameObject* create_cape_player1() {
  GameObject* cape_player1 = init_game_object(dingding_sprites);

  cape_player1->sprite_index = 2;
  cape_player1->pos = (Pos){60, 100};
  cape_player1->scale = 4;
  cape_player1->collidable = true;

  cape_player1->on_render = on_render_cape_player1;
  cape_player1->on_destroy = on_destroy_cape_player1;
  cape_player1->on_collide = on_collide_cape_player1;

  CapePlayer1Data* player_data = malloc(sizeof(CapePlayer1Data));
  if (player_data == NULL) return NULL;
  init_wave_data(&player_data->wave_data);

  player_data->bar_rect.top = 20;
  player_data->bar_rect.bottom = 20 + 30;
  player_data->bar_rect.left = 190;
  player_data->bar_rect.right = 190 + 500;

  player_data->bar_brush = GetStockObject(LTGRAY_BRUSH);
  player_data->fill_brush = CreateSolidBrush(RGB(0, 200, 0));

  cape_player1->data = player_data;

  return cape_player1;
}