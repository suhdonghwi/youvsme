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

GameScene* g_current_scene;
GameScene* g_new_scene;

int g_coco_score = 0;
int g_dingding_score = 0;

HDC g_window_dc;
bool g_story_mode;

int main() {
  load_set_score();  // 세트 스코어를 로드합니다.

  srand((unsigned int)time(
      NULL));  // 난수 생성 시드를 실행 시마다 다르게 설정합니다.
  SetProcessDpiAwareness(
      PROCESS_PER_MONITOR_DPI_AWARE);  // 해상도, 확대 비율에 관계없이 윈도우가
                                       // 같은 사이즈로 나오게 합니다.

  // 콘솔 윈도우, DC, 핸들을 가져옵니다.
  HWND window = GetConsoleWindow();
  g_window_dc = GetDC(window);
  HINSTANCE inst = GetModuleHandle(NULL);

  // 스프라이트 자원을 초기화합니다.
  init_sprite_resources(inst);

  // 대표 배경의 약 20배 비율로 윈도우 크기를 설정합니다.
  BITMAP bitmap_data;
  GetObject(background_sprites[1], sizeof(BITMAP), &bitmap_data);
  int window_width = (int)(bitmap_data.bmWidth * 4.5),
      window_height = (int)(bitmap_data.bmHeight * 4.5);
  SetWindowPos(window, (HWND)0, 0, 0, (int)(window_width * 1.031),
               (int)(window_height * 1.063), 0);

  // 윈도우의 RECT 데이터를 가져옵니다.
  RECT window_rect;
  GetClientRect(window, &window_rect);

  // 기본 배경을 색칠하는 브러쉬를 가져옵니다.
  HBRUSH background_brush = GetStockObject(BLACK_BRUSH);

  // AddFontResource("DungGeunMo.ttf");
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
  // g_current_scene = create_after_dance_story(true);
  // g_current_scene = create_home_scene();

  // 현재 화면을 홈 화면으로 설정하고, 다음 화면을 NULL로 설정합니다.
  g_current_scene = create_home_scene();
  g_new_scene = NULL;

  while (1) {
    // 현재 누르고 있는 키들을 나타내는 배열을 업데이트합니다.
    update_pressed_map();
    // 현재 화면을 렌더링합니다.
    render_game_scene(g_current_scene, g_window_dc, window_width,
                      window_height);

    // 새로운 화면이 대입되어있으면 현재 화면을 해제하고 현재 화면을 새로운
    // 화면으로 바꿉니다.
    if (g_new_scene != NULL) {
      deinit_scene(g_current_scene);
      g_current_scene = g_new_scene;
      g_new_scene = NULL;
    }
  }

  // 프로그램이 끝날 시 할당된 자원을 전부 해제합니다.
  ReleaseDC(window, g_window_dc);
  DeleteObject(background_brush);
  deinit_sprite_resources();
  deinit_scene(g_current_scene);
  system("pause");
}