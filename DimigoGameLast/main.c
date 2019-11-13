#include <stdbool.h>
#include <stdio.h>
#include <time.h>

#include <Windows.h>
#include <mmsystem.h>
#include <shellscalingapi.h>
#include <vfw.h>

#include "KeyInput.h"
#include "WaveAudio.h"

#include "SpriteResources.h"

#include "DanceGameScene.h"
#include "DiskGameScene.h"
#include "GameHelpScene.h"
#include "GameResultScene.h"
#include "PullGameScene.h"
#include "ReadyStartScene.h"
#include "StoryScene.h"

#include "GameObject.h"
#include "GameScene.h"

extern SHORT g_pressed_map[256];
extern SHORT g_prev_pressed_map[256];

GameScene* g_current_scene;
GameScene* g_new_scene;
int g_coco_score = 0;
int g_dingding_score = 0;
HDC g_window_dc;
bool g_story_mode;

int main() {
  srand((unsigned int)time(NULL));
  SetProcessDpiAwareness(PROCESS_PER_MONITOR_DPI_AWARE);

  HWND window = GetConsoleWindow();
  g_window_dc = GetDC(window);
  HINSTANCE inst = GetModuleHandle(NULL);

  init_sprite_resources(inst);

  BITMAP bitmap_data;
  GetObject(background_sprites[1], sizeof(BITMAP), &bitmap_data);
  int window_width = (int)(bitmap_data.bmWidth * 4.5),
      window_height = (int)(bitmap_data.bmHeight * 4.5);
  SetWindowPos(window, (HWND)0, 0, 0, (int)(window_width * 1.031),
               (int)(window_height * 1.063), 0);

  RECT window_rect;
  GetClientRect(window, &window_rect);

  // HANDLE std_input = GetStdHandle(STD_INPUT_HANDLE);
  // DWORD num_read, num_input;
  // INPUT_RECORD input_buf[32];

  HBRUSH background_brush = GetStockObject(BLACK_BRUSH);

  AddFontResource("DungGeunMo.ttf");
  // RemoveFontResource("DungGeunMo.ttf");

  /*GameScene* ready_scene = create_readystart_scene(
      create_pull_game_scene(), pull_ready_sprites, 2, (Pos){560, 300});
  g_current_scene = create_game_help_scene(game_help_sprites[1],
                                           logo_sprites[1], ready_scene);*/
  /*GameScene* ready_scene =
      create_readystart_scene(create_disk_game_scene(true, (Pos){0, 0}),
                              coco_disk_ready_sprites, 3, (Pos){560, 300});
  g_current_scene = create_game_help_scene(game_help_sprites[0],
                                           logo_sprites[0], ready_scene);*/
  // g_current_scene = create_pull_game_scene();

  // g_current_scene = create_disk_game_scene(true, (Pos){0, 0});
  // g_current_scene = create_game_result_scene(false);
  // g_current_scene = create_pull_game_scene();
  g_story_mode = true;

  wchar_t** t = malloc(sizeof(wchar_t*) * 2);

  t[0] = malloc(sizeof(wchar_t) * 100);
  wcscpy(t[0], L"¾È³çÇÏ¼¼¿ä!");
  t[1] = malloc(sizeof(wchar_t) * 100);
  wcscpy(t[1], L"Goodbye, world!");

  RECT rect;
  rect.top = 50;
  rect.left = 680;
  rect.bottom = 300;
  rect.right = 1050;
  g_current_scene = create_story_scene(create_dance_game_scene(),
                                       game_help_sprites[2], t, 2, rect);
  g_new_scene = NULL;

  while (1) {
    /*GetNumberOfConsoleInputEvents(std_input, &num_input);

    if (num_input > 0) {
      ReadConsoleInput(std_input, input_buf, 32, &num_read);

      for (WORD i = 0; i < num_read; i++) {
        switch (input_buf[i].EventType) {
          case KEY_EVENT: {
            KEY_EVENT_RECORD event = input_buf[i].Event.KeyEvent;
            g_pressed_map[event.wVirtualKeyCode] = event.bKeyDown;
          }
        }
      }
    }*/

    update_pressed_map();
    render_game_scene(g_current_scene, g_window_dc, window_width,
                      window_height);

    if (g_new_scene != NULL) {
      deinit_scene(g_current_scene);
      g_current_scene = g_new_scene;
      g_new_scene = NULL;

      FillRect(g_window_dc, &window_rect, background_brush);
    }
  }

  ReleaseDC(window, g_window_dc);
  DeleteObject(background_brush);
  deinit_sprite_resources();
  deinit_scene(g_current_scene);
  system("pause");
}