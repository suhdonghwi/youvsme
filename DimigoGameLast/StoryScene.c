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

// 스토리 화면의 on_render 콜백입니다. 말풍선의 대사가 끝나면 설정된 다음
// 화면으로 넘어갑니다.
void on_render_story_scene(GameScene* scene, HDC main_dc) {
  StorySceneData* data = scene->data;

  render_bitmap(data->background, main_dc, (Pos){0, 0}, 1.26);

  if (strcmp(data->speech->tag, "speech_end") == 0) {
    g_new_scene = data->next_scene;
  }
}

// 스토리 화면의 on_first_render 콜백입니다. 배경 음악이 설정되어있으면 이를
// 재생합니다.
void on_first_render_story_scene(GameScene* scene, HDC main_dc) {
  StorySceneData* data = scene->data;

  if (data->sound_filename != NULL) {
    PlaySound(TEXT(data->sound_filename), NULL,
              SND_FILENAME | SND_ASYNC | SND_LOOP);
  }
}

// 다음 화면, 배경 사진, 대사, 대사의 개수, 말풍선의 위치와 크기를 담은 RECT
// 데이터, 배경 음악의 경로를 받고 스토리 화면을 생성하여 반환합니다.
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

// 홈 화면 뒤의 스토리를 생성하여 반환합니다.
GameScene* create_after_main_story() {
  GameScene* disk_help = create_disk_help_scene();

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
         L"멀리 날려야 좋은 점수를 받을테니 폐활량을 키워오는게 좋을거다.");

  GameScene* teacher_help = create_story_scene(disk_help, teacher_sprites[0],
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

// 플라잉 디스크 게임 뒤의 스토리를 생성하여 반환합니다.
GameScene* create_after_disk_story(bool coco_win) {
  RECT rect;
  GameScene* pull_help = create_pull_help_scene();

  CREATE_MENT(teacher_ment, 4, NULL);

  wcscpy(teacher_ment[0], L"자, 이번엔 줄다리기다!");
  wcscpy(teacher_ment[1], L"잘못하면 다칠 수 있으니까 정신 똑바로 차리고.");
  wcscpy(
      teacher_ment[2],
      L"자신의 머리 위에 떠있는 키를 차례대로 누르면 줄을 당길 수 있게된다.");
  wcscpy(teacher_ment[3], L"먼저 깃발을 잡으면 이기니까 최대한 빠르게 당겨라!");

  rect.top = 50;
  rect.left = 680;
  rect.bottom = 300;
  rect.right = 1050;

  GameScene* teacher_help = create_story_scene(pull_help, teacher_sprites[1],
                                               teacher_ment, 4, rect, NULL);

  CREATE_MENT(ment, 3, NULL);
  wcscpy(ment[0], coco_win ? L"코코 : 풋, 내가 이겼네? ㅋ"
                           : L"딩딩 : 풋, 내가 이겼네? ㅋ");
  wcscpy(ment[1],
         coco_win ? L"코코 : 잘 좀 해봐~ 그렇게 해서 나 이길 수 있겠어? ㅋ"
                  : L"딩딩 : 잘 좀 해봐~ 그렇게 해서 나 이길 수 있겠어? ㅋ");
  wcscpy(ment[2], coco_win ? L"딩딩 : 다음 판에는 내가 이길테니까 두고봐..!"
                           : L"코코 : ㅠㅠ 다음 번에는 내가 꼭 이긴다..");

  rect.top = 450;
  rect.left = 200;
  rect.bottom = rect.top + 200;
  rect.right = rect.left + 750;

  GameScene* next_scene =
      create_story_scene(teacher_help, story_sprites[coco_win ? 6 : 7], ment, 3,
                         rect, "Sound/avengers.wav");

  return create_game_result_scene(coco_win, next_scene);
}

// 줄다리기 게임 뒤의 스토리를 생성하여 반환합니다.
GameScene* create_after_pull_story(bool coco_win) {
  RECT rect;
  GameScene* dance_help = create_dance_help_scene();

  CREATE_MENT(teacher_ment, 4, NULL);

  wcscpy(teacher_ment[0], L"마지막으로 댄스 수업이다!");
  wcscpy(teacher_ment[1], L"방향키 혹은 W, A, S, D키로 춤을 출 수가 있다.");
  wcscpy(teacher_ment[2],
         L"자신에게 스포트라이트가 오면 춤을 추고, 상대편은 그걸 따라서 추면 "
         L"된다.");
  wcscpy(teacher_ment[3],
         L"잘못 따라추면 바로 탈락이고, 갈수록 진행이 빨라지니까 집중해라!");

  rect.top = 50;
  rect.left = 680;
  rect.bottom = 300;
  rect.right = 1050;

  GameScene* teacher_help = create_story_scene(dance_help, teacher_sprites[2],
                                               teacher_ment, 4, rect, NULL);

  CREATE_MENT(ment, 3, NULL);

  if (g_coco_score == 0) {
    wcscpy(ment[0],
           coco_win
               ? L"코코 : 내가 분명히 말했지? 내가 이.긴.다.고 ㅋ"
               : L"딩딩 : 이번에도 내가 이겼네? ㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋ");
    wcscpy(
        ment[1],
        coco_win
            ? L"딩딩 : 고작 한 번 이겼다고 자만하다니.. 억울해 ㅠㅠ!!"
            : L"딩딩 : 너가 이긴다고 하지 않았니? 하여간 입만 살아가지고 ㅋ");
    wcscpy(ment[2],
           coco_win
               ? L"딩딩 : 하지만 마지막 게임의 승리는.. 나의 것이다.. 두고봐!!"
               : L"코코 : 이미 진 판이지만..끝까지 최선을 다하겠어... 내 "
                 L"자신아 ! 조금만 더 힘을 내줘!!");
  } else {
    wcscpy(ment[0],
           !coco_win
               ? L"딩딩 : 내가 분명히 말했지? 내가 이.긴.다.고 ㅋ"
               : L"코코 : 이번에도 내가 이겼네? ㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋ");
    wcscpy(
        ment[1],
        !coco_win
            ? L"코코 : 고작 한 번 이겼다고 자만하다니.. 억울해 ㅠㅠ!!"
            : L"코코 : 너가 이긴다고 하지 않았니? 하여간 입만 살아가지고 ㅋ");
    wcscpy(ment[2],
           !coco_win
               ? L"코코 : 하지만 마지막 게임의 승리는.. 나의 것이다.. 두고봐!!"
               : L"딩딩 : 이미 진 판이지만..끝까지 최선을 다하겠어... 내 "
                 L"자신아 ! 조금만 더 힘을 내줘!!");
  }

  rect.top = 450;
  rect.left = 200;
  rect.bottom = rect.top + 200;
  rect.right = rect.left + 750;

  GameScene* next_scene =
      create_story_scene(teacher_help, story_sprites[coco_win ? 2 : 3], ment, 3,
                         rect, "Sound/avengers.wav");
  return create_game_result_scene(coco_win, next_scene);
}

// 댄스 게임 뒤의 스토리를 생성하여 반환합니다.
GameScene* create_after_dance_story(bool coco_win) {
  int coco_score = g_coco_score;
  if (coco_win) coco_score++;
  bool final_result = coco_score > g_dingding_score;

  update_set_score(final_result);
  CREATE_MENT(final_ment, 3, NULL);

  wcscpy(final_ment[0],
         !final_result ? L"코코 : 이게.. 진짜 일리 없어.. 내가.. 지다니..."
                       : L"딩딩 : 이게.. 진짜 일리 없어.. 내가.. 지다니...");
  wcscpy(final_ment[1],
         !final_result
             ? L"코코 : 청소 진짜 힘들다.. 그래도 열심히 해야지 아자아자!"
             : L"딩딩 : 청소 진짜 힘들다.. 그래도 열심히 해야지 아자아자!");
  wcscpy(final_ment[2], !final_result
                            ? L"코코 : 내 자신아...졌지만..잘 싸웠다!"
                            : L"딩딩 : 내 자신아...졌지만..잘 싸웠다!");

  RECT rect;
  rect.top = 120;
  rect.left = 200;
  rect.bottom = rect.top + 200;
  rect.right = rect.left + 750;

  GameScene* clean_scene = create_story_scene(
      create_final_result_scene(), story_sprites[final_result ? 5 : 4],
      final_ment, 3, rect, "Sound/game_over.wav");

  CREATE_MENT(ment, 2, NULL);

  wcscpy(ment[0], final_result ? L"코코 : 결국 마지막엔 내가 이겼네?"
                               : L"딩딩 : 결국 마지막엔 내가 이겼네?");
  wcscpy(ment[1], final_result
                      ? L"코코 : 이긴다고 막 그러더니.. 내가 까불지 말랬지?"
                      : L"딩딩 : 이긴다고 막 그러더니.. 내가 까불지 말랬지?");

  rect.top = 170;
  rect.left = final_result ? 350 : 450;
  rect.bottom = rect.top + 200;
  rect.right = rect.left + 350;
  GameScene* next_scene = create_story_scene(
      clean_scene, story_sprites[final_result ? 8 : 9], ment, 2, rect, NULL);

  return create_game_result_scene(coco_win, next_scene);
}
