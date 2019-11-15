#include "ReadyStartScene.h"

#include "SpriteResources.h"

extern GameScene* g_new_scene;

// 준비 시작 화면의 on_render 콜백입니다. 현재 인덱스에 해당하는 스프라이트를
// 렌더링합니다.
void on_render_readystart_scene(GameScene* scene, HDC main_dc) {
  ReadyStartData* data = (ReadyStartData*)scene->data;

  render_bitmap(background_sprites[1], main_dc, (Pos){0, 0}, 20.25);
  HBITMAP current_bitmap = data->slide_bitmaps[data->index];
  BITMAP bitmap_data;
  GetObject(current_bitmap, sizeof(BITMAP), &bitmap_data);
  render_bitmap(
      current_bitmap, main_dc,
      (Pos){(int)(data->render_pos.x - (bitmap_data.bmWidth * 4.5) / 2),
            (int)(data->render_pos.y - (bitmap_data.bmHeight * 4.5) / 2)},
      20.25);

  data->index++;

  if (data->index > data->slide_size) {
    g_new_scene = data->dest_scene;
    return;
  }
}

// 다음 화면, 슬라이드 비트맵들, 비트맵 개수, 렌더링 위치를 받고 준비 시작
// 화면을 생성한 뒤 반환합니다.
GameScene* create_readystart_scene(GameScene* dest_scene,
                                   HBITMAP* slide_bitmaps, int size, Pos pos) {
  GameScene* scene = init_scene();

  ReadyStartData* data = malloc(sizeof(ReadyStartData));
  if (data == NULL) return NULL;
  data->dest_scene = dest_scene;
  data->slide_bitmaps = slide_bitmaps;
  data->slide_size = size;
  data->render_pos = pos;
  data->index = 0;
  scene->data = data;

  scene->on_render = on_render_readystart_scene;
  scene->sleep_duration = 1000;

  return scene;
}