#include <stdio.h>

#include "GameHelpScene.h"

#include "KeyInput.h"
#include "SpriteResources.h"

#include "DanceGameScene.h"
#include "DiskGameScene.h"
#include "PullGameScene.h"
#include "ReadyStartScene.h"

extern GameScene* g_new_scene;
extern bool g_story_mode;

// ���� ���� ȭ���� on_render �ݹ��Դϴ�. SŰ�� �ԷµǸ� ������ ���� ȭ������
// �Ѿ�ϴ�.
void on_render_game_help_scene(GameScene* scene, HDC main_dc) {
  GameHelpData* data = (GameHelpData*)scene->data;

  SelectObject(main_dc, data->font);

  render_bitmap(background_sprites[1], main_dc, (Pos){0, 0}, 20.25);
  render_bitmap(data->help_message, main_dc, (Pos){250, 280}, 3.5);
  render_bitmap(data->logo, main_dc, data->logo_pos, 13);

  if (g_story_mode) {
    char stage_text[100];
    sprintf(stage_text, "- STAGE %d -", data->stage);
    SetTextColor(main_dc, RGB(30, 30, 30));
    TextOut(main_dc, 472, 30, stage_text, strlen(stage_text));
  }

  char* press_s = TEXT("[S]Ű�� ������ �����ϼ���!");

  SetTextColor(main_dc, RGB(150, 150, 150));
  TextOut(main_dc, 382, 622, press_s, strlen(press_s));

  SetTextColor(main_dc, RGB(60, 60, 60));
  TextOut(main_dc, 380, 620, press_s, strlen(press_s));

  if (is_pressed(0x53)) {
    g_new_scene = data->dest_scene;
  }
}

// ���� �޽��� ��Ʈ��, ���� �ΰ�, �ΰ� ��ġ, ���� ȭ��, �������� ���� �ް� ����
// ���� ȭ���� ������ �� ��ȯ�մϴ�.
GameScene* create_game_help_scene(HBITMAP help_message, HBITMAP logo,
                                  Pos logo_pos, GameScene* game_scene,
                                  int stage) {
  GameScene* scene = init_scene();
  scene->on_render = on_render_game_help_scene;
  scene->sleep_duration = 100;

  GameHelpData* data = malloc(sizeof(GameHelpData));
  if (data == NULL) return NULL;
  data->help_message = help_message;
  data->logo = logo;
  data->logo_pos = logo_pos;
  data->dest_scene = game_scene;
  data->font = CreateFont(25, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0,
                          VARIABLE_PITCH | FF_ROMAN, TEXT("�ձٸ��"));
  data->stage = stage;

  scene->data = data;

  return scene;
}

// �ö��� ��ũ ������ ���� ȭ���� �����մϴ�.
GameScene* create_disk_help_scene() {
  GameScene* disk_scene = create_disk_game_scene(true, (Pos){0, 0});
  GameScene* ready_scene = create_readystart_scene(
      disk_scene, coco_disk_ready_sprites, 3, (Pos){560, 300});
  GameScene* help_scene = create_game_help_scene(
      game_help_sprites[0], logo_sprites[0], (Pos){360, 50}, ready_scene, 1);

  return help_scene;
}

// �ٴٸ��� ������ ���� ȭ���� �����մϴ�.
GameScene* create_pull_help_scene() {
  GameScene* pull_scene = create_pull_game_scene();
  GameScene* ready_scene = create_readystart_scene(
      pull_scene, ready_start_sprites, 2, (Pos){560, 300});
  GameScene* help_scene = create_game_help_scene(
      game_help_sprites[1], logo_sprites[1], (Pos){350, 80}, ready_scene, 2);
  return help_scene;
}

// �� ������ ���� ȭ���� �����մϴ�.
GameScene* create_dance_help_scene() {
  GameScene* dance_scene = create_dance_game_scene();
  GameScene* ready_scene = create_readystart_scene(
      dance_scene, ready_start_sprites, 2, (Pos){560, 300});
  GameScene* help_scene = create_game_help_scene(
      game_help_sprites[2], logo_sprites[2], (Pos){340, 80}, ready_scene, 3);
  return help_scene;
}
