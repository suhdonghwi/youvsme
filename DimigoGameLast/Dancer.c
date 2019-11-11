#include "Dancer.h"
#include "DanceNote.h"
#include "GameScene.h"
#include "KeyInput.h"
#include "SpriteResources.h"

extern GameScene* g_current_scene;

int dance_queue_length(DanceDirection* queue, int max) {
  if (queue == NULL) return 0;
  int i = 0;
  for (; queue[i] != DANCE_NONE && i < max; i++)
    ;
  return i;
}

bool is_dance_queue_full(DanceDirection* queue, int max) {
  return dance_queue_length(queue, max) == max;
}

void dance_queue_push(DanceDirection* queue, int max, DanceDirection v) {
  int length = dance_queue_length(queue, max);
  if (length == max) return;

  queue[length] = v;
}

void on_render_dancer(GameObject* dancer, HDC main_dc) {
  DancerData* data = (DancerData*)dancer->data;

  if (data->is_dancing) {
    if (!is_dance_queue_full(data->dance_queue, data->dance_max)) {
      static DanceDirection directions[4] = {DANCE_UP, DANCE_RIGHT, DANCE_DOWN,
                                             DANCE_LEFT};

      for (int i = 0; i < 4; i++) {
        if (is_pressed(data->move_keys[i])) {
          dance_queue_push(data->dance_queue, data->dance_max, directions[i]);

          GameObject* note =
              create_dance_note(directions[i], dancer->sprites,
                                dancer->sprites == dingding_sprites ? -2 : 2);
          note->pos = (Pos){dancer->pos.x, dancer->pos.y + 20};
          note->scale = 3;
          insert_game_object(note, g_current_scene);
        }
      }
    }

    int queue_length = dance_queue_length(data->dance_queue, data->dance_max);
    if (queue_length != 0) {
      DanceDirection dir = data->dance_queue[queue_length - 1];
      if (dir != DANCE_NONE) {
        dancer->sprite_index = 4 + dir;
      }
    }
  }
}

GameObject* create_dancer(bool coco, SHORT* move_keys) {
  GameObject* dancer = init_game_object(coco ? coco_sprites : dingding_sprites);

  dancer->scale = 7;

  DancerData* data = malloc(sizeof(DancerData));
  if (data == NULL) return NULL;
  data->move_keys = move_keys;
  data->dance_max = 0;
  data->dance_queue = NULL;
  data->is_dancing = false;

  dancer->data = data;
  dancer->on_render = on_render_dancer;
  return dancer;
}
