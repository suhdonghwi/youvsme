#include "HomeScene.h"

GameScene* create_home_scene() {
  GameScene* scene = init_scene();
  scene->sleep_duration = 100;
}
