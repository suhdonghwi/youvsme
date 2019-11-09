#include "PullGameScene.h"

#include "String.h"

GameScene* create_pull_game_scene() {
  GameScene* scene = init_scene();

  GameObject* string = create_string();
  insert_game_object(string, scene);

  return scene;
}
