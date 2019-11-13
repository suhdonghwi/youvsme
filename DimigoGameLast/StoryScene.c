#include "StoryScene.h"
#include "Speech.h"

void on_render_story_scene(GameScene* scene, HDC main_dc) {
  StorySceneData* data = scene->data;

  render_bitmap(data->background, main_dc, (Pos){0, 0}, 5.1);
}

GameScene* create_story_scene(GameScene* next_scene, HBITMAP background,
                              char* text, Pos text_pos) {
  GameScene* scene = init_scene();
  scene->on_render = on_render_story_scene;

  char** t = malloc(sizeof(char*) * 2);

  t[0] = malloc(sizeof(char) * 100);
  strcpy(t[0], "Hello, world!");
  t[1] = malloc(sizeof(char) * 100);
  strcpy(t[1], "Goodbye, world!");

  RECT rect;
  rect.top = 50;
  rect.left = 680;
  rect.bottom = 300;
  rect.right = 1050;
  GameObject* speech = create_speech(t, 2, rect);
  insert_game_object(speech, scene);

  StorySceneData* data = malloc(sizeof(StorySceneData));
  if (data == NULL) return NULL;
  data->background = background;

  scene->data = data;

  return scene;
}