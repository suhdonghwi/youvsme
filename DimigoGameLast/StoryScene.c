#include "StoryScene.h"
#include "Speech.h"

void on_render_story_scene(GameScene* scene, HDC main_dc) {
  StorySceneData* data = scene->data;

  render_bitmap(data->background, main_dc, (Pos){0, 0}, 5.1);
}

GameScene* create_story_scene(GameScene* next_scene, HBITMAP background,
                              char** text, int text_count, RECT text_rect) {
  GameScene* scene = init_scene();
  scene->on_render = on_render_story_scene;

  GameObject* speech = create_speech(text, text_count, text_rect);
  insert_game_object(speech, scene);

  StorySceneData* data = malloc(sizeof(StorySceneData));
  if (data == NULL) return NULL;
  data->background = background;

  scene->data = data;

  return scene;
}