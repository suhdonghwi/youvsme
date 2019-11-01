#include "CapeGameScene.h"

#include "CapeChar1.h"

GameScene* create_cape_game_scene() {
  GameScene* scene = create_scene();

  GameObject* cape_char1 = create_cape_char1();
  insert_game_object(cape_char1, scene);

  return scene;
}
