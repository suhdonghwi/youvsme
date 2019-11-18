#include <stdio.h>

#include "DanceGameScene.h"
#include "Dancer.h"
#include "Delay.h"
#include "GameResultScene.h"
#include "GameScene.h"
#include "HomeScene.h"
#include "PullGameScene.h"
#include "SpriteResources.h"
#include "StoryScene.h"

extern GameScene* g_current_scene;
extern GameScene* g_new_scene;
extern HDC g_window_dc;
extern bool g_story_mode;
extern HFONT g_font_big;

// 댄스 큐와 사이즈를 받고 새로 초기화합니다.
void init_dance_queue(DanceDirection** queue, int size) {
  *queue = malloc(sizeof(DanceDirection) * size);
  if (*queue == NULL) return;

  for (int i = 0; i < size; i++) {
    (*queue)[i] = DANCE_NONE;
  }
}

// 사용이 완료된 댄스 큐의 메모리를 해제합니다.
void deinit_dance_queue(DanceDirection** queue) {
  free(*queue);
  *queue = NULL;
}

// 코코 쪽으로 화면을 확대합니다.
void zoom_coco(DanceGameSceneData* data) {
  data->background_scale = 50;
  data->background_pos = (Pos){0, -200};
  data->coco->scale = 25;
  data->coco->pos = (Pos){380, 325};
  data->coco->sprite_index = 0;
  data->dingding->scale = 0;
  data->dingding->sprite_index = 0;
}

// 딩딩 쪽으로 화면을 확대합니다.
void zoom_dingding(DanceGameSceneData* data) {
  data->background_scale = 50;
  data->background_pos = (Pos){-645, -200};
  data->coco->scale = 0;
  data->coco->sprite_index = 0;
  data->dingding->scale = 25;
  data->dingding->pos = (Pos){630, 325};
  data->dingding->sprite_index = 0;
}

// 확대된 화면을 초기화합니다.
void zoom_normal(DanceGameSceneData* data) {
  data->background_pos = (Pos){0, 0};
  data->background_scale = 20.25;
  data->coco->pos = (Pos){230, 335};
  data->coco->scale = 10;
  data->dingding->pos = (Pos){810, 335};
  data->dingding->scale = 10;
}

// 댄스 게임의 on_render 콜백입니다. 춤을 추고 있는 상태있지, 따라하고 있는
// 상태인지 조절하고 턴 횟수에 따라서 스피드업을 해줍니다.
void on_render_dance_game_scene(GameScene* scene, HDC main_dc) {
  DanceGameSceneData* data = (DanceGameSceneData*)scene->data;
  DancerData* coco_data = data->coco->data;
  DancerData* dingding_data = data->dingding->data;

  render_bitmap(background_sprites[3 + data->state], main_dc,
                data->background_pos, data->background_scale);

  if (data->dance_count == 3 || data->dance_count == 6) {
    if (data->speedup_show_delay == 0) data->speedup_show_delay = clock();
    if (after_delay(&data->speedup_blink_delay, 0.5)) {
      data->show_speed_up = !data->show_speed_up;
    }

    if (data->show_speed_up && elapsed_time(data->speedup_show_delay) < 3.0) {
      SelectObject(main_dc, g_font_big);
      SetTextColor(main_dc, RGB(255, 212, 59));
      TextOut(main_dc, 450, 100, "Speed Up!", strlen("Speed Up!"));
    }
  }

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
        data->to_imiate_queue = dancer_data->dance_queue;
        dancer_data->dance_queue = NULL;
        dancer_data->is_dancing = false;
        dancer_data->dance_max = 0;

        opponent_data->is_imitating = true;

        data->state = STATE_IMITATING;
        Sleep(700);
        data->imitate_clock = clock();
        zoom_normal(data);
      }
      break;
    }
    case STATE_IMITATING: {
      DancerData* imitator_data =
          coco_data->is_imitating ? coco_data : dingding_data;

      int imitating_length = dance_queue_length(imitator_data->dance_queue,
                                                imitator_data->dance_max);

      char remain_str[100];
      clock_t current_clock = clock();
      double elapsed =
          ((double)current_clock - data->imitate_clock) / CLOCKS_PER_SEC;
      sprintf(remain_str, "%.1lf초 남음", data->imitate_time - elapsed);

      SelectObject(main_dc, g_font_big);
      SetTextColor(main_dc, RGB(200, 200, 200));
      TextOut(main_dc, 420, 150, remain_str, strlen(remain_str));

      if ((data->previous_length < imitating_length &&
           imitator_data->dance_queue[imitating_length - 1] !=
               data->to_imiate_queue[imitating_length - 1]) ||
          data->imitate_time - elapsed <= 0.00003) {
        render_bitmap(
            sign_sprites[1], g_window_dc,
            coco_data->is_imitating ? data->coco->pos : data->dingding->pos,
            25);
        Sleep(1500);

        bool coco_win = !coco_data->is_imitating;
        if (g_story_mode)
          g_new_scene = create_after_dance_story(coco_win);
        else
          g_new_scene = create_game_result_scene(coco_win, create_home_scene());
        return;
      }

      if (imitator_data->dance_queue == NULL) {
        init_dance_queue(&imitator_data->dance_queue, 4);
        imitator_data->dance_max = 4;
        imitator_data->is_imitating = true;
      } else if (is_dance_queue_full(imitator_data->dance_queue,
                                     imitator_data->dance_max)) {
        data->dance_count++;

        if (data->dance_count == 3) {
          coco_data->dance_cooldown -= 0.1;
          dingding_data->dance_cooldown -= 0.1;
          data->imitate_time -= 2;
        } else if (data->dance_count == 6) {
          coco_data->dance_cooldown -= 0.05;
          dingding_data->dance_cooldown -= 0.05;
          data->imitate_time -= 1.5;
        }

        data->speedup_show_delay = clock();

        if (coco_data->is_imitating) {
          data->state = STATE_COCO_DANCING;
          zoom_coco(data);
        } else {
          data->state = STATE_DINGDING_DANCING;
          zoom_dingding(data);
        }

        deinit_dance_queue(&imitator_data->dance_queue);
        deinit_dance_queue(&data->to_imiate_queue);
        imitator_data->is_imitating = false;
        imitator_data->dance_max = 0;
        data->previous_length = 0;
      }
      data->previous_length = imitating_length;

      break;
    }
  }
}

// 댄스 화면의 on_first_render 콜백입니다. 배경 음악을 재생합니다.
void on_first_render_dance_game_scene(GameScene* scene, HDC main_dc) {
  PlaySound(TEXT("Sound/radioactive.wav"), NULL,
            SND_FILENAME | SND_ASYNC | SND_LOOP);
}

// 댄스 화면을 생성하고 반환합니다.
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
  data->previous_length = 0;
  data->imitate_time = 5;
  data->dance_count = 0;
  data->speedup_show_delay = 0;
  data->speedup_blink_delay = 0;
  data->show_speed_up = false;
  zoom_dingding(data);

  scene->data = data;
  scene->sleep_duration = 20;

  scene->on_render = on_render_dance_game_scene;
  scene->on_first_render = on_first_render_dance_game_scene;
  return scene;
}