#include "PullGameScene.h"

#include "Flag.h"
#include "SpriteResources.h"
#include "String.h"

void on_render_pull_game_scene(GameScene* scene, HDC main_dc) {
  render_bitmap(background_sprites[2], main_dc, (Pos){0, 0}, 25);
}

GameScene* create_pull_game_scene() {
  GameScene* scene = init_scene();

  GameObject* string = create_string();
  insert_game_object(string, scene);

  GameObject* coco_flag = create_flag(true);
  coco_flag->pos = (Pos){30, 500};
  coco_flag->scale = 7;
  insert_game_object(coco_flag, scene);

  GameObject* dingding_flag = create_flag(false);
  dingding_flag->pos = (Pos){1150, 500};
  dingding_flag->scale = 7;
  insert_game_object(dingding_flag, scene);

  scene->on_render = on_render_pull_game_scene;

  return scene;
}