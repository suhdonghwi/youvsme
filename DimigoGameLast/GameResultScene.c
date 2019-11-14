#include "GameResultScene.h"

#include "CheeringPlayer.h"
#include "GameScene.h"
#include "KeyInput.h"
#include "ScoreDisplay.h"
#include "SpriteResources.h"

extern int g_coco_score;
extern int g_dingding_score;
extern GameScene* g_new_scene;
extern bool g_story_mode;

void on_render_game_result_scene(GameScene* scene, HDC main_dc) {
  GameResultSceneData* data = scene->data;

  render_bitmap(background_sprites[1], main_dc, (Pos){0, 0}, 20.25);

  if (g_story_mode) {
    char* press_enter = TEXT("[Enter]키를 눌러서 넘어가세요");

    SelectObject(main_dc, data->font);
    SetTextColor(main_dc, RGB(100, 100, 100));
    TextOut(main_dc, 362, 632, press_enter, strlen(press_enter));
  } else {
    char* press_enter = TEXT("[Enter]키를 눌러서 메인 화면으로");

    SelectObject(main_dc, data->font);
    SetTextColor(main_dc, RGB(100, 100, 100));
    TextOut(main_dc, 362, 552, press_enter, strlen(press_enter));
  }

  if (is_pressed(VK_RETURN)) {
    g_new_scene = data->next_scene;
  }
}

void on_first_render_game_result_scene(GameScene* scene, HDC main_dc) {
  PlaySound(TEXT("Sound/victory.wav"), NULL, SND_FILENAME | SND_ASYNC);
}

GameScene* create_game_result_scene(bool coco_won, GameScene* next_scene) {
  if (coco_won)
    g_coco_score++;
  else
    g_dingding_score++;

  GameScene* scene = init_scene();

  GameObject* cheering_player = create_cheering_player(coco_won);
  cheering_player->pos = (Pos){515, 320};
  insert_game_object(cheering_player, scene);

  if (g_story_mode) {
    GameObject* score = create_score_display();
    score->pos = (Pos){430, 500};
    insert_game_object(score, scene);
  }

  scene->on_render = on_render_game_result_scene;
  scene->on_first_render = on_first_render_game_result_scene;
  scene->sleep_duration = 100;

  GameResultSceneData* data = malloc(sizeof(GameResultSceneData));
  if (data == NULL) return NULL;
  data->font = CreateFont(25, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0,
                          VARIABLE_PITCH | FF_ROMAN, TEXT("둥근모꼴"));
  data->next_scene = next_scene;

  scene->data = data;

  return scene;
}
