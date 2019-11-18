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

// ���丮 ȭ���� on_render �ݹ��Դϴ�. ��ǳ���� ��簡 ������ ������ ����
// ȭ������ �Ѿ�ϴ�.
void on_render_story_scene(GameScene* scene, HDC main_dc) {
  StorySceneData* data = scene->data;

  render_bitmap(data->background, main_dc, (Pos){0, 0}, 1.26);

  if (strcmp(data->speech->tag, "speech_end") == 0) {
    g_new_scene = data->next_scene;
  }
}

// ���丮 ȭ���� on_first_render �ݹ��Դϴ�. ��� ������ �����Ǿ������� �̸�
// ����մϴ�.
void on_first_render_story_scene(GameScene* scene, HDC main_dc) {
  StorySceneData* data = scene->data;

  if (data->sound_filename != NULL) {
    PlaySound(TEXT(data->sound_filename), NULL,
              SND_FILENAME | SND_ASYNC | SND_LOOP);
  }
}

// ���� ȭ��, ��� ����, ���, ����� ����, ��ǳ���� ��ġ�� ũ�⸦ ���� RECT
// ������, ��� ������ ��θ� �ް� ���丮 ȭ���� �����Ͽ� ��ȯ�մϴ�.
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

// Ȩ ȭ�� ���� ���丮�� �����Ͽ� ��ȯ�մϴ�.
GameScene* create_after_main_story() {
  GameScene* disk_help = create_disk_help_scene();

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
         L"�ָ� ������ ���� ������ �����״� ��Ȱ���� Ű�����°� �����Ŵ�.");

  GameScene* teacher_help = create_story_scene(disk_help, teacher_sprites[0],
                                               teacher_ment, 4, rect, NULL);

  rect.top = 500;
  rect.left = 300;
  rect.bottom = rect.top + 140;
  rect.right = rect.left + 500;

  CREATE_MENT(timetable_ment, 2, NULL);
  wcscpy(timetable_ment[0], L"���̵� : (��������)");
  wcscpy(timetable_ment[1], L"���̵� : �� ���� ü�� 3�ð��̴�! ���� ����!");

  GameScene* timetable_story = create_story_scene(
      teacher_help, story_sprites[0], timetable_ment, 2, rect, NULL);

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

  GameScene* first_help =
      create_story_scene(timetable_story, story_sprites[1], first_ment, 4, rect,
                         "Sound/story_begin.wav");

  return first_help;
}

// �ö��� ��ũ ���� ���� ���丮�� �����Ͽ� ��ȯ�մϴ�.
GameScene* create_after_disk_story(bool coco_win) {
  RECT rect;
  GameScene* pull_help = create_pull_help_scene();

  CREATE_MENT(teacher_ment, 4, NULL);

  wcscpy(teacher_ment[0], L"��, �̹��� �ٴٸ����!");
  wcscpy(teacher_ment[1], L"�߸��ϸ� ��ĥ �� �����ϱ� ���� �ȹٷ� ������.");
  wcscpy(
      teacher_ment[2],
      L"�ڽ��� �Ӹ� ���� ���ִ� Ű�� ���ʴ�� ������ ���� ��� �� �ְԵȴ�.");
  wcscpy(teacher_ment[3], L"���� ����� ������ �̱�ϱ� �ִ��� ������ ��ܶ�!");

  rect.top = 50;
  rect.left = 680;
  rect.bottom = 300;
  rect.right = 1050;

  GameScene* teacher_help = create_story_scene(pull_help, teacher_sprites[1],
                                               teacher_ment, 4, rect, NULL);

  CREATE_MENT(ment, 3, NULL);
  wcscpy(ment[0], coco_win ? L"���� : ǲ, ���� �̰��? ��"
                           : L"���� : ǲ, ���� �̰��? ��");
  wcscpy(ment[1],
         coco_win ? L"���� : �� �� �غ�~ �׷��� �ؼ� �� �̱� �� �ְھ�? ��"
                  : L"���� : �� �� �غ�~ �׷��� �ؼ� �� �̱� �� �ְھ�? ��");
  wcscpy(ment[2], coco_win ? L"���� : ���� �ǿ��� ���� �̱��״ϱ� �ΰ��..!"
                           : L"���� : �Ф� ���� ������ ���� �� �̱��..");

  rect.top = 450;
  rect.left = 200;
  rect.bottom = rect.top + 200;
  rect.right = rect.left + 750;

  GameScene* next_scene =
      create_story_scene(teacher_help, story_sprites[coco_win ? 6 : 7], ment, 3,
                         rect, "Sound/avengers.wav");

  return create_game_result_scene(coco_win, next_scene);
}

