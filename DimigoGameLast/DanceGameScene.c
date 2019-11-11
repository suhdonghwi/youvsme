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

void deinit_dance_queue(DanceDirection** queue) {
  free(*queue);
  *queue = NULL;
}

void on_render_dance_game_scene(GameScene* scene, HDC main_dc) {
  DanceGameSceneData* data = (DanceGameSceneData*)scene->data;

  render_bitmap(background_sprites[data->is_coco_turn ? 5 : 4], main_dc,
                (Pos){0, 0}, 20.25);

  DancerData* dancer_data =
      data->is_coco_turn ? data->coco->data : data->dingding->data;

  if (dancer_data->dance_queue == NULL) {
    init_dance_queue(&dancer_data->dance_queue, 4);
    dancer_data->dance_max = 4;
    dancer_data->is_dancing = true;
  }

  if (is_dance_queue_full(dancer_data->dance_queue, dancer_data->dance_max)) {
    deinit_dance_queue(&dancer_data->dance_queue);
    dancer_data->is_dancing = false;
    dancer_data->dance_max = 0;
    data->is_coco_turn = !data->is_coco_turn;
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
  coco->pos = (Pos){290, 355};
  insert_game_object(coco, scene);

  GameObject* dingding = create_dancer(false, dingding_keys);
  dingding->pos = (Pos){710, 355};
  insert_game_object(dingding, scene);

  DanceGameSceneData* data = malloc(sizeof(DanceGameSceneData));
  if (data == NULL) return NULL;
  data->coco = coco;
  data->dingding = dingding;
  data->is_coco_turn = false;

  scene->data = data;
  scene->sleep_duration = 5;

  scene->on_render = on_render_dance_game_scene;
  return scene;
}