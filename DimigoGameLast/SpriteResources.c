#include "SpriteResources.h"

#include "resource.h"

void init_sprite_resources(HINSTANCE inst) {
  cape_char1_sprites = malloc(sizeof(HBITMAP) * 1);
  if (cape_char1_sprites == NULL) return;
  cape_char1_sprites[0] = LoadBitmap(inst, MAKEINTRESOURCE(IDB_CAPE_CHAR1));
}

void deinit_sprite_resources() {
  DeleteObject(cape_char1_sprites[0]);
  free(cape_char1_sprites);
}