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
  GameScene* disk_help = create_disk_help_scene();

  RECT rect;
  rect.top = 50;
  rect.left = 680;
  rect.bottom = 300;
  rect.right = 1050;

  CREATE_MENT(teacher_ment, 4, NULL);

  wcscpy(teacher_ment[0], L"切, 増掻!");
  wcscpy(teacher_ment[1], L"戚薦 酔軒澗 巴虞跡 巨什滴研 壕随暗陥.");
  wcscpy(teacher_ment[2],
         L"巴虞跡 巨什滴澗 原戚滴拭 郊寓聖 企壱 災檎 劾虞亜惟 鞠嬢赤陥.");
  wcscpy(teacher_ment[3],
         L"菰軒 劾形醤 疏精 繊呪研 閤聖砺艦 需聖 滴惟 級戚習嬢虞.");

  GameScene* teacher_help = create_story_scene(disk_help, teacher_sprites[0],
                                               teacher_ment, 4, rect, NULL);

  rect.top = 500;
  rect.left = 300;
  rect.bottom = rect.top + 140;
  rect.right = rect.left + 500;

  CREATE_MENT(timetable_ment, 2, NULL);
  wcscpy(timetable_ment[0], L"焼戚級 : (枢失枢失)");
  wcscpy(timetable_ment[1], L"焼戚級 : 人 神潅 端整 3獣娃戚陥! 察軒 亜切!");

  GameScene* timetable_story = create_story_scene(
      teacher_help, story_sprites[0], timetable_ment, 2, rect, NULL);

  rect.top = 450;
  rect.left = 200;
  rect.bottom = rect.top + 200;
  rect.right = rect.left + 750;

  CREATE_MENT(first_ment, 4, NULL);
  wcscpy(first_ment[0],
         L"坪坪人 漁漁戚澗 戚腰爽拭 鋼拭辞 説陥廃 析聖 坦軒馬澗 爽腰戚 "
         L"鞠醸柔艦陥. ");
  wcscpy(first_ment[1], L"益軒壱 原徴鎧, 神潅精 '榎推瑛亜'研 馬澗 劾脊艦陥.");
  wcscpy(first_ment[2],
         L"坪坪人 漁漁戚澗 神潅 惟績聖 背辞 遭 紫寓戚 害焼辞 短社研 馬壱 "
         L"亜奄稽 梅柔艦陥.");
  wcscpy(first_ment[3], L"引尻 刊亜 戚奄惟 吃猿推?");

  GameScene* first_help =
      create_story_scene(timetable_story, story_sprites[1], first_ment, 4, rect,
                         "Sound/story_begin.wav");

  return first_help;
}

GameScene* create_after_disk_story(bool coco_win) {
  RECT rect;
  GameScene* pull_help = create_pull_help_scene();

  CREATE_MENT(teacher_ment, 4, NULL);

  wcscpy(teacher_ment[0], L"切, 戚腰殖 匝陥軒奄陥!");
  wcscpy(teacher_ment[1], L"設公馬檎 陥張 呪 赤生艦猿 舛重 業郊稽 託軒壱.");
  wcscpy(
      teacher_ment[2],
      L"切重税 袴軒 是拭 彊赤澗 徹研 託景企稽 刊牽檎 匝聖 雁掩 呪 赤惟吉陥.");
  wcscpy(teacher_ment[3],
         L"胡煽 炎降聖 説生檎 戚奄艦猿 重紗拝 呪 赤亀系 尻柔背虞!");

  rect.top = 50;
  rect.left = 680;
  rect.bottom = 300;
  rect.right = 1050;

  GameScene* teacher_help = create_story_scene(pull_help, teacher_sprites[1],
                                               teacher_ment, 4, rect, NULL);

  CREATE_MENT(ment, 2, NULL);
  wcscpy(ment[0],
         coco_win ? L"坪坪 : 撚, 鎧亜 戚医革?" : L"漁漁 : 撚, 鎧亜 戚医革?");
  wcscpy(ment[1], coco_win ? L"漁漁 : 陥製 毒拭澗 鎧亜 戚掩砺艦猿 砧壱坐..!"
                           : L"坪坪 : 陥製 毒拭澗 鎧亜 伽 戚延陥.. 延舌背虞!");

  rect.top = 450;
  rect.left = 200;
  rect.bottom = rect.top + 200;
  rect.right = rect.left + 750;

  GameScene* next_scene =
      create_story_scene(teacher_help, story_sprites[coco_win ? 6 : 7], ment, 2,
                         rect, "Sound/avengers.wav");

  return create_game_result_scene(coco_win, next_scene);
}

