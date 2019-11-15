#include "PullGameScene.h"

#include "Flag.h"
#include "SpriteResources.h"
#include "String.h"

// 줄다리기 게임 화면의 on_render 콜백입니다. 배경화면을 렌더링합니다.
void on_render_pull_game_scene(GameScene* scene, HDC main_dc) {
  render_bitmap(background_sprites[2], main_dc, (Pos){0, 0}, 20.25);
}

// 줄다리기 게임 화면의 on_first_render 콜백입니다. 줄다리기 배경 음악을
// 재생합니다.
void on_first_render_pull_game_scene(GameScene* scene, HDC main_dc) {
  PlaySound(NULL, 0, 0);
  PlaySound(TEXT("Sound/pull_bgm.wav"), NULL,
            SND_FILENAME | SND_ASYNC | SND_LOOP);
}

// 줄다리기 게임 화면을 생성한 뒤 반환합니다.
GameScene* create_pull_game_scene() {
  GameScene* scene = init_scene();

  scene->on_first_render = on_first_render_pull_game_scene;

  GameObject* string = create_string();
  insert_game_object(string, scene);

  GameObject* coco_flag = create_flag(true);
  coco_flag->pos = (Pos){30, 450};
  coco_flag->scale = 7;
  insert_game_object(coco_flag, scene);

  GameObject* dingding_flag = create_flag(false);
  dingding_flag->pos = (Pos){1030, 450};
  dingding_flag->scale = 7;
  insert_game_object(dingding_flag, scene);

  scene->on_render = on_render_pull_game_scene;

  return scene;
}
