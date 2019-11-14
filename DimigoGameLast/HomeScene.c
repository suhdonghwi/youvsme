#include "HomeScene.h"

void on_render_home_scene(GameScene* home_scene, HDC main_dc) {}

void on_first_render_home_scene(GameScene* home_scene, HDC main_dc) {
  PlaySound(TEXT("Sound/main_bgm.wav"), NULL,
            SND_FILENAME | SND_ASYNC | SND_LOOP);
}

GameScene* create_home_scene() {
  GameScene* scene = init_scene();

  scene->on_first_render = on_first_render_home_scene;

  scene->sleep_duration = 20;

  return scene;
}
