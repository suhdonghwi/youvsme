#include "StoryScene.h"
#include "DanceGameScene.h"
#include "DiskGameScene.h"
#include "FinalResultScene.h"
#include "GameHelpScene.h"
#include "GameResultScene.h"
#include "PullGameScene.h"
#include "ReadyStartScene.h"
#include "SetScore.h"
#include "Speech.h"
#include "SpriteResources.h"
#include "StoryScene.h"

extern GameScene* g_new_scene;
extern int g_coco_score;
extern int g_dingding_score;

void on_render_story_scene(GameScene* scene, HDC main_dc) {
  StorySceneData* data = scene->data;

  render_bitmap(data->background, main_dc, (Pos){0, 0}, 1.26);

  if (strcmp(data->speech->tag, "speech_end") == 0) {
    g_new_scene = data->next_scene;
  }
}

void on_first_render_story_scene(GameScene* scene, HDC main_dc) {
  StorySceneData* data = scene->data;

  if (data->sound_filename != NULL) {
    PlaySound(TEXT(data->sound_filename), NULL,
              SND_FILENAME | SND_ASYNC | SND_LOOP);
  }
}

GameScene* create_story_scene(GameScene* next_scene, HBITMAP background,
                              wchar_t** text, int text_count, RECT text_rect,
                              char* sound) {
  GameScene* scene = init_scene();
  scene->on_render = on_render_story_scene;
  scene->on_first_render = on_first_render_story_scene;

  GameObject* speech = create_speech(text, text_count, text_rect);
  insert_game_object(speech, scene);

  StorySceneData* data = malloc(sizeof(StorySceneData));
  if (data == NULL) return NULL;
  data->background = background;
  data->speech = speech;
  data->next_scene = next_scene;
  data->sound_filename = sound;

  scene->data = data;

  return scene;
}

GameScene* create_after_main_story() {
  GameScene* disk_ready =
      create_readystart_scene(create_disk_game_scene(true, (Pos){0, 0}),
                              coco_disk_ready_sprites, 3, (Pos){560, 300});

  GameScene* disk_help =
      create_game_help_scene(game_help_sprites[0], logo_sprites[0], disk_ready);

  RECT rect;
  rect.top = 50;
  rect.left = 680;
  rect.bottom = 300;
  rect.right = 1050;

  CREATE_MENT(teacher_ment, 4, NULL);

  wcscpy(teacher_ment[0], L"자, 집중!");
  wcscpy(teacher_ment[1], L"이제 우리는 플라잉 디스크를 배울거다.");
  wcscpy(teacher_ment[2],
         L"플라잉 디스크는 마이크에 바람을 대고 불면 날라가게 되어있다.");
  wcscpy(teacher_ment[3],
         L"멀리 날려야 좋은 점수를 받을테니 숨을 크게 들이쉬어라.");

  GameScene* teacher_help = create_story_scene(disk_help, game_help_sprites[2],
                                               teacher_ment, 4, rect, NULL);

  rect.top = 500;
  rect.left = 300;
  rect.bottom = rect.top + 140;
  rect.right = rect.left + 500;

  CREATE_MENT(timetable_ment, 2, NULL);
  wcscpy(timetable_ment[0], L"아이들 : (웅성웅성)");
  wcscpy(timetable_ment[1], L"아이들 : 와 오늘 체육 3시간이다! 빨리 가자!");

  GameScene* timetable_story = create_story_scene(
      teacher_help, story_sprites[0], timetable_ment, 2, rect, NULL);

  rect.top = 450;
  rect.left = 200;
  rect.bottom = rect.top + 200;
  rect.right = rect.left + 750;

  CREATE_MENT(first_ment, 4, NULL);
  wcscpy(first_ment[0],
         L"코코와 딩딩이는 이번주에 반에서 잡다한 일을 처리하는 주번이 "
         L"되었습니다. ");
  wcscpy(first_ment[1], L"그리고 마침내, 오늘은 '금요귀가'를 하는 날입니다.");
  wcscpy(first_ment[2],
         L"코코와 딩딩이는 오늘 게임을 해서 진 사람이 남아서 청소를 하고 "
         L"가기로 했습니다.");
  wcscpy(first_ment[3], L"과연 누가 이기게 될까요?");

  GameScene* first_help =
      create_story_scene(timetable_story, story_sprites[1], first_ment, 4, rect,
                         "Sound/story_begin.wav");

  return first_help;
}

