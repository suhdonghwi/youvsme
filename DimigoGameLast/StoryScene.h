#pragma once
#include "GameScene.h"

#define CREATE_MENT(var, size, err)                \
  wchar_t** var = malloc(sizeof(wchar_t*) * size); \
  if (var == NULL) return err;                     \
  for (int i = 0; i < size; i++) {                 \
    var[i] = malloc(sizeof(wchar_t) * 100);        \
    if (var[i] == NULL) return err;                \
  }

typedef struct tagStorySceneData {
  HBITMAP background;
  GameObject* speech;
  GameScene* next_scene;
} StorySceneData;

GameScene* create_story_scene(GameScene* next_scene, HBITMAP background,
                              wchar_t** text, int text_count, RECT text_rect);

GameScene* create_after_main_story();
GameScene* create_after_disk_story(bool coco_win);
GameScene* create_after_pull_story(bool coco_win);
GameScene* create_after_dance_story(bool coco_win);