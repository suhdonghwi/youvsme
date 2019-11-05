#include "CapeGameScene.h"

#include "CapePlayer1.h"
#include "CapePlayer2.h"
#include "Spit.h"
#include "SpriteResources.h"

void on_render_cape_game_scene(GameScene* scene, HDC main_dc) {
  render_bitmap(background_sprites[0], main_dc, (Pos){0, 0}, 1.0);
}

GameScene* create_cape_game_scene() {
  GameScene* scene = init_scene();

  GameObject* cape_player1 = create_cape_player1();
  insert_game_object(cape_player1, scene);

  GameObject* cape_player2 = create_cape_player2();
  insert_game_object(cape_player2, scene);

  scene->on_render = on_render_cape_game_scene;
  scene->sleep_duration = 15;

  return scene;
}