GameScene* create_after_disk_story(bool coco_win) {
  CREATE_MENT(ment, 2, NULL);
  wcscpy(ment[0],
         coco_win ? L"코코 : 풋, 내가 이겼네?" : L"딩딩 : 풋, 내가 이겼네?");
  wcscpy(ment[1], coco_win ? L"딩딩 : 다음 판에는 내가 이길테니까 두고봐..!"
                           : L"코코 : 다음 판에는 내가 꼭 이긴다.. 긴장해라!");

  RECT rect;
  rect.top = 450;
  rect.left = 200;
  rect.bottom = rect.top + 200;
  rect.right = rect.left + 750;

  GameScene* pull_ready = create_readystart_scene(
      create_pull_game_scene(), ready_start_sprites, 2, (Pos){560, 300});

  GameScene* pull_help =
      create_game_help_scene(game_help_sprites[1], logo_sprites[1], pull_ready);

  GameScene* next_scene =
      create_story_scene(pull_help, story_sprites[coco_win ? 2 : 3], ment, 2,
                         rect, "Sound/avengers.wav");

  return create_game_result_scene(coco_win, next_scene);
}

GameScene* create_after_pull_story(bool coco_win) {
  CREATE_MENT(ment, 3, NULL);

  if (g_coco_score == 0) {
    wcscpy(ment[0], coco_win ? L"코코 : 내가 분명히 말했지? 이번엔 내가 이겼네?"
                             : L"딩딩 : 이번에도 내가 이겼네? 이번엔 너가 "
                               L"이긴다고 하지 않았니?");
    wcscpy(ment[1],
           coco_win ? L"딩딩 : 이제 마지막 게임이다.. 마지막엔 내가 이기겠어!"
                    : L"코코 : 이미 진 판이지만.. 끝까지 최선을 다하겠어!");
  } else {
    wcscpy(ment[0], !coco_win
                        ? L"딩딩 : 내가 분명히 말했지? 이번엔 내가 이겼네?"
                        : L"코코 : 이번에도 내가 이겼네? 이번엔 너가 "
                          L"이긴다고 하지 않았니?");
    wcscpy(ment[1],
           !coco_win ? L"코코 : 이제 마지막 게임이다.. 마지막엔 내가 이기겠어!"
                     : L"딩딩 : 이미 진 판이지만.. 끝까지 최선을 다하겠어!");
  }

  RECT rect;
  rect.top = 450;
  rect.left = 200;
  rect.bottom = rect.top + 200;
  rect.right = rect.left + 750;

  GameScene* dance_ready = create_readystart_scene(
      create_dance_game_scene(), ready_start_sprites, 2, (Pos){560, 300});

  GameScene* dance_help = create_game_help_scene(game_help_sprites[3],
                                                 logo_sprites[2], dance_ready);

  GameScene* next_scene =
      create_story_scene(dance_help, story_sprites[coco_win ? 2 : 3], ment, 2,
                         rect, "Sound/avengers.wav");
  return create_game_result_scene(coco_win, next_scene);
}

GameScene* create_after_dance_story(bool coco_win) {
  CREATE_MENT(ment, 4, NULL);

  bool final_result;
  final_result = coco_win && g_coco_score + 1 > g_dingding_score;
  update_set_score(final_result);

  wcscpy(ment[0], !final_result
                      ? L"코코 : 이게 진짜일리 없어.. 내가 지다니 ㅠㅠ"
                      : L"딩딩 : 이게 진짜일리 없어.. 내가 지다니 ㅠㅠ");
  wcscpy(ment[1], !final_result
                      ? L"코코 : 청소 진짜 힘들다 .. 집 가고 싶다 ㅠㅠ"
                      : L"딩딩 : 청소 진짜 힘들다.. 집 가고 싶어 ㅠㅠ");
  wcscpy(ment[2], !final_result
                      ? L"코코 : 그래도.. 열심히 해야지!"
                      : L"딩딩 : 그래도.. 내게 주어진 임무는 열심히 해야지.. ");
  wcscpy(ment[3], !final_result ? L"코코 : 내 자신아 ... 졌지만... 잘 싸웠다!"
                                : L"딩딩 : 내 자신아 ... 졌지만... 잘 싸웠다!");

  RECT rect;
  rect.top = 450;
  rect.left = 200;
  rect.bottom = rect.top + 200;
  rect.right = rect.left + 750;

  GameScene* next_scene =
      create_story_scene(create_final_result_scene(),
                         story_sprites[coco_win ? 5 : 4], ment, 4, rect, NULL);
  return create_game_result_scene(coco_win, next_scene);
}
