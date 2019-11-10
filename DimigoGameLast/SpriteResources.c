#include "SpriteResources.h"

#include "resource.h"

void init_sprite_resources(HINSTANCE inst) {
  dingding_sprites = malloc(sizeof(HBITMAP) * 3);
  if (dingding_sprites == NULL) return;
  dingding_sprites[0] =
      LoadBitmap(inst, MAKEINTRESOURCE(IDB_DINGDING_STANDING));
  dingding_sprites[1] =
      LoadBitmap(inst, MAKEINTRESOURCE(IDB_DINGDING_CHEERING));
  dingding_sprites[2] =
      LoadBitmap(inst, MAKEINTRESOURCE(IDB_DINGDING_THROWING));

  coco_sprites = malloc(sizeof(HBITMAP) * 3);
  if (coco_sprites == NULL) return;
  coco_sprites[0] = LoadBitmap(inst, MAKEINTRESOURCE(IDB_COCO_STANDING));
  coco_sprites[1] = LoadBitmap(inst, MAKEINTRESOURCE(IDB_COCO_CHEERING));
  coco_sprites[2] = LoadBitmap(inst, MAKEINTRESOURCE(IDB_COCO_THROWING));

  background_sprites = malloc(sizeof(HBITMAP) * 3);
  if (background_sprites == NULL) return;
  background_sprites[0] =
      LoadBitmap(inst, MAKEINTRESOURCE(IDB_DISK_BACKGROUND));
  background_sprites[1] = LoadBitmap(inst, MAKEINTRESOURCE(IDB_SKY_BACKGROUND));
  background_sprites[2] =
      LoadBitmap(inst, MAKEINTRESOURCE(IDB_PULL_BACKGROUND));

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
  game_help_sprites[0] = LoadBitmap(inst, MAKEINTRESOURCE(IDB_DISK_HELP));
  game_help_sprites[1] = LoadBitmap(inst, MAKEINTRESOURCE(IDB_PULL_HELP));

  ready_start_sprites = malloc(sizeof(HBITMAP) * 2);
  if (ready_start_sprites == NULL) return;
  ready_start_sprites[0] = LoadBitmap(inst, MAKEINTRESOURCE(IDB_READY));
  ready_start_sprites[1] = LoadBitmap(inst, MAKEINTRESOURCE(IDB_START));

  coco_disk_sprites = malloc(sizeof(HBITMAP) * 4);
  if (coco_disk_sprites == NULL) return;
  coco_disk_sprites[0] = LoadBitmap(inst, MAKEINTRESOURCE(IDB_COCO_DISK1));
  coco_disk_sprites[1] = LoadBitmap(inst, MAKEINTRESOURCE(IDB_COCO_DISK2));
  coco_disk_sprites[2] = LoadBitmap(inst, MAKEINTRESOURCE(IDB_COCO_DISK3));
  coco_disk_sprites[3] = LoadBitmap(inst, MAKEINTRESOURCE(IDB_COCO_DISK4));

  dingding_disk_sprites = malloc(sizeof(HBITMAP) * 4);
  if (dingding_disk_sprites == NULL) return NULL;
  dingding_disk_sprites[0] =
      LoadBitmap(inst, MAKEINTRESOURCE(IDB_DINGDING_DISK1));
  dingding_disk_sprites[1] =
      LoadBitmap(inst, MAKEINTRESOURCE(IDB_DINGDING_DISK2));
  dingding_disk_sprites[2] =
      LoadBitmap(inst, MAKEINTRESOURCE(IDB_DINGDING_DISK3));
  dingding_disk_sprites[3] =
      LoadBitmap(inst, MAKEINTRESOURCE(IDB_DINGDING_DISK4));

  disk_shadow_sprites = malloc(sizeof(HBITMAP) * 1);
  disk_shadow_sprites[0] = LoadBitmap(inst, MAKEINTRESOURCE(IDB_DISK_SHADOW));

  coco_turn_sprites = malloc(sizeof(HBITMAP) * 3);
  if (coco_turn_sprites == NULL) return;
  coco_turn_sprites[0] = LoadBitmap(inst, MAKEINTRESOURCE(IDB_COCO_TURN));
  coco_turn_sprites[1] = LoadBitmap(inst, MAKEINTRESOURCE(IDB_READY));
  coco_turn_sprites[2] = LoadBitmap(inst, MAKEINTRESOURCE(IDB_NOW_BLOW));

  dingding_turn_sprites = malloc(sizeof(HBITMAP) * 3);
  if (dingding_turn_sprites == NULL) return;
  dingding_turn_sprites[0] =
      LoadBitmap(inst, MAKEINTRESOURCE(IDB_DINGDING_TURN));
  dingding_turn_sprites[1] = LoadBitmap(inst, MAKEINTRESOURCE(IDB_READY));
  dingding_turn_sprites[2] = LoadBitmap(inst, MAKEINTRESOURCE(IDB_NOW_BLOW));

  score_board_sprites = malloc(sizeof(HBITMAP) * 1);
  if (score_board_sprites == NULL) return;
  score_board_sprites[0] = LoadBitmap(inst, MAKEINTRESOURCE(IDB_SCORE_BOARD));

  string_sprites = malloc(sizeof(HBITMAP) * 1);
  if (string_sprites == NULL) return;
  string_sprites[0] = LoadBitmap(inst, MAKEINTRESOURCE(IDB_STRING));

  flag_sprites = malloc(sizeof(HBITMAP) * 2);
  if (flag_sprites == NULL) return;
  flag_sprites[0] = LoadBitmap(inst, MAKEINTRESOURCE(IDB_COCO_FLAG));
  flag_sprites[1] = LoadBitmap(inst, MAKEINTRESOURCE(IDB_DINGDING_FLAG));

  logo_sprites = malloc(sizeof(HBITMAP) * 2);
  if (logo_sprites == NULL) return;
  logo_sprites[0] = LoadBitmap(inst, MAKEINTRESOURCE(IDB_DISK_LOGO));
  logo_sprites[1] = LoadBitmap(inst, MAKEINTRESOURCE(IDB_PULL_LOGO));
}

