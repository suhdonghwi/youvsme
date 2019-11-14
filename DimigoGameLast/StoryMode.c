#include "StoryMode.h"

#include "DiskGameScene.h"
#include "GameHelpScene.h"
#include "ReadyStartScene.h"
#include "SpriteResources.h"
#include "StoryScene.h"

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

  CREATE_MENT(teacher_ment, 4, NULL);

  wcscpy(teacher_ment[0], L"��, ����!");
  wcscpy(teacher_ment[1], L"���� �츮�� �ö��� ��ũ�� ���Ŵ�.");
  wcscpy(teacher_ment[2],
         L"�ö��� ��ũ�� ����ũ�� �ٶ��� ��� �Ҹ� ���󰡰� �Ǿ��ִ�.");
  wcscpy(teacher_ment[3],
         L"�ָ� ������ ���� ������ �����״� ���� ũ�� ���̽����.");

  GameScene* teacher_help = create_story_scene(disk_help, game_help_sprites[2],
                                               teacher_ment, 4, rect);

  rect.top = 500;
  rect.left = 300;
  rect.bottom = rect.top + 140;
  rect.right = rect.left + 500;

  CREATE_MENT(timetable_ment, 2, NULL);
  wcscpy(timetable_ment[0], L"���̵� : (��������)");
  wcscpy(timetable_ment[1], L"���̵� : �� ���� ü�� 3�ð��̴�! ���� ����!");

  GameScene* timetable_story = create_story_scene(
      teacher_help, story_sprites[0], timetable_ment, 2, rect);

  rect.top = 450;
  rect.left = 200;
  rect.bottom = rect.top + 200;
  rect.right = rect.left + 750;

  CREATE_MENT(first_ment, 4, NULL);
  wcscpy(first_ment[0],
         L"���ڿ� �����̴� �̹��ֿ� �ݿ��� ����� ���� ó���ϴ� �ֹ��� "
         L"�Ǿ����ϴ�. ");
  wcscpy(first_ment[1], L"�׸��� ��ħ��, ������ '�ݿ�Ͱ�'�� �ϴ� ���Դϴ�.");
  wcscpy(first_ment[2],
         L"���ڿ� �����̴� ���� ������ �ؼ� �� ����� ���Ƽ� û�Ҹ� �ϰ� "
         L"����� �߽��ϴ�.");
  wcscpy(first_ment[3], L"���� ���� �̱�� �ɱ��?");

  GameScene* first_help = create_story_scene(timetable_story, story_sprites[1],
                                             first_ment, 4, rect);

  return first_help;
}