// �ٴٸ��� ���� ���� ���丮�� �����Ͽ� ��ȯ�մϴ�.
GameScene* create_after_pull_story(bool coco_win) {
  RECT rect;
  GameScene* dance_help = create_dance_help_scene();

  CREATE_MENT(teacher_ment, 4, NULL);

  wcscpy(teacher_ment[0], L"���������� �� �����̴�!");
  wcscpy(teacher_ment[1], L"����Ű Ȥ�� W, A, S, DŰ�� ���� �� ���� �ִ�.");
  wcscpy(teacher_ment[2],
         L"�ڽſ��� ����Ʈ����Ʈ�� ���� ���� �߰�, ������� �װ� ���� �߸� "
         L"�ȴ�.");
  wcscpy(teacher_ment[3],
         L"�߸� �����߸� �ٷ� Ż���̰�, ������ ������ �������ϱ� �����ض�!");

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
               ? L"���� : ���� �и��� ������? ���� ��.��.��.�� ��"
               : L"���� : �̹����� ���� �̰��? ��������������������������");
    wcscpy(
        ment[1],
        coco_win
            ? L"���� : ���� �� �� �̰�ٰ� �ڸ��ϴٴ�.. ����� �Ф�!!"
            : L"���� : �ʰ� �̱�ٰ� ���� �ʾҴ�? �Ͽ��� �Ը� ��ư����� ��");
    wcscpy(ment[2],
           coco_win
               ? L"���� : ������ ������ ������ �¸���.. ���� ���̴�.. �ΰ��!!"
               : L"���� : �̹� �� ��������..������ �ּ��� ���ϰھ�... �� "
                 L"�ڽž� ! ���ݸ� �� ���� ����!!");
  } else {
    wcscpy(ment[0],
           !coco_win
               ? L"���� : ���� �и��� ������? ���� ��.��.��.�� ��"
               : L"���� : �̹����� ���� �̰��? ��������������������������");
    wcscpy(
        ment[1],
        !coco_win
            ? L"���� : ���� �� �� �̰�ٰ� �ڸ��ϴٴ�.. ����� �Ф�!!"
            : L"���� : �ʰ� �̱�ٰ� ���� �ʾҴ�? �Ͽ��� �Ը� ��ư����� ��");
    wcscpy(ment[2],
           !coco_win
               ? L"���� : ������ ������ ������ �¸���.. ���� ���̴�.. �ΰ��!!"
               : L"���� : �̹� �� ��������..������ �ּ��� ���ϰھ�... �� "
                 L"�ڽž� ! ���ݸ� �� ���� ����!!");
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

// �� ���� ���� ���丮�� �����Ͽ� ��ȯ�մϴ�.
GameScene* create_after_dance_story(bool coco_win) {
  int coco_score = g_coco_score;
  if (coco_win) coco_score++;
  bool final_result = coco_score > g_dingding_score;

  update_set_score(final_result);
  CREATE_MENT(final_ment, 3, NULL);

  wcscpy(final_ment[0],
         !final_result ? L"���� : �̰�.. ��¥ �ϸ� ����.. ����.. ���ٴ�..."
                       : L"���� : �̰�.. ��¥ �ϸ� ����.. ����.. ���ٴ�...");
  wcscpy(final_ment[1],
         !final_result
             ? L"���� : û�� ��¥ �����.. �׷��� ������ �ؾ��� ���ھ���!"
             : L"���� : û�� ��¥ �����.. �׷��� ������ �ؾ��� ���ھ���!");
  wcscpy(final_ment[2], !final_result
                            ? L"���� : �� �ڽž�...������..�� �ο���!"
                            : L"���� : �� �ڽž�...������..�� �ο���!");

  RECT rect;
  rect.top = 120;
  rect.left = 200;
  rect.bottom = rect.top + 200;
  rect.right = rect.left + 750;

  GameScene* clean_scene = create_story_scene(
      create_final_result_scene(), story_sprites[final_result ? 5 : 4],
      final_ment, 3, rect, "Sound/game_over.wav");

  CREATE_MENT(ment, 2, NULL);

  wcscpy(ment[0], final_result ? L"���� : �ᱹ �������� ���� �̰��?"
                               : L"���� : �ᱹ �������� ���� �̰��?");
  wcscpy(ment[1], final_result
                      ? L"���� : �̱�ٰ� �� �׷�����.. ���� ����� ������?"
                      : L"���� : �̱�ٰ� �� �׷�����.. ���� ����� ������?");

  rect.top = 170;
  rect.left = final_result ? 350 : 450;
  rect.bottom = rect.top + 200;
  rect.right = rect.left + 350;
  GameScene* next_scene = create_story_scene(
      clean_scene, story_sprites[final_result ? 8 : 9], ment, 2, rect, NULL);

  return create_game_result_scene(coco_win, next_scene);
}
