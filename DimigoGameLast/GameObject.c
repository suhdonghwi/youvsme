#include "GameObject.h"
#include <math.h>

GameObject* init_game_object() {
  GameObject* object = malloc(sizeof(GameObject));
  if (object == NULL) return NULL;

  object->alive = true;
  object->sprites = NULL;
  object->sprite_index = 0;
  object->pos = (Pos){0, 0};

  object->scale = 1;

  object->on_update = NULL;

  return object;
}

void deinit_game_object(GameObject* object) {}

void render_game_object(GameObject* object, HDC main_dc) {
  HDC mem_dc = CreateCompatibleDC(main_dc);

  HBITMAP current_sprite = object->sprites[object->sprite_index];
  HBITMAP old_bitmap = (HBITMAP)SelectObject(mem_dc, current_sprite);

  BITMAP bitmap_data;
  GetObject(current_sprite, sizeof(BITMAP), &bitmap_data);

  double scale_root = sqrt(object->scale);

  RECT object_rect = {object->pos.x, object->pos.y,
                      bitmap_data.bmWidth * scale_root,
                      bitmap_data.bmHeight * scale_root};

  TransparentBlt(main_dc, object_rect.left, object_rect.top, object_rect.right,
                 object_rect.bottom, mem_dc, 0, 0,
                 object_rect.right / scale_root,
                 object_rect.bottom / scale_root, RGB(255, 0, 255));

  DeleteDC(mem_dc);
}
