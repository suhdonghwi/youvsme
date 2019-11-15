#include "GameObject.h"
#include <math.h>

// 게임 오브젝트를 할당하고 초기 상태로 둔 뒤 반환합니다.
GameObject* init_game_object(HBITMAP* sprites) {
  GameObject* object = malloc(sizeof(GameObject));
  if (object == NULL) return NULL;

  strncpy(object->tag, "(default)", 100);
  object->rendered = false;
  object->alive = true;
  object->collidable = false;

  object->sprites = sprites;
  object->sprite_index = 0;
  object->pos = (Pos){0, 0};

  object->scale = 1;

  object->data = NULL;

  object->on_destroy = NULL;
  object->on_collide = NULL;
  object->on_render = NULL;
  object->on_first_render = NULL;
  object->after_render = NULL;

  return object;
}

// 사용을 완료한 게임 오브젝트를 해제시킵니다.
void deinit_game_object(GameObject* object) {
  if (object->on_destroy != NULL) {
    object->on_destroy(object);
  }

  free(object->data);
  free(object);
}

// 비트맵, DC, 위치, 확대 비율을 받고 DC에 주어진 비트맵을 위치와 크기를
// 조정해서 그립니다.
void render_bitmap(HBITMAP bitmap, HDC main_dc, Pos pos, double scale) {
  HDC bitmap_dc = CreateCompatibleDC(main_dc);
  SelectObject(bitmap_dc, bitmap);

  BITMAP bitmap_data;
  GetObject(bitmap, sizeof(BITMAP), &bitmap_data);

  double scale_root = sqrt(scale),
         real_width = bitmap_data.bmWidth * scale_root,
         real_height = bitmap_data.bmHeight * scale_root;

  RECT object_rect = {pos.x, pos.y, (LONG)real_width, (LONG)real_height};

  TransparentBlt(main_dc, object_rect.left, object_rect.top, object_rect.right,
                 object_rect.bottom, bitmap_dc, 0, 0,
                 (int)ceil(object_rect.right / scale_root),
                 (int)ceil(object_rect.bottom / scale_root), RGB(255, 0, 255));

  DeleteDC(bitmap_dc);
}

// 게임 오브젝트를 받고 데이터를 기반으로 주어진 DC에 그립니다.
void render_game_object(GameObject* object, HDC main_dc) {
  if (!object->rendered) {
    if (object->on_first_render != NULL)
      object->on_first_render(object, main_dc);
    object->rendered = true;
  }

  if (object->on_render != NULL) object->on_render(object, main_dc);

  if (object->sprites == NULL) return;
  render_bitmap(object->sprites[object->sprite_index], main_dc, object->pos,
                object->scale);

  if (object->after_render != NULL) object->after_render(object, main_dc);
}

// 게임 오브젝트를 받고 위치, 크기 데이터를 기반으로 해당하는 RECT 데이터를
// 반환합니다.
RECT get_game_object_rect(GameObject* object) {
  if (object->sprites == NULL) {
    RECT result;
    result.left = object->pos.x;
    result.top = object->pos.y;
    result.right = 0;
    result.bottom = 0;

    return result;
  }

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
