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

// ���� ��� ���� ȭ���� on_render �ݹ��Դϴ�. ����Ű�� Enter Ű�� ���ؼ� �޴���
// Ž���ϰ� ������ �� �ֵ��� �մϴ�.
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

  char back_str[] = "[Backspace]Ű�� ���� �ڷΰ���";
  TextOut(main_dc, 380, 610, back_str, strlen(back_str));
}

// ���� ��� ���� ȭ���� ������ �� ��ȯ�մϴ�.
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
