#include "SpriteResources.h"

#include "resource.h"

void init_sprite_resources(HINSTANCE inst) {
  dingding_sprites = malloc(sizeof(HBITMAP) * 4);
  if (dingding_sprites == NULL) return;
  dingding_sprites[0] =
      LoadBitmap(inst, MAKEINTRESOURCE(IDB_DINGDING_STANDING));
  dingding_sprites[1] =
      LoadBitmap(inst, MAKEINTRESOURCE(IDB_DINGDING_CHEERING));
  dingding_sprites[2] =
      LoadBitmap(inst, MAKEINTRESOURCE(IDB_DINGDING_THROWING));
  dingding_sprites[3] = LoadBitmap(inst, MAKEINTRESOURCE(IDB_DINGDING_CRYING));

  coco_sprites = malloc(sizeof(HBITMAP) * 4);
  if (coco_sprites == NULL) return;
  coco_sprites[0] = LoadBitmap(inst, MAKEINTRESOURCE(IDB_COCO_STANDING));
  coco_sprites[1] = LoadBitmap(inst, MAKEINTRESOURCE(IDB_COCO_CHEERING));
  coco_sprites[2] = LoadBitmap(inst, MAKEINTRESOURCE(IDB_COCO_THROWING));
  coco_sprites[3] = LoadBitmap(inst, MAKEINTRESOURCE(IDB_COCO_CRYING));

  background_sprites = malloc(sizeof(HBITMAP) * 3);
  if (background_sprites == NULL) return;
  background_sprites[0] =
      LoadBitmap(inst, MAKEINTRESOURCE(IDB_DISK_BACKGROUND));
  background_sprites[1] = LoadBitmap(inst, MAKEINTRESOURCE(IDB_SKY_BACKGROUND));
  background_sprites[2] =
      LoadBitmap(inst, MAKEINTRESOURCE(IDB_PULL_BACKGROUND));

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
  if (dingding_disk_sprites == NULL) return;
  dingding_disk_sprites[0] =
      LoadBitmap(inst, MAKEINTRESOURCE(IDB_DINGDING_DISK1));
  dingding_disk_sprites[1] =
      LoadBitmap(inst, MAKEINTRESOURCE(IDB_DINGDING_DISK2));
  dingding_disk_sprites[2] =
      LoadBitmap(inst, MAKEINTRESOURCE(IDB_DINGDING_DISK3));
  dingding_disk_sprites[3] =
      LoadBitmap(inst, MAKEINTRESOURCE(IDB_DINGDING_DISK4));

  disk_shadow_sprites = malloc(sizeof(HBITMAP) * 1);
  if (disk_shadow_sprites == NULL) return;
  disk_shadow_sprites[0] = LoadBitmap(inst, MAKEINTRESOURCE(IDB_DISK_SHADOW));

  disk_line_sprites = malloc(sizeof(HBITMAP) * 2);
  if (disk_line_sprites == NULL) return;
  disk_line_sprites[0] = LoadBitmap(inst, MAKEINTRESOURCE(IDB_DISK_LINE));
  disk_line_sprites[1] =
      LoadBitmap(inst, MAKEINTRESOURCE(IDB_DISK_CROSSED_LINE));

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

  ment_sprites = malloc(sizeof(HBITMAP) * 1);
  if (ment_sprites == NULL) return;
  ment_sprites[0] = LoadBitmap(inst, MAKEINTRESOURCE(IDB_NO_MENT));

  key_sprites = malloc(sizeof(HBITMAP) * 6);
  if (key_sprites == NULL) return;
  key_sprites[0] = LoadBitmap(inst, MAKEINTRESOURCE(IDB_KEY_1));
  key_sprites[1] = LoadBitmap(inst, MAKEINTRESOURCE(IDB_KEY_2));
  key_sprites[2] = LoadBitmap(inst, MAKEINTRESOURCE(IDB_KEY_3));
  key_sprites[3] = LoadBitmap(inst, MAKEINTRESOURCE(IDB_KEY_7));
  key_sprites[4] = LoadBitmap(inst, MAKEINTRESOURCE(IDB_KEY_8));
  key_sprites[5] = LoadBitmap(inst, MAKEINTRESOURCE(IDB_KEY_9));

  sign_sprites = malloc(sizeof(HBITMAP) * 1);
  if (sign_sprites == NULL) return;
  sign_sprites[0] = LoadBitmap(inst, MAKEINTRESOURCE(IDB_OK));

  coco_disk_ready_sprites = malloc(sizeof(HBITMAP) * 3);
  if (coco_disk_ready_sprites == NULL) return;
  coco_disk_ready_sprites[0] = LoadBitmap(inst, MAKEINTRESOURCE(IDB_COCO_TURN));
  coco_disk_ready_sprites[1] = LoadBitmap(inst, MAKEINTRESOURCE(IDB_READY));
  coco_disk_ready_sprites[2] = LoadBitmap(inst, MAKEINTRESOURCE(IDB_NOW_BLOW));

  dingding_disk_ready_sprites = malloc(sizeof(HBITMAP) * 3);
  if (dingding_disk_ready_sprites == NULL) return;
  dingding_disk_ready_sprites[0] =
      LoadBitmap(inst, MAKEINTRESOURCE(IDB_DINGDING_TURN));
  dingding_disk_ready_sprites[1] = LoadBitmap(inst, MAKEINTRESOURCE(IDB_READY));
  dingding_disk_ready_sprites[2] =
      LoadBitmap(inst, MAKEINTRESOURCE(IDB_NOW_BLOW));

  pull_ready_sprites = malloc(sizeof(HBITMAP) * 2);
  if (pull_ready_sprites == NULL) return;
  pull_ready_sprites[0] = LoadBitmap(inst, MAKEINTRESOURCE(IDB_READY));
  pull_ready_sprites[1] = LoadBitmap(inst, MAKEINTRESOURCE(IDB_START));
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

  DeleteObject(disk_line_sprites[0]);
  DeleteObject(disk_line_sprites[1]);
  free(disk_line_sprites);

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

  DeleteObject(ment_sprites[0]);
  free(ment_sprites);

  DeleteObject(key_sprites[0]);
  DeleteObject(key_sprites[1]);
  DeleteObject(key_sprites[2]);
  DeleteObject(key_sprites[3]);
  DeleteObject(key_sprites[4]);
  DeleteObject(key_sprites[5]);
  free(key_sprites);

  DeleteObject(sign_sprites[0]);
  free(sign_sprites);

  DeleteObject(coco_disk_ready_sprites[0]);
  DeleteObject(coco_disk_ready_sprites[1]);
  DeleteObject(coco_disk_ready_sprites[2]);
  free(coco_disk_ready_sprites);

  DeleteObject(dingding_disk_ready_sprites[0]);
  DeleteObject(dingding_disk_ready_sprites[1]);
  DeleteObject(dingding_disk_ready_sprites[2]);
  free(dingding_disk_ready_sprites);

  DeleteObject(pull_ready_sprites[0]);
  DeleteObject(pull_ready_sprites[1]);
  free(pull_ready_sprites);
}