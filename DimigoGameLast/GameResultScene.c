#include "GameResultScene.h"

#include "CapeBackground.h"
#include "CheeringPlayer.h"
#include "GameScene.h"

GameScene* create_game_result_scene(bool player1_won) {
  GameScene* scene = init_scene();

  GameObject* result_background = create_cape_background();
  insert_game_object(result_background, scene);

  GameObject* cheering_player = create_cheering_player(player1_won);
  insert_game_object(cheering_player, scene);

  return scene;
}
