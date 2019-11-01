#include <stdbool.h>
#include <stdio.h>

#include <Windows.h>
#include <mmsystem.h>
#include <vfw.h>

#include "Camera.h"
#include "WaveAudio.h"

#include "SpriteResources.h"

#include "CapeGameScene.h"

#include "GameObject.h"
#include "GameScene.h"

WaveData g_wave_data;
bool g_pressed_map[0xFE] = {
    false,
};

int main() {
  HWND window = GetConsoleWindow();
  HDC window_dc = GetDC(window);
  HINSTANCE inst = GetModuleHandle(NULL);

  SetWindowPos(window, (HWND)0, 100, 100, 750, 650, 0);
  RECT window_rect;
  GetClientRect(window, &window_rect);
  window_rect.right = (LONG)(window_rect.right * 1.3);
  window_rect.bottom = (LONG)(window_rect.bottom * 1.3);

  HANDLE std_input = GetStdHandle(STD_INPUT_HANDLE);
  DWORD num_read, num_input;
  INPUT_RECORD input_buf[128];

  init_sprite_resources(inst);
  init_wave_data(&g_wave_data);

  GameScene* scene = create_cape_game_scene();

  while (1) {
    GetNumberOfConsoleInputEvents(std_input, &num_input);

    if (num_input > 0) {
      ReadConsoleInput(std_input, input_buf, 128, &num_read);

      for (WORD i = 0; i < num_read; i++) {
        switch (input_buf[i].EventType) {
          case KEY_EVENT: {
            KEY_EVENT_RECORD event = input_buf[i].Event.KeyEvent;
            g_pressed_map[event.wVirtualKeyCode] = event.bKeyDown;
          }
        }
      }
    }

    render_game_scene(scene, window_dc);
    Sleep(10);
  }

  deinit_sprite_resources();
  deinit_scene(scene);
  system("pause");
}