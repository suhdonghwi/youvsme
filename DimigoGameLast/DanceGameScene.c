#include "DanceGameScene.h"
#include "Dancer.h"
#include "GameScene.h"
#include "SpriteResources.h"

extern GameScene* g_current_scene;

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

  render_bitmap(background_sprites[3 + data->state], main_dc, (Pos){0, 0},
                20.25);

  switch (data->state) {
    case STATE_COCO_DANCING:
    case STATE_DINGDING_DANCING: {
      DancerData* dancer_data = data->state == STATE_COCO_DANCING
                                    ? data->coco->data
                                    : data->dingding->data;
      DancerData* opponent_data = data->state == STATE_COCO_DANCING
                                      ? data->dingding->data
                                      : data->coco->data;

      if (dancer_data->dance_queue == NULL) {
        init_dance_queue(&dancer_data->dance_queue, 4);
        dancer_data->dance_max = 4;
        dancer_data->is_dancing = true;

        dancer_data->is_imitating = false;
        opponent_data->is_imitating = true;
      }

      if (is_dance_queue_full(dancer_data->dance_queue,
                              dancer_data->dance_max)) {
        deinit_dance_queue(&dancer_data->dance_queue);
        dancer_data->is_dancing = false;
        dancer_data->dance_max = 0;
        data->state = STATE_IMITATING;
      }
      break;
    }
    case STATE_IMITATING: {
      int note_count = scene_tag_count(g_current_scene, "dance_up") +
                       scene_tag_count(g_current_scene, "dance_right") +
                       scene_tag_count(g_current_scene, "dance_down") +
                       scene_tag_count(g_current_scene, "dance_left");
      if (note_count == 0) {
        DancerData* coco_data = data->coco->data;
        if (coco_data->is_imitating) {
          data->state = STATE_COCO_DANCING;
        } else {
          data->state = STATE_DINGDING_DANCING;
        }
      }
      break;
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
  coco->pos = (Pos){230, 335};
  insert_game_object(coco, scene);

  GameObject* dingding = create_dancer(false, dingding_keys);
  dingding->pos = (Pos){810, 335};
  insert_game_object(dingding, scene);

  DanceGameSceneData* data = malloc(sizeof(DanceGameSceneData));
  if (data == NULL) return NULL;
  data->coco = coco;
  data->dingding = dingding;
  data->state = STATE_DINGDING_DANCING;

  scene->data = data;
  scene->sleep_duration = 20;

  scene->on_render = on_render_dance_game_scene;
  return scene;
}