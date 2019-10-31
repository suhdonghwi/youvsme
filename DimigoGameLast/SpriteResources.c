#include "SpriteResources.h"

#include "resource.h"

void init_sprite_resources(HINSTANCE inst) {
  bird_sprites = malloc(sizeof(HBITMAP) * 1);
  bird_sprites[0] = LoadBitmap(inst, MAKEINTRESOURCE(IDB_BIRD));
}

void deinit_sprite_resources() {
  DeleteObject(bird_sprites[0]);
  free(bird_sprites);
}