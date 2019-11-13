#include <stdio.h>

#include "Dancer.h"
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

int dance_queue_push(DanceDirection* queue, int max, DanceDirection v) {
  int length = dance_queue_length(queue, max);
  if (length == max) return 1;
  if (length > 0 && queue[length - 1] == v) return 1;

  queue[length] = v;
  return 0;
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

  clock_t current_clock = clock();
  if (data->is_dancing) {
    HBITMAP dancer_sprite = dancer->sprites[dancer->sprite_index];
    BITMAP dancer_sprite_data;
    GetObject(dancer_sprite, sizeof(BITMAP), &dancer_sprite_data);

    RECT bar_rect;
    bar_rect.top = dancer->pos.y - 30;
    bar_rect.left = dancer->pos.x + dancer_sprite_data.bmWidth * 5.0 / 2.0 - 50;
    bar_rect.bottom = bar_rect.top + 15;
    bar_rect.right = bar_rect.left + 100;
    FillRect(main_dc, &bar_rect, data->bar_brush);

    double elapsed =
        ((double)current_clock - data->last_dance_clock) / CLOCKS_PER_SEC;
    bar_rect.right = bar_rect.left + 100 * min(elapsed / 0.3, 1);
    FillRect(main_dc, &bar_rect, data->fill_brush);
  }

  if ((((double)current_clock - data->last_dance_clock) / CLOCKS_PER_SEC >
           0.2 &&
       data->is_dancing) ||
      data->is_imitating) {
    if (!is_dance_queue_full(data->dance_queue, data->dance_max)) {
      for (int i = 0; i < 4; i++) {
        if (is_pressed(data->move_keys[i])) {
          if (dance_queue_push(data->dance_queue, data->dance_max,
                               directions[i]) == 0)
            data->last_dance_clock = clock();
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

void on_destroy_dancer(GameObject* dancer) {
  DancerData* data = dancer->data;
  DeleteObject(data->bar_brush);
  DeleteObject(data->fill_brush);
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

  data->bar_brush = CreateSolidBrush(RGB(50, 50, 50));
  data->fill_brush = CreateSolidBrush(RGB(0, 150, 0));

  dancer->data = data;
  dancer->on_render = on_render_dancer;

  return dancer;
}
