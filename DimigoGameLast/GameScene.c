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
    GameSceneNode* tmp = node->next;

    deinit_game_object(node->game_object);
    free(node);

    node = tmp;
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

bool rect_intersect_check(RECT r1, RECT r2) {
  return !(r2.left > r1.right || r2.right < r1.left || r2.top > r1.bottom ||
           r2.bottom < r1.top);
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

      GameSceneNode* tmp = node->next;

      deinit_game_object(node->game_object);
      free(node);

      node = tmp;
    }

    GameSceneNode* node2 = node->next;
    while (node2 != NULL) {
      RECT rect1 = get_game_object_rect(node->game_object),
           rect2 = get_game_object_rect(node2->game_object);

      if (rect_intersect_check(rect1, rect2) && node->game_object->collidable &&
          node2->game_object->collidable) {
        if (node->game_object->on_collide != NULL)
          node->game_object->on_collide(node->game_object, node2->game_object);
        if (node2->game_object->on_collide != NULL)
          node2->game_object->on_collide(node2->game_object, node->game_object);
      }

      node2 = node2->next;
    }

    if (node == NULL) return;

    render_game_object(node->game_object, main_dc);

    if (node->game_object->on_update != NULL) {
      node->game_object->on_update(node->game_object);
    }

    prev = node;
    node = node->next;
  }
}