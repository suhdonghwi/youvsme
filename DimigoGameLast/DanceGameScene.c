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

void zoom_coco(DanceGameSceneData* data) {
  data->background_scale = 50;
  data->background_pos = (Pos){0, -200};
  data->coco->scale = 25;
  data->coco->pos = (Pos){380, 325};
  data->coco->sprite_index = 0;
  data->dingding->scale = 0;
}

void zoom_dingding(DanceGameSceneData* data) {
  data->background_scale = 50;
  data->background_pos = (Pos){-645, -200};
  data->coco->scale = 0;
  data->dingding->scale = 25;
  data->dingding->pos = (Pos){630, 325};
  data->dingding->sprite_index = 0;
}

void zoom_normal(DanceGameSceneData* data) {
  data->background_pos = (Pos){0, 0};
  data->background_scale = 20.25;
  data->coco->pos = (Pos){230, 335};
  data->coco->scale = 10;
  data->dingding->pos = (Pos){810, 335};
  data->dingding->scale = 10;
}

void on_render_dance_game_scene(GameScene* scene, HDC main_dc) {
  DanceGameSceneData* data = (DanceGameSceneData*)scene->data;

  render_bitmap(background_sprites[3 + data->state], main_dc,
                data->background_pos, data->background_scale);

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
      }

      if (is_dance_queue_full(dancer_data->dance_queue,
                              dancer_data->dance_max)) {
        deinit_dance_queue(&dancer_data->dance_queue);
        dancer_data->is_dancing = false;
        opponent_data->is_imitating = true;
        dancer_data->dance_max = 0;
        data->state = STATE_IMITATING;
        zoom_normal(data);
      }
      break;
    }
    case STATE_IMITATING: {
      DancerData* coco_data = data->coco->data;
      DancerData* imitator_data =
          coco_data->is_imitating ? coco_data : data->dingding->data;

      if (imitator_data->dance_queue == NULL) {
        init_dance_queue(&imitator_data->dance_queue, 4);
        imitator_data->dance_max = 4;
        imitator_data->is_imitating = true;
      }

      if (is_dance_queue_full(imitator_data->dance_queue,
                              imitator_data->dance_max)) {
        if (coco_data->is_imitating) {
          data->state = STATE_COCO_DANCING;
          Sleep(300);
          zoom_coco(data);
        } else {
          data->state = STATE_DINGDING_DANCING;
          Sleep(300);
          zoom_dingding(data);
        }

        deinit_dance_queue(&imitator_data->dance_queue);
        imitator_data->is_imitating = false;
        imitator_data->dance_max = 0;
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
  insert_game_object(coco, scene);

  GameObject* dingding = create_dancer(false, dingding_keys);
  insert_game_object(dingding, scene);

  DanceGameSceneData* data = malloc(sizeof(DanceGameSceneData));
  if (data == NULL) return NULL;
  data->coco = coco;
  data->dingding = dingding;
  data->state = STATE_DINGDING_DANCING;
  zoom_dingding(data);

  scene->data = data;
  scene->sleep_duration = 20;

  scene->on_render = on_render_dance_game_scene;
  return scene;
}