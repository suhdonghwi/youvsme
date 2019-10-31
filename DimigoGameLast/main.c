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

  init_sprite_resources(inst);

  GameObject bird = make_bird();

  while (1) {
    render_game_object(bird, window_dc);
  }

  system("pause");
}