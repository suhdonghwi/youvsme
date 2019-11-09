#include "PullGameScene.h"

#include "SpriteResources.h"
#include "String.h"

void on_render_pull_game_scene(GameScene* scene, HDC main_dc) {
  render_bitmap(background_sprites[2], main_dc, (Pos){0, 0}, 25);
}

GameScene* create_pull_game_scene() {
  GameScene* scene = init_scene();

  GameObject* string = create_string();
  insert_game_object(string, scene);

  scene->on_render = on_render_pull_game_scene;

  return scene;
}
