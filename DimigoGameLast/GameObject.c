#include "GameObject.h"
#include <math.h>

GameObject* init_game_object() {
  GameObject* object = malloc(sizeof(GameObject));
  if (object == NULL) return NULL;

  strncpy(object->tag, "(default)", 100);
  object->alive = true;
  object->collidable = false;

  object->sprites = NULL;
  object->sprite_index = 0;
  object->pos = (Pos){0, 0};

  object->scale = 1;

  object->on_update = NULL;
  object->on_destroy = NULL;
  object->on_collide = NULL;

  return object;
}

void deinit_game_object(GameObject* object) {
  if (object->on_destroy != NULL) {
    object->on_destroy(object);
  }
}

void render_game_object(GameObject* object, HDC main_dc) {
  HDC mem_dc = CreateCompatibleDC(main_dc);

  HBITMAP current_sprite = object->sprites[object->sprite_index];
  HBITMAP old_bitmap = (HBITMAP)SelectObject(mem_dc, current_sprite);

  BITMAP bitmap_data;
  GetObject(current_sprite, sizeof(BITMAP), &bitmap_data);

  double scale_root = sqrt(object->scale);

  RECT object_rect = {object->pos.x, object->pos.y,
                      (LONG)(bitmap_data.bmWidth * scale_root),
                      (LONG)(bitmap_data.bmHeight * scale_root)};

  TransparentBlt(main_dc, object_rect.left, object_rect.top, object_rect.right,
                 object_rect.bottom, mem_dc, 0, 0,
                 (int)(object_rect.right / scale_root),
                 (int)(object_rect.bottom / scale_root), RGB(255, 0, 255));

  DeleteDC(mem_dc);
}

RECT get_game_object_rect(GameObject* object) {
  HBITMAP sprite = object->sprites[object->sprite_index];
  BITMAP bitmap;

  GetObject(sprite, sizeof(BITMAP), &bitmap);

  double scale_root = sqrt(object->scale);

  RECT rect;
  rect.left = object->pos.x;
  rect.top = object->pos.y;
  rect.right = rect.left + (LONG)(bitmap.bmWidth * scale_root);
  rect.bottom = rect.top + (LONG)(bitmap.bmHeight * scale_root);

  return rect;
}
