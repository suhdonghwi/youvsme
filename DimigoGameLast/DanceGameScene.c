#include "DanceGameScene.h"
#include "Dancer.h"
#include "SpriteResources.h"

void init_dance_queue(DanceDirection** queue, int size) {
  *queue = malloc(sizeof(DanceDirection) * size);
  if (*queue == NULL) return;

  for (int i = 0; i < size; i++) {
    (*queue)[i] = DANCE_NONE;
  }
}

void on_render_dance_game_scene(GameScene* scene, HDC main_dc) {
  DanceGameSceneData* data = (DanceGameSceneData*)scene->data;

  render_bitmap(background_sprites[data->is_coco_turn ? 5 : 4], main_dc,
                (Pos){0, 0}, 20.25);

  if (!data->is_coco_turn) {
    DancerData* dingding_data = (DancerData*)data->dingding->data;

    if (dingding_data->dance_queue == NULL) {
      init_dance_queue(&dingding_data->dance_queue, 4);
      dingding_data->dance_max = 4;
      dingding_data->is_dancing = true;
    }
  }
}

GameScene* create_dance_game_scene() {
  GameScene* scene = init_scene();

  SHORT* coco_keys = malloc(sizeof(SHORT) * 4);
  if (coco_keys == NULL) return NULL;
  coco_keys[0] = 0x57;
  coco_keys[1] = 0x44;
  coco_keys[2] = 0x53;
  coco_keys[3] = 0x41;

  SHORT* dingding_keys = malloc(sizeof(SHORT) * 4);
  if (dingding_keys == NULL) return NULL;
  dingding_keys[0] = VK_UP;
  dingding_keys[1] = VK_RIGHT;
  dingding_keys[2] = VK_DOWN;
  dingding_keys[3] = VK_LEFT;

  GameObject* coco = create_dancer(true, coco_keys);
  coco->pos = (Pos){290, 280};
  insert_game_object(coco, scene);

  GameObject* dingding = create_dancer(false, dingding_keys);
  dingding->pos = (Pos){650, 280};
  insert_game_object(dingding, scene);

  DanceGameSceneData* data = malloc(sizeof(DanceGameSceneData));
  if (data == NULL) return NULL;
  data->coco = coco;
  data->dingding = dingding;
  data->is_coco_turn = false;

  scene->data = data;

  scene->on_render = on_render_dance_game_scene;
  return scene;
}