#include "GameScene.h"

GameSceneNode* create_node(GameObject* object) {
  GameSceneNode* node = malloc(sizeof(GameSceneNode));
  if (node == NULL) return NULL;

  node->game_object = object;
  node->next = NULL;
  return node;
}

GameScene* create_scene() {
  GameScene* scene = malloc(sizeof(GameScene));
  if (scene == NULL) return NULL;

  scene->head = NULL;
  return scene;
}

void insert_game_object(GameObject* object, GameScene* scene) {
  GameSceneNode* new_node = create_node(object);
  if (scene->head == NULL) {
    scene->head = new_node;
  } else {
    GameSceneNode* tail = scene->head;
    while (tail->next != NULL) {
      tail = tail->next;
    }

    tail->next = new_node;
  }
}

void render_game_scene(GameScene* scene, HDC main_dc) {
  GameSceneNode* node = scene->head;

  while (node != NULL) {
    if (node->game_object->on_update != NULL) {
      node->game_object->on_update(node->game_object);
    }

    render_game_object(node->game_object, main_dc);
    node = node->next;
  }
}