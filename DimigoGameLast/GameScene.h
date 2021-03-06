#pragma once
#include "GameObject.h"

typedef void (*OnRenderScene)(struct tagGameScene*, HDC);
typedef void (*OnFirstRenderScene)(struct tagGameScene*, HDC);

typedef struct tagGameSceneNode {
  GameObject* game_object;
  struct tagGameSceneNode* next;
} GameSceneNode;

typedef struct tagGameScene {
  GameSceneNode* head;
  int sleep_duration;

  void* data;

  OnRenderScene on_render;
  OnFirstRenderScene on_first_render;
  bool rendered;
} GameScene;

GameSceneNode* create_node(GameObject* object);
GameScene* init_scene();
void deinit_scene(GameScene* scene);

void insert_game_object(GameObject* game_object, GameScene* game_scene);
void render_game_scene(GameScene* scene, HDC main_dc, int window_width,
                       int window_height);
