#include "WaveAudio.h"

#include "CapeProgress.h"
#include "SpriteResources.h"

extern WaveData g_wave_data;

static HBRUSH bar_brush;
static HBRUSH fill_brush;

void on_render_cape_progress(GameObject* cape_progress, HDC main_dc) {
  double progress = (double)g_wave_data.wave_hdr.dwBytesRecorded /
                    g_wave_data.wave_hdr.dwBufferLength;
  cape_progress->pos.x = (int)(200 + 450 * progress);

  RECT bar_rect;
  bar_rect.top = 20;
  bar_rect.bottom = 20 + 30;
  bar_rect.left = 190;
  bar_rect.right = 190 + 500;

  RECT fill_rect;
  fill_rect.top = 20;
  fill_rect.bottom = 20 + 30;
  fill_rect.left = 190;
  fill_rect.right = (LONG)(240 + 450 * progress);

  FillRect(main_dc, &bar_rect, bar_brush);
  FillRect(main_dc, &fill_rect, fill_brush);

  render_bitmap(finish_flag_sprites[0], main_dc, (Pos){700, 15}, 0.5);
}

void on_destroy_cape_progress(GameObject* cape_progress) {
  DeleteObject(bar_brush);
  DeleteObject(fill_brush);
}

GameObject* create_cape_progress() {
  bar_brush = GetStockObject(LTGRAY_BRUSH);
  fill_brush = CreateSolidBrush(RGB(0, 200, 0));

  GameObject* cape_progress = init_game_object(player1_sprites);

  cape_progress->sprite_index = 2;
  cape_progress->pos = (Pos){200, 20};

  cape_progress->on_render = on_render_cape_progress;
  cape_progress->on_destroy = on_destroy_cape_progress;

  return cape_progress;
}
