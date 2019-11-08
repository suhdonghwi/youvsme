#include <stdbool.h>
#include <stdio.h>

#include <Windows.h>
#include <mmsystem.h>
#include <shellscalingapi.h>
#include <vfw.h>

#include "Camera.h"
#include "WaveAudio.h"

#include "SpriteResources.h"

#include "GameHelpScene.h"
#include "GameResultScene.h"
#include "PlaneGameScene.h"
#include "ReadyStartScene.h"

#include "GameObject.h"
#include "GameScene.h"

GameScene* g_current_scene;
GameScene* g_new_scene;
bool g_pressed_map[0xFE] = {
    false,
};
int g_coco_score = 0;
int g_dingding_score = 0;

GameScene* main_plane_game_scene() {
  return create_plane_game_scene(true, NULL);
}

int main() {
  SetProcessDpiAwareness(PROCESS_PER_MONITOR_DPI_AWARE);

  HWND window = GetConsoleWindow();
  HDC window_dc = GetDC(window);
  HINSTANCE inst = GetModuleHandle(NULL);

  init_sprite_resources(inst);

  BITMAP bitmap_data;
  GetObject(background_sprites[0], sizeof(BITMAP), &bitmap_data);
  SetWindowPos(window, (HWND)0, 0, 0, 900, 780, 0);

  RECT window_rect;
  GetClientRect(window, &window_rect);

  HANDLE std_input = GetStdHandle(STD_INPUT_HANDLE);
  DWORD num_read, num_input;
  INPUT_RECORD input_buf[128];

  HBRUSH background_brush = GetStockObject(BLACK_BRUSH);

  HFONT score_font = CreateFont(50, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0,
                                0, VARIABLE_PITCH | FF_ROMAN,
                                TEXT("DSEG7 Classic Mini-Bold Italic"));
  SelectObject(window_dc, score_font);
  SetBkMode(window_dc, TRANSPARENT);
  SetTextColor(window_dc, RGB(255, 0, 0));

  // GameScene* ready_scene =
  create_readystart_scene(create_plane_game_scene(true, NULL),
                          coco_turn_sprites, 3, (Pos){70, 100});
  // g_current_scene = create_game_help_scene(game_help_sprites[0],
  // ready_scene);
  g_current_scene = create_plane_game_scene(true, NULL);
  g_new_scene = NULL;

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

    render_game_scene(g_current_scene, window_dc);

    if (g_new_scene != NULL) {
      deinit_scene(g_current_scene);
      g_current_scene = g_new_scene;
      g_new_scene = NULL;

      FillRect(window_dc, &window_rect, background_brush);
    }
  }

  ReleaseDC(window, window_dc);
  DeleteObject(score_font);
  DeleteObject(background_brush);
  deinit_sprite_resources();
  deinit_scene(g_current_scene);
  system("pause");
}