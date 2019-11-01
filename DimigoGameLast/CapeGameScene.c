#include "CapeGameScene.h"

#include "Bird.h"

GameScene* create_cape_game_scene() {
  GameScene* scene = create_scene();

  GameObject* bird = create_bird();
  insert_game_object(bird, scene);

  return scene;
}
