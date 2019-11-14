#include "StoryMode.h"

#include "DiskGameScene.h"
#include "GameHelpScene.h"
#include "ReadyStartScene.h"
#include "SpriteResources.h"
#include "StoryScene.h"

#define CREATE_MENT(var, size)                     \
  wchar_t** var = malloc(sizeof(wchar_t*) * size); \
  if (var == NULL) return NULL;                    \
  for (int i = 0; i < size; i++) {                 \
    var[i] = malloc(sizeof(wchar_t) * 100);        \
    if (var[i] == NULL) return NULL;               \
  }

GameScene* create_story_mode() {
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

  CREATE_MENT(teacher_ment, 4);

  wcscpy(teacher_ment[0], L"자, 집중!");
  wcscpy(teacher_ment[1], L"이제 우리는 플라잉 디스크를 배울거다.");
  wcscpy(teacher_ment[2],
         L"플라잉 디스크는 마이크에 바람을 대고 불면 날라가게 되어있다.");
  wcscpy(teacher_ment[3],
         L"멀리 날려야 좋은 점수를 받을테니 숨을 크게 들이쉬어라.");

  GameScene* teacher_help = create_story_scene(disk_help, game_help_sprites[2],
                                               teacher_ment, 4, rect);

  rect.top = 500;
  rect.left = 300;
  rect.bottom = rect.top + 140;
  rect.right = rect.left + 500;

  CREATE_MENT(timetable_ment, 2);
  wcscpy(timetable_ment[0], L"아이들 : (웅성웅성)");
  wcscpy(timetable_ment[1], L"아이들 : 와 오늘 체육 3시간이다! 빨리 가자!");

  GameScene* timetable_story = create_story_scene(
      teacher_help, story_sprites[0], timetable_ment, 2, rect);

  rect.top = 450;
  rect.left = 200;
  rect.bottom = rect.top + 200;
  rect.right = rect.left + 750;

  CREATE_MENT(first_ment, 4);
  wcscpy(first_ment[0],
         L"코코와 딩딩이는 이번주에 반에서 잡다한 일을 처리하는 주번이 "
         L"되었습니다. ");
  wcscpy(first_ment[1], L"그리고 마침내, 오늘은 '금요귀가'를 하는 날입니다.");
  wcscpy(first_ment[2],
         L"코코와 딩딩이는 오늘 게임을 해서 진 사람이 남아서 청소를 하고 "
         L"가기로 했습니다.");
  wcscpy(first_ment[3], L"과연 누가 이기게 될까요?");

  GameScene* first_help = create_story_scene(timetable_story, story_sprites[1],
                                             first_ment, 4, rect);

  return first_help;
}
