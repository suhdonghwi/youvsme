/*
  본 프로그램의 구조는 크게 GameScene(게임 화면)과 GameObject(게임 오브젝트)로
  구성되어있습니다.

  게임 오브젝트는 위치, 크기, 스프라이트 비트맵 등을 담고 있는 구조체이며 렌더링
  시 1 프레임마다 호출되는 on_render 콜백, 소멸시 호출되는 on_destroy 콜백 등
  다양한 콜백 함수를 사용하여 각 게임 오브젝트마다 특징적인 행동을
  정의하게됩니다.

  게임 화면은 여러 개의 게임 오브젝트들로 구성된 연결 리스트입니다. 게임 화면을
  렌더링 하면 리스트가 가지고 있는 게임 오브젝트 원소를 차례대로 모두
  렌더링합니다. 게임 화면 자체도 게임 오브젝트와 유사하게 on_render와 같은
  콜백을 가지고 있습니다.

  게임 화면이 넘어가는 것은 main.c에 있는 g_current_scene, g_new_scene 변수로
  구현하였습니다. g_new_scene 변수는 기본적으로 NULL 값을 가지고 있고,
  g_current_scene은 현재 게임 화면을 나타내는 변수로 main 함수에서는 항상 이
  변수에 담긴 게임 화면만을 렌더링합니다. 어떤 게임 오브젝트 혹은 게임 화면에서
  게임 화면을 변경하고 싶을 때는 g_new_scene에 생성된 다음 화면 데이터를
  대입하면 됩니다. 그러면 main에서 g_new_scene이 NULL이 아님을 확인하게 되고,
  g_current_scene의 메모리를 해제시킨 뒤에 g_current_scene에 새로 들어온 게임
  화면을 대입합니다. 이렇게 게임 화면이 변경되게 됩니다.

  게임 스프라이트 자원은 SpriteResources.h/.c 에서 전부 관리합니다. 아무래도
  게임 오브젝트가 자주 생성되었다가 소멸하는 경우에 스프라이트 자원을 지속적으로
  할당하였다 해제하면 메모리 관리의 복잡성에도, 프로그램의 성능에도 영향이 있을
  것 같아서 스프라이트 자원을 전역 한 곳에 집중하는 것으로 방식을
  변경하였습니다. 어떤 스프라이트를 사용하지 않는 경우에도 메모리가 할당되어있어
  메모리를 많이 사용하기는 하지만, 일단 관리가 편리하고 실제 게임 실행 중에는
  성능에 영향이 없기 때문에 메모리를 비용으로써 지불하고 편의성을 택하였습니다.
*/

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

HFONT g_font_bigger;
HFONT g_font_big;
HFONT g_font_medium;
HFONT g_font_small;

// 윈도우를 생성한 뒤 현재 화면을 렌더링하고, 렌더링이 완료된 뒤 g_new_scene에
// 변화가 있으면 화면을 갱신합니다. 그리고 KeyInput.h에서 사용하는 키 누름
// 정보를 담고 있는 배열 또한 main에서 함수를 호출하여 갱신합니다.
// 기초적이고 전역적으로 사용해야하는 자원들은 대부분 main에서 생성하고,
// 관리합니다.
int main() {
  load_set_score();  // 세트 스코어를 로드합니다.

  srand((unsigned int)time(
      NULL));  // 난수 생성 시드를 실행 시마다 다르게 설정합니다.
  SetProcessDpiAwareness(
      PROCESS_PER_MONITOR_DPI_AWARE);  // 해상도, 확대 비율에 관계없이 윈도우가
                                       // 같은 사이즈로 나오게 합니다.

  AddFontResource("DungGeunMo.ttf");
  g_font_bigger = CreateFont(80, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0,
                             VARIABLE_PITCH | FF_ROMAN, TEXT("둥근모꼴"));
  g_font_big = CreateFont(50, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0,
                          VARIABLE_PITCH | FF_ROMAN, TEXT("둥근모꼴"));
  g_font_medium = CreateFont(30, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0,
                             VARIABLE_PITCH | FF_ROMAN, TEXT("둥근모꼴"));
  g_font_small = CreateFont(25, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0,
                            VARIABLE_PITCH | FF_ROMAN, TEXT("둥근모꼴"));
  RemoveFontResource("DungGeunMo.ttf");

  // 콘솔 윈도우, DC, 핸들을 가져옵니다.
  HWND window = GetConsoleWindow();
  g_window_dc = GetDC(window);
  HINSTANCE inst = GetModuleHandle(NULL);

  // 윈도우를 사이즈 조절하지 못하게 합니다.
  SetWindowLong(
      window, GWL_STYLE,
      GetWindowLong(window, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);

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