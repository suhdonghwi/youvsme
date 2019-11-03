#include "SpriteResources.h"

#include "resource.h"

void init_sprite_resources(HINSTANCE inst) {
  player1_sprites = malloc(sizeof(HBITMAP) * 3);
  if (player1_sprites == NULL) return;
  player1_sprites[0] = LoadBitmap(inst, MAKEINTRESOURCE(IDB_PLAYER1_STANDING));
  player1_sprites[1] = LoadBitmap(inst, MAKEINTRESOURCE(IDB_PLAYER1_CHEERING));
  player1_sprites[2] = LoadBitmap(inst, MAKEINTRESOURCE(IDB_CAPE_PLAYER1));

  player2_sprites = malloc(sizeof(HBITMAP) * 3);
  if (player2_sprites == NULL) return;
  player2_sprites[0] = LoadBitmap(inst, MAKEINTRESOURCE(IDB_PLAYER2_STANDING));
  player2_sprites[1] = LoadBitmap(inst, MAKEINTRESOURCE(IDB_PLAYER2_CHEERING));
  player2_sprites[2] = LoadBitmap(inst, MAKEINTRESOURCE(IDB_CAPE_PLAYER2));

  cape_background_sprites = malloc(sizeof(HBITMAP) * 1);
  if (cape_background_sprites == NULL) return;
  cape_background_sprites[0] =
      LoadBitmap(inst, MAKEINTRESOURCE(IDB_CAPE_BACKGROUND));

  spit_sprites = malloc(sizeof(HBITMAP) * 1);
  if (spit_sprites == NULL) return;
  spit_sprites[0] = LoadBitmap(inst, MAKEINTRESOURCE(IDB_SPIT));

  finish_flag_sprites = malloc(sizeof(HBITMAP) * 1);
  if (finish_flag_sprites == NULL) return;
  finish_flag_sprites[0] = LoadBitmap(inst, MAKEINTRESOURCE(IDB_FINISH_FLAG));

  won_message_sprites = malloc(sizeof(HBITMAP) * 2);
  if (won_message_sprites == NULL) return;
  won_message_sprites[0] = LoadBitmap(inst, MAKEINTRESOURCE(IDB_COCO_WON));
  won_message_sprites[1] = LoadBitmap(inst, MAKEINTRESOURCE(IDB_DINGDING_WON));

  game_help_sprites = malloc(sizeof(HBITMAP) * 2);
  if (game_help_sprites == NULL) return;
  game_help_sprites[0] = LoadBitmap(inst, MAKEINTRESOURCE(IDB_BNA_HELP));
}

void deinit_sprite_resources() {
  DeleteObject(player1_sprites[0]);
  DeleteObject(player1_sprites[1]);
  DeleteObject(player1_sprites[2]);
  free(player1_sprites);

  DeleteObject(player2_sprites[0]);
  DeleteObject(player2_sprites[1]);
  DeleteObject(player2_sprites[2]);
  free(player2_sprites);

  DeleteObject(cape_background_sprites[0]);
  free(cape_background_sprites);

  DeleteObject(spit_sprites[0]);
  free(spit_sprites);

  DeleteObject(finish_flag_sprites[0]);
  free(finish_flag_sprites);

  DeleteObject(won_message_sprites[0]);
  DeleteObject(won_message_sprites[1]);
  free(won_message_sprites);

  DeleteObject(game_help_sprites[0]);
  free(game_help_sprites);
}