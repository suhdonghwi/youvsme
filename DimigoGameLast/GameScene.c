#include "GameScene.h"

GameSceneNode* create_node(GameObject* object) {
  GameSceneNode* node = malloc(sizeof(GameSceneNode));
  if (node == NULL) return NULL;

  node->game_object = object;
  node->next = NULL;
  return node;
}

GameScene* init_scene() {
  GameScene* scene = malloc(sizeof(GameScene));
  if (scene == NULL) return NULL;

  scene->head = NULL;
  return scene;
}

void deinit_scene(GameScene* scene) {
  GameSceneNode* node = scene->head;

  while (node != NULL) {
    GameSceneNode* tmp = node;
    node = node->next;
    deinit_game_object(tmp->game_object);
    free(tmp);
  }
}

void insert_game_object(GameObject* object, GameScene* scene) {
  GameSceneNode* new_node = create_node(object);
  if (scene->head == NULL) {
    scene->head = new_node;
  } else {
    new_node->next = scene->head;
    scene->head = new_node;
  }
}

void render_game_scene(GameScene* scene, HDC main_dc) {
  GameSceneNode* node = scene->head;
  GameSceneNode* prev = node;

  while (node != NULL) {
    if (!node->game_object->alive) {
      prev->next = node->next;
      if (node == scene->head) {
        scene->head = node->next;
      }

      deinit_game_object(node->game_object);
      free(node);
      return;
    }

    render_game_object(node->game_object, main_dc);

    if (node->game_object->on_update != NULL) {
      node->game_object->on_update(node->game_object);
    }

    prev = node;
    node = node->next;
  }
}