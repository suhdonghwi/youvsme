#include <stdio.h>

#include <Windows.h>
#include <mmsystem.h>
#include <vfw.h>

#include "Camera.h"
#include "WaveAudio.h"

#include "SpriteResources.h"

#include "Bird.h"
#include "CapeGameScene.h"

#include "GameObject.h"
#include "GameScene.h"

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

  GameScene* scene = create_cape_game_scene();

  while (1) {
    FillRect(window_dc, &window_rect, background_brush);

    render_game_scene(scene, window_dc);
    Sleep(10);
  }

  system("pause");
}