#include <stdio.h>

#include "Dancer.h"
#include "Delay.h"
#include "GameScene.h"
#include "KeyInput.h"
#include "SpriteResources.h"

extern GameScene* g_current_scene;

// �� ť�� ���̸� ���Ͽ� ��ȯ�մϴ�.
int dance_queue_length(DanceDirection* queue, int max) {
  if (queue == NULL) return 0;
  int i = 0;
  for (; queue[i] != DANCE_NONE && i < max; i++)
    ;
  return i;
}

// �� ť�� �� á���� �ƴ��� bool �������� ��ȯ�մϴ�.
bool is_dance_queue_full(DanceDirection* queue, int max) {
  return dance_queue_length(queue, max) == max;
}

// �� ť�� �� �����͸� �߰��մϴ�.
int dance_queue_push(DanceDirection* queue, int max, DanceDirection v) {
  int length = dance_queue_length(queue, max);
  if (length == max) return 1;

  queue[length] = v;
  return 0;
}

// ���� on_render �ݹ��Դϴ�. Ű �Է��� �ް� �׿� ���� ��������Ʈ��
// �����մϴ�.
void on_render_dancer(GameObject* dancer, HDC main_dc) {
  DancerData* data = (DancerData*)dancer->data;
  static DanceDirection directions[4] = {DANCE_UP, DANCE_RIGHT, DANCE_DOWN,
                                         DANCE_LEFT};
  static delay_t last_dance_delay;

  if (data->is_dancing) {
    HBITMAP dancer_sprite = dancer->sprites[dancer->sprite_index];
    BITMAP dancer_sprite_data;
    GetObject(dancer_sprite, sizeof(BITMAP), &dancer_sprite_data);

    double elapsed = elapsed_time(last_dance_delay);
    Pos progress_pos = (Pos){
        (LONG)(dancer->pos.x + dancer_sprite_data.bmWidth * 5.0 / 2.0 - 27),
        dancer->pos.y - 70};
    int current_index = (int)(10 * (elapsed / data->dance_cooldown));
    render_bitmap(progress_sprites[min(current_index, 10)], main_dc,
                  progress_pos, 3);
  }

  if ((elapsed_time(last_dance_delay) >= data->dance_cooldown &&
       data->is_dancing) ||
      data->is_imitating) {
    if (!is_dance_queue_full(data->dance_queue, data->dance_max)) {
      for (int i = 0; i < 4; i++) {
        if (is_pressed(data->move_keys[i])) {
          int length = dance_queue_length(data->dance_queue, data->dance_max);
          if (length > 0 && directions[i] == data->dance_queue[length - 1]) {
            continue;
          }
          dance_queue_push(data->dance_queue, data->dance_max, directions[i]);
          last_dance_delay = clock();
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

// ĳ���Ϳ� ����Ű�� �ް� ���� �����Ͽ� ��ȯ�մϴ�.
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
  data->dance_cooldown = 0.4;

  dancer->data = data;
  dancer->on_render = on_render_dancer;

  return dancer;
}
