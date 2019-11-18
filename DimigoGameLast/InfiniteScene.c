#include "InfiniteScene.h"
#include "SpriteResources.h"

#include "DanceGameScene.h"
#include "DiskGameScene.h"
#include "GameHelpScene.h"
#include "HomeScene.h"
#include "KeyInput.h"
#include "PullGameScene.h"
#include "ReadyStartScene.h"

extern bool g_story_mode;
extern GameScene* g_new_scene;

extern HFONT g_font_small;

// 무한 모드 선택 화면의 on_render 콜백입니다. 방향키와 Enter 키를 통해서 메뉴를
// 탐색하고 진입할 수 있도록 합니다.
void on_render_infinite_scene(GameScene* scene, HDC main_dc) {
  InfiniteSceneData* data = scene->data;

  render_bitmap(infinite_sprites[data->index], main_dc, (Pos){0, 0}, 5.1);

  if (is_pressed(VK_LEFT)) {
    data->index--;
    if (data->index < 0) {
      data->index = 0;
    }
  } else if (is_pressed(VK_RIGHT)) {
    data->index++;
    if (data->index > 2) data->index = 2;
  } else if (is_pressed(VK_RETURN)) {
    g_story_mode = false;

    if (data->index == 0) {
      g_new_scene = create_disk_help_scene();
    } else if (data->index == 1) {
      g_new_scene = create_pull_help_scene();
    } else if (data->index == 2) {
      g_new_scene = create_dance_help_scene();
    }
  } else if (is_pressed(VK_BACK)) {
    g_new_scene = create_home_scene();
  }

  SelectObject(main_dc, g_font_small);
  SetTextColor(main_dc, RGB(50, 50, 50));

  char back_str[] = "[Backspace]키를 눌러 뒤로가기";
  TextOut(main_dc, 380, 610, back_str, strlen(back_str));
}

// 무한 모드 선택 화면을 생성한 뒤 반환합니다.
GameScene* create_infinite_scene() {
  GameScene* scene = init_scene();

  scene->sleep_duration = 20;
  scene->on_render = on_render_infinite_scene;

  InfiniteSceneData* data = malloc(sizeof(InfiniteSceneData));
  if (data == NULL) return NULL;
  data->index = 0;

  scene->data = data;
  return scene;
}