GameScene* create_after_pull_story(bool coco_win) {
  RECT rect;
  GameScene* dance_help = create_dance_help_scene();

  CREATE_MENT(teacher_ment, 4, NULL);

  wcscpy(teacher_ment[0], L"原走厳生稽 危什 呪穣戚陥!");
  wcscpy(teacher_ment[1], L"号狽徹 箸精 W, A, S, D徹稽 茶聖 窒 呪亜 赤陥.");
  wcscpy(teacher_ment[2],
         L"切重拭惟 什匂闘虞戚闘亜 神檎 茶聖 蓄壱, 雌企畷精 益杏 魚虞辞 蓄檎 "
         L"吉陥.");
  wcscpy(teacher_ment[3],
         L"設公 魚虞蓄檎 郊稽 纏喰戚壱, 哀呪系 遭楳戚 察虞走艦猿 増掻!");

  rect.top = 50;
  rect.left = 680;
  rect.bottom = 300;
  rect.right = 1050;

  GameScene* teacher_help = create_story_scene(dance_help, teacher_sprites[2],
                                               teacher_ment, 4, rect, NULL);

  CREATE_MENT(ment, 3, NULL);

  if (g_coco_score == 0) {
    wcscpy(ment[0], coco_win ? L"坪坪 : 鎧亜 歳誤備 源梅走? 戚腰殖 鎧亜 戚医革?"
                             : L"漁漁 : 戚腰拭亀 鎧亜 戚医革? 戚腰殖 格亜 "
                               L"戚延陥壱 馬走 省紹艦?");
    wcscpy(ment[1],
           coco_win ? L"漁漁 : 戚薦 原走厳 惟績戚陥.. 原走厳殖 鎧亜 戚奄畏嬢!"
                    : L"坪坪 : 戚耕 遭 毒戚走幻.. 魁猿走 置識聖 陥馬畏嬢!");
  } else {
    wcscpy(ment[0], !coco_win
                        ? L"漁漁 : 鎧亜 歳誤備 源梅走? 戚腰殖 鎧亜 戚医革?"
                        : L"坪坪 : 戚腰拭亀 鎧亜 戚医革? 戚腰殖 格亜 "
                          L"戚延陥壱 馬走 省紹艦?");
    wcscpy(ment[1],
           !coco_win ? L"坪坪 : 戚薦 原走厳 惟績戚陥.. 原走厳殖 鎧亜 戚奄畏嬢!"
                     : L"漁漁 : 戚耕 遭 毒戚走幻.. 魁猿走 置識聖 陥馬畏嬢!");
  }

  rect.top = 450;
  rect.left = 200;
  rect.bottom = rect.top + 200;
  rect.right = rect.left + 750;

  GameScene* next_scene =
      create_story_scene(teacher_help, story_sprites[coco_win ? 2 : 3], ment, 2,
                         rect, "Sound/avengers.wav");
  return create_game_result_scene(coco_win, next_scene);
}

GameScene* create_after_dance_story(bool coco_win) {
  int coco_score = g_coco_score;
  if (coco_win) coco_score++;
  bool final_result = coco_score > g_dingding_score;

  update_set_score(final_result);
  CREATE_MENT(final_ment, 4, NULL);

  wcscpy(final_ment[0], !final_result
                            ? L"坪坪 : 戚惟 遭促析軒 蒸嬢.. 鎧亜 走陥艦 ばば"
                            : L"漁漁 : 戚惟 遭促析軒 蒸嬢.. 鎧亜 走陥艦 ばば");
  wcscpy(final_ment[1], !final_result
                            ? L"坪坪 : 短社 遭促 毘級陥 .. 増 亜壱 粛陥 ばば"
                            : L"漁漁 : 短社 遭促 毘級陥.. 増 亜壱 粛嬢 ばば");
  wcscpy(final_ment[2],
         !final_result
             ? L"坪坪 : 益掘亀.. 伸宿備 背醤走!"
             : L"漁漁 : 益掘亀.. 鎧惟 爽嬢遭 績巷澗 伸宿備 背醤走.. ");
  wcscpy(final_ment[3], !final_result
                            ? L"坪坪 : 鎧 切重焼 ... 然走幻... 設 塾頗陥!"
                            : L"漁漁 : 鎧 切重焼 ... 然走幻... 設 塾頗陥!");

  RECT rect;
  rect.top = 120;
  rect.left = 200;
  rect.bottom = rect.top + 200;
  rect.right = rect.left + 750;

  GameScene* clean_scene = create_story_scene(
      create_final_result_scene(), story_sprites[coco_win ? 5 : 4], final_ment,
      4, rect, "Sound/game_over.wav");

  CREATE_MENT(ment, 3, NULL);

  wcscpy(ment[0], final_result ? L"坪坪 : 衣厩 原走厳殖 鎧亜 戚医革?"
                               : L"漁漁 : 衣厩 原走厳殖 鎧亜 戚医革?");
  wcscpy(ment[1], final_result
                      ? L"坪坪 : 戚延陥壱 厳 益君希艦.. 鎧亜 猿災走 源隈走?"
                      : L"漁漁 : 戚延陥壱 厳 益君希艦.. 鎧亜 猿災走 源隈走?");
  wcscpy(ment[2], final_result ? L"漁漁 : 照掬 ばば" : L"坪坪 : 照掬 ばば");

  rect.top = 150;
  rect.left = 370;
  rect.bottom = rect.top + 200;
  rect.right = rect.left + 350;
  GameScene* next_scene = create_story_scene(
      clean_scene, story_sprites[coco_win ? 8 : 9], ment, 3, rect, NULL);

  return create_game_result_scene(coco_win, next_scene);
}