void deinit_sprite_resources() {
  DeleteObject(dingding_sprites[0]);
  DeleteObject(dingding_sprites[1]);
  DeleteObject(dingding_sprites[2]);
  free(dingding_sprites);

  DeleteObject(coco_sprites[0]);
  DeleteObject(coco_sprites[1]);
  DeleteObject(coco_sprites[2]);
  free(coco_sprites);

  DeleteObject(background_sprites[0]);
  free(background_sprites);

  DeleteObject(spit_sprites[0]);
  free(spit_sprites);

  DeleteObject(finish_flag_sprites[0]);
  free(finish_flag_sprites);

  DeleteObject(won_message_sprites[0]);
  DeleteObject(won_message_sprites[1]);
  free(won_message_sprites);

  DeleteObject(game_help_sprites[0]);
  DeleteObject(game_help_sprites[1]);
  free(game_help_sprites);

  DeleteObject(ready_start_sprites[0]);
  DeleteObject(ready_start_sprites[1]);
  free(ready_start_sprites);

  DeleteObject(coco_disk_sprites[0]);
  DeleteObject(coco_disk_sprites[1]);
  DeleteObject(coco_disk_sprites[2]);
  DeleteObject(coco_disk_sprites[3]);
  free(coco_disk_sprites);

  DeleteObject(dingding_disk_sprites[0]);
  DeleteObject(dingding_disk_sprites[1]);
  DeleteObject(dingding_disk_sprites[2]);
  DeleteObject(dingding_disk_sprites[3]);
  free(dingding_disk_sprites);

  DeleteObject(disk_shadow_sprites[0]);
  free(disk_shadow_sprites);

  DeleteObject(coco_turn_sprites[0]);
  DeleteObject(coco_turn_sprites[1]);
  DeleteObject(coco_turn_sprites[2]);
  free(coco_turn_sprites);

  DeleteObject(dingding_turn_sprites[0]);
  DeleteObject(dingding_turn_sprites[1]);
  DeleteObject(dingding_turn_sprites[2]);
  free(dingding_turn_sprites);

  DeleteObject(score_board_sprites[0]);
  free(score_board_sprites);

  DeleteObject(string_sprites[0]);
  free(string_sprites);

  DeleteObject(flag_sprites[0]);
  DeleteObject(flag_sprites[1]);
  free(flag_sprites);

  DeleteObject(logo_sprites[0]);
  DeleteObject(logo_sprites[1]);
  free(logo_sprites);
}