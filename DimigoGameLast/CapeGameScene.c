#include "CapeGameScene.h"

#include "CapeBackground.h"
#include "CapePlayer1.h"
#include "CapePlayer2.h"

GameScene* create_cape_game_scene() {
  GameScene* scene = create_scene();

  GameObject* cape_background = create_cape_background();
  insert_game_object(cape_background, scene);

  GameObject* cape_player2 = create_cape_player2();
  insert_game_object(cape_player2, scene);

  GameObject* cape_player1 = create_cape_player1();
  insert_game_object(cape_player1, scene);

  return scene;
}
