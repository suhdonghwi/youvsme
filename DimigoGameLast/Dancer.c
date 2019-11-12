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

bool compare_tag_and_dir(DanceDirection dir, char* tag) {
  switch (dir) {
    case DANCE_UP:
      return strcmp(tag, "dance_up") == 0;
    case DANCE_RIGHT:
      return strcmp(tag, "dance_right") == 0;
    case DANCE_DOWN:
      return strcmp(tag, "dance_down") == 0;
    case DANCE_LEFT:
      return strcmp(tag, "dance_left") == 0;
  }

  return false;
}
void on_render_dancer(GameObject* dancer, HDC main_dc) {
  DancerData* data = (DancerData*)dancer->data;
  static DanceDirection directions[4] = {DANCE_UP, DANCE_RIGHT, DANCE_DOWN,
                                         DANCE_LEFT};

  if (data->is_dancing) {
    if (!is_dance_queue_full(data->dance_queue, data->dance_max)) {
      for (int i = 0; i < 4; i++) {
        clock_t current_clock = clock();
        if (is_pressed(data->move_keys[i])) {
          if (!data->is_imitating &&
              ((double)current_clock - data->last_dance_clock) /
                      CLOCKS_PER_SEC >
                  0.3) {
            dance_queue_push(data->dance_queue, data->dance_max, directions[i]);

            GameObject* note = create_dance_note(
                directions[i], dancer->sprites,
                dancer->sprites == dingding_sprites ? -10 : 10);
            note->pos = (Pos){dancer->pos.x, dancer->pos.y + 20};
            note->scale = 3;
            insert_game_object(note, g_current_scene);

            data->last_dance_clock = clock();
          }
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
  } else if (data->is_imitating) {
    for (int i = 0; i < 4; i++) {
      if (is_pressed(data->move_keys[i])) {
        if (data->colliding_note != NULL &&
            compare_tag_and_dir(directions[i], data->colliding_note->tag)) {
          data->colliding_note->alive = false;
        } else {
          dancer->pos.y -= 10;  // dance wrong
        }
      }
    }
  }

  data->colliding_note = NULL;
}

void on_collide_dancer(GameObject* dancer, GameObject* object) {
  static char* note_tags[] = {"dance_up", "dance_right", "dance_down",
                              "dance_left"};

  for (int i = 0; i < 4; i++) {
    if (strcmp(object->tag, note_tags[i]) == 0) {
      DancerData* data = dancer->data;
      data->colliding_note = object;
      return;
    }
  }
}

GameObject* create_dancer(bool coco, SHORT* move_keys) {
  GameObject* dancer = init_game_object(coco ? coco_sprites : dingding_sprites);

  dancer->scale = 10;
  dancer->collidable = true;

  DancerData* data = malloc(sizeof(DancerData));
  if (data == NULL) return NULL;
  data->move_keys = move_keys;
  data->dance_max = 0;
  data->dance_queue = NULL;
  data->is_dancing = false;
  data->is_imitating = false;
  data->last_dance_clock = clock();
  data->colliding_note = NULL;

  dancer->data = data;
  dancer->on_render = on_render_dancer;
  dancer->on_collide = on_collide_dancer;

  return dancer;
}
