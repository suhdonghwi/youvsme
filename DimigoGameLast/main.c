#include <stdbool.h>
#include <stdio.h>
#include <time.h>

#include <Windows.h>
#include <mmsystem.h>
#include <shellscalingapi.h>
#include <vfw.h>

#include "KeyInput.h"
#include "SetScore.h"
#include "WaveAudio.h"

#include "SpriteResources.h"

#include "DanceGameScene.h"
#include "DiskGameScene.h"
#include "FinalResultScene.h"
#include "GameHelpScene.h"
#include "GameResultScene.h"
#include "HomeScene.h"
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
  load_set_score();

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
  g_current_scene = create_after_dance_story(true);
  // g_current_scene = create_after_main_story();
  g_story_mode = true;

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
    }
  }

  ReleaseDC(window, g_window_dc);
  DeleteObject(background_brush);
  deinit_sprite_resources();
  deinit_scene(g_current_scene);
  system("pause");
}