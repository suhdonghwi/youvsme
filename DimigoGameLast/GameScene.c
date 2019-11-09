#include "GameScene.h"

#include "SpriteResources.h"

extern GameScene* g_new_scene;

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
  if (object == NULL) return;

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

void render_game_scene(GameScene* scene, HDC main_dc, int window_width,
                       int window_height) {
  HDC back_dc = CreateCompatibleDC(main_dc);

  HBITMAP back_bitmap =
      CreateCompatibleBitmap(main_dc, window_width, window_height);
  SelectObject(back_dc, back_bitmap);
  DeleteObject(back_bitmap);

  HFONT score_font = CreateFont(50, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0,
                                0, VARIABLE_PITCH | FF_ROMAN, TEXT("µÕ±Ù¸ð²Ã"));
  SelectObject(back_dc, score_font);
  SetBkMode(back_dc, TRANSPARENT);
  SetTextColor(back_dc, RGB(255, 0, 0));

  if (scene->on_render != NULL) scene->on_render(scene, back_dc);

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

    if (g_new_scene != NULL) return;
    if (node == NULL) return;

    if (node->game_object->on_render != NULL)
      node->game_object->on_render(node->game_object, back_dc);

    render_game_object(node->game_object, back_dc);

    if (node->game_object->after_render != NULL)
      node->game_object->after_render(node->game_object, back_dc);

    prev = node;
    node = node->next;
  }

  BitBlt(main_dc, 0, 0, window_width, window_height, back_dc, 0, 0, SRCCOPY);
  DeleteDC(back_dc);
  DeleteObject(score_font);

  Sleep(scene->sleep_duration);
}