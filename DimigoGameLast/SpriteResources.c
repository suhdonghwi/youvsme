#include "SpriteResources.h"

#include "resource.h"

void init_sprite_resources(HINSTANCE inst) {
  cape_player1_sprites = malloc(sizeof(HBITMAP) * 1);
  if (cape_player1_sprites == NULL) return;
  cape_player1_sprites[0] = LoadBitmap(inst, MAKEINTRESOURCE(IDB_CAPE_PLAYER1));

  cape_player2_sprites = malloc(sizeof(HBITMAP) * 1);
  if (cape_player2_sprites == NULL) return;
  cape_player2_sprites[0] = LoadBitmap(inst, MAKEINTRESOURCE(IDB_CAPE_PLAYER2));

  cape_background_sprites = malloc(sizeof(HBITMAP) * 1);
  if (cape_background_sprites == NULL) return;
  cape_background_sprites[0] =
      LoadBitmap(inst, MAKEINTRESOURCE(IDB_CAPE_BACKGROUND));
}

void deinit_sprite_resources() {
  DeleteObject(cape_player1_sprites[0]);
  free(cape_player1_sprites);

  DeleteObject(cape_player2_sprites[0]);
  free(cape_player2_sprites);

  DeleteObject(cape_background_sprites[0]);
  free(cape_background_sprites);
}