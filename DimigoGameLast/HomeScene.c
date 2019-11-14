#include "HomeScene.h"
#include "InfiniteScene.h"
#include "KeyInput.h"
#include "SpriteResources.h"
#include "StoryScene.h"

extern bool g_story_mode;
extern GameScene* g_new_scene;

void on_render_home_scene(GameScene* scene, HDC main_dc) {
  HomeSceneData* data = scene->data;

  render_bitmap(home_sprites[data->index], main_dc, (Pos){0, 0}, 5.1);

  if (is_pressed(VK_LEFT)) {
    data->index = 0;
  } else if (is_pressed(VK_RIGHT)) {
    data->index = 1;
  } else if (is_pressed(VK_RETURN)) {
    if (data->index == 0) {
      g_story_mode = true;
      g_new_scene = create_after_main_story();
    } else {
      Sleep(500);
      g_new_scene = create_infinite_scene();
    }
  }
}

void on_first_render_home_scene(GameScene* scene, HDC main_dc) {
  PlaySound(TEXT("Sound/main_bgm.wav"), NULL,
            SND_FILENAME | SND_ASYNC | SND_LOOP);
}

GameScene* create_home_scene() {
  GameScene* scene = init_scene();

  scene->on_first_render = on_first_render_home_scene;
  scene->on_render = on_render_home_scene;

  scene->sleep_duration = 20;

  HomeSceneData* data = malloc(sizeof(HomeSceneData));
  if (data == NULL) return NULL;
  data->index = 0;

  scene->data = data;

  return scene;
}
