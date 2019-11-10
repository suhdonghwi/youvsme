#include "GameHelpScene.h"

#include "SpriteResources.h"

extern SHORT g_pressed_map[256];
extern GameScene* g_new_scene;

void on_render_game_help_scene(GameScene* scene, HDC main_dc) {
  GameHelpData* data = (GameHelpData*)scene->data;

  HFONT score_font = CreateFont(25, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0,
                                0, VARIABLE_PITCH | FF_ROMAN, TEXT("둥근모꼴"));
  SelectObject(main_dc, score_font);
  SetBkMode(main_dc, TRANSPARENT);

  render_bitmap(background_sprites[1], main_dc, (Pos){0, 0}, 25);
  render_bitmap(data->logo, main_dc, (Pos){400, 40}, 13);
  render_bitmap(data->help_message, main_dc, (Pos){300, 280}, 3.5);

  char* press_s = TEXT("[S]키를 눌러서 시작하세요!");

  SetTextColor(main_dc, RGB(150, 150, 150));
  TextOut(main_dc, 462, 642, press_s, strlen(press_s));

  SetTextColor(main_dc, RGB(60, 60, 60));
  TextOut(main_dc, 460, 640, press_s, strlen(press_s));

  if (g_pressed_map[0x53]) {
    g_new_scene = data->dest_scene;
  }
}

GameScene* create_game_help_scene(HBITMAP help_message, HBITMAP logo,
                                  GameScene* game_scene) {
  GameScene* scene = init_scene();
  scene->on_render = on_render_game_help_scene;
  scene->sleep_duration = 100;

  GameHelpData* data = malloc(sizeof(GameHelpData));
  if (data == NULL) return NULL;
  data->help_message = help_message;
  data->logo = logo;
  data->dest_scene = game_scene;

  scene->data = data;

  return scene;
}
