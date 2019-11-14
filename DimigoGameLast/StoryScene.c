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

  wcscpy(teacher_ment[0], L"��, ����!");
  wcscpy(teacher_ment[1], L"���� �츮�� �ö��� ��ũ�� ���Ŵ�.");
  wcscpy(teacher_ment[2],
         L"�ö��� ��ũ�� ����ũ�� �ٶ��� ��� �Ҹ� ���󰡰� �Ǿ��ִ�.");
  wcscpy(teacher_ment[3],
         L"�ָ� ������ ���� ������ �����״� ���� ũ�� ���̽����.");

  GameScene* teacher_help = create_story_scene(disk_help, game_help_sprites[2],
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

GameScene* create_after_disk_story(bool coco_win) {
  CREATE_MENT(ment, 2, NULL);
  wcscpy(ment[0],
         coco_win ? L"���� : ǲ, ���� �̰��?" : L"���� : ǲ, ���� �̰��?");
  wcscpy(ment[1], coco_win ? L"���� : ���� �ǿ��� ���� �̱��״ϱ� �ΰ��..!"
                           : L"���� : ���� �ǿ��� ���� �� �̱��.. �����ض�!");

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
    wcscpy(ment[0], coco_win ? L"���� : ���� �и��� ������? �̹��� ���� �̰��?"
                             : L"���� : �̹����� ���� �̰��? �̹��� �ʰ� "
                               L"�̱�ٰ� ���� �ʾҴ�?");
    wcscpy(ment[1],
           coco_win ? L"���� : ���� ������ �����̴�.. �������� ���� �̱�ھ�!"
                    : L"���� : �̹� �� ��������.. ������ �ּ��� ���ϰھ�!");
  } else {
    wcscpy(ment[0], !coco_win
                        ? L"���� : ���� �и��� ������? �̹��� ���� �̰��?"
                        : L"���� : �̹����� ���� �̰��? �̹��� �ʰ� "
                          L"�̱�ٰ� ���� �ʾҴ�?");
    wcscpy(ment[1],
           !coco_win ? L"���� : ���� ������ �����̴�.. �������� ���� �̱�ھ�!"
                     : L"���� : �̹� �� ��������.. ������ �ּ��� ���ϰھ�!");
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
                      ? L"���� : �̰� ��¥�ϸ� ����.. ���� ���ٴ� �Ф�"
                      : L"���� : �̰� ��¥�ϸ� ����.. ���� ���ٴ� �Ф�");
  wcscpy(ment[1], !final_result
                      ? L"���� : û�� ��¥ ����� .. �� ���� �ʹ� �Ф�"
                      : L"���� : û�� ��¥ �����.. �� ���� �;� �Ф�");
  wcscpy(ment[2], !final_result
                      ? L"���� : �׷���.. ������ �ؾ���!"
                      : L"���� : �׷���.. ���� �־��� �ӹ��� ������ �ؾ���.. ");
  wcscpy(ment[3], !final_result ? L"���� : �� �ڽž� ... ������... �� �ο���!"
                                : L"���� : �� �ڽž� ... ������... �� �ο���!");

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
