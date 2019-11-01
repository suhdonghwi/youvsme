#pragma once
#include "GameObject.h"

typedef struct tagGameSceneNode {
  GameObject* game_object;
  struct tagGameSceneNode* next;
} GameSceneNode;

typedef struct tagGameScene {
  GameSceneNode* head;
} GameScene;

GameSceneNode* create_node(GameObject* object);
GameScene* create_scene();

void insert_game_object(GameObject* game_object, GameScene* game_scene);

void render_game_scene(GameScene* scene, HDC main_dc);
