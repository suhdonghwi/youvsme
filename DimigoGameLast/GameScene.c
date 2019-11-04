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
  scene->sleep_duration = 0;
  scene->on_render = NULL;
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
    GameSceneNode* current = scene->head;
    while (current->next != NULL) {
      current = current->next;
    }
    current->next = new_node;
  }
}

bool rect_intersect_check(RECT r1, RECT r2) {
  return !(r2.left > r1.right || r2.right < r1.left || r2.top > r1.bottom ||
           r2.bottom < r1.top);
}

void render_game_scene(GameScene* scene, HDC main_dc) {
  if (scene->on_render != NULL) scene->on_render(scene, main_dc);

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

    if (node == NULL) break;

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

    if (node->game_object->on_render != NULL)
      node->game_object->on_render(node->game_object, main_dc);

    render_game_object(node->game_object, main_dc);

    if (node->game_object->after_render != NULL)
      node->game_object->after_render(node->game_object, main_dc);

    prev = node;
    node = node->next;
  }

  Sleep(scene->sleep_duration);
}