#include "GameScene.h"

typedef struct tagStorySceneData {
  HBITMAP background;
} StorySceneData;

GameScene* create_story_scene(GameScene* next_scene, HBITMAP background,
                              wchar_t** text, int text_count, RECT text_rect);