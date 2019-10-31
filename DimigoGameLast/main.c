#include <stdio.h>

#include <Windows.h>
#include <mmsystem.h>
#include <vfw.h>

#include "Camera.h"
#include "WaveAudio.h"

#include "SpriteResources.h"

#include "Bird.h"
#include "GameObject.h"

int main() {
  HWND window = GetConsoleWindow();
  HDC window_dc = GetDC(window);
  HINSTANCE inst = GetModuleHandle(NULL);

  SetWindowPos(window, (HWND)0, 100, 100, 750, 650, 0);
  RECT window_rect;
  GetClientRect(window, &window_rect);
  window_rect.right = (LONG)(window_rect.right * 1.3);
  window_rect.bottom = (LONG)(window_rect.bottom * 1.3);

  HBRUSH background_brush = GetStockObject(BLACK_BRUSH);

  init_sprite_resources(inst);

  GameObject bird = make_bird();

  WaveData wave_data;
  init_wave_data(&wave_data);

  int was_up = 0;
  int y_offset = 30;

  while (1) {
    double volume;
    get_current_volume(wave_data, &volume);

    if (volume > 0.8) {
      bird.pos.y -= 50;
    } else if (volume > 0.6) {
      bird.pos.y -= 30;
    } else if (volume > 0.4) {
      bird.pos.y -= 15;
    } else {
      bird.pos.y += 15;
    }

    FillRect(window_dc, &window_rect, background_brush);
    render_game_object(bird, window_dc);
  }

  system("pause");
}