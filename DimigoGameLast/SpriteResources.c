#include "SpriteResources.h"

#include "resource.h"

void init_sprite_resources(HINSTANCE inst) {
  dingding_sprites = malloc(sizeof(HBITMAP) * 9);
  if (dingding_sprites == NULL) return;
  dingding_sprites[0] =
      LoadBitmap(inst, MAKEINTRESOURCE(IDB_DINGDING_STANDING));
  dingding_sprites[1] =
      LoadBitmap(inst, MAKEINTRESOURCE(IDB_DINGDING_CHEERING));
  dingding_sprites[2] =
      LoadBitmap(inst, MAKEINTRESOURCE(IDB_DINGDING_THROWING));
  dingding_sprites[3] = LoadBitmap(inst, MAKEINTRESOURCE(IDB_DINGDING_CRYING));
  dingding_sprites[4] =
      LoadBitmap(inst, MAKEINTRESOURCE(IDB_DINGDING_DANCE_UP));
  dingding_sprites[5] =
      LoadBitmap(inst, MAKEINTRESOURCE(IDB_DINGDING_DANCE_RIGHT));
  dingding_sprites[6] =
      LoadBitmap(inst, MAKEINTRESOURCE(IDB_DINGDING_DANCE_DOWN));
  dingding_sprites[7] =
      LoadBitmap(inst, MAKEINTRESOURCE(IDB_DINGDING_DANCE_LEFT));
  dingding_sprites[8] =
      LoadBitmap(inst, MAKEINTRESOURCE(IDB_DINGDING_STANDING_DARK));

  coco_sprites = malloc(sizeof(HBITMAP) * 9);
  if (coco_sprites == NULL) return;
  coco_sprites[0] = LoadBitmap(inst, MAKEINTRESOURCE(IDB_COCO_STANDING));
  coco_sprites[1] = LoadBitmap(inst, MAKEINTRESOURCE(IDB_COCO_CHEERING));
  coco_sprites[2] = LoadBitmap(inst, MAKEINTRESOURCE(IDB_COCO_THROWING));
  coco_sprites[3] = LoadBitmap(inst, MAKEINTRESOURCE(IDB_COCO_CRYING));
  coco_sprites[4] = LoadBitmap(inst, MAKEINTRESOURCE(IDB_COCO_DANCE_UP));
  coco_sprites[5] = LoadBitmap(inst, MAKEINTRESOURCE(IDB_COCO_DANCE_RIGHT));
  coco_sprites[6] = LoadBitmap(inst, MAKEINTRESOURCE(IDB_COCO_DANCE_DOWN));
  coco_sprites[7] = LoadBitmap(inst, MAKEINTRESOURCE(IDB_COCO_DANCE_LEFT));
  coco_sprites[8] = LoadBitmap(inst, MAKEINTRESOURCE(IDB_COCO_STANDING_DARK));

  background_sprites = malloc(sizeof(HBITMAP) * 6);
  if (background_sprites == NULL) return;
  background_sprites[0] =
      LoadBitmap(inst, MAKEINTRESOURCE(IDB_DISK_BACKGROUND));
  background_sprites[1] = LoadBitmap(inst, MAKEINTRESOURCE(IDB_SKY_BACKGROUND));
  background_sprites[2] =
      LoadBitmap(inst, MAKEINTRESOURCE(IDB_PULL_BACKGROUND));
  background_sprites[3] =
      LoadBitmap(inst, MAKEINTRESOURCE(IDB_DANCE_BACKGROUND));
  background_sprites[4] =
      LoadBitmap(inst, MAKEINTRESOURCE(IDB_DANCE_BACKGROUND_RIGHT));
  background_sprites[5] =
      LoadBitmap(inst, MAKEINTRESOURCE(IDB_DANCE_BACKGROUND_LEFT));

  won_message_sprites = malloc(sizeof(HBITMAP) * 2);
  if (won_message_sprites == NULL) return;
  won_message_sprites[0] = LoadBitmap(inst, MAKEINTRESOURCE(IDB_COCO_WON));
  won_message_sprites[1] = LoadBitmap(inst, MAKEINTRESOURCE(IDB_DINGDING_WON));

  game_help_sprites = malloc(sizeof(HBITMAP) * 3);
  if (game_help_sprites == NULL) return;
  game_help_sprites[0] = LoadBitmap(inst, MAKEINTRESOURCE(IDB_DISK_HELP));
  game_help_sprites[1] = LoadBitmap(inst, MAKEINTRESOURCE(IDB_PULL_HELP));
  game_help_sprites[2] = LoadBitmap(inst, MAKEINTRESOURCE(IDB_TEACHER_HELP));

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

  sign_sprites = malloc(sizeof(HBITMAP) * 2);
  if (sign_sprites == NULL) return;
  sign_sprites[0] = LoadBitmap(inst, MAKEINTRESOURCE(IDB_OK));
  sign_sprites[1] = LoadBitmap(inst, MAKEINTRESOURCE(IDB_WRONG));

  progress_sprites = malloc(sizeof(HBITMAP) * 11);
  if (progress_sprites == NULL) return;
  progress_sprites[0] = LoadBitmap(inst, MAKEINTRESOURCE(IDB_PROGRESS_0));
  progress_sprites[1] = LoadBitmap(inst, MAKEINTRESOURCE(IDB_PROGRESS_1));
  progress_sprites[2] = LoadBitmap(inst, MAKEINTRESOURCE(IDB_PROGRESS_2));
  progress_sprites[3] = LoadBitmap(inst, MAKEINTRESOURCE(IDB_PROGRESS_3));
  progress_sprites[4] = LoadBitmap(inst, MAKEINTRESOURCE(IDB_PROGRESS_4));
  progress_sprites[5] = LoadBitmap(inst, MAKEINTRESOURCE(IDB_PROGRESS_5));
  progress_sprites[6] = LoadBitmap(inst, MAKEINTRESOURCE(IDB_PROGRESS_6));
  progress_sprites[7] = LoadBitmap(inst, MAKEINTRESOURCE(IDB_PROGRESS_7));
  progress_sprites[8] = LoadBitmap(inst, MAKEINTRESOURCE(IDB_PROGRESS_8));
  progress_sprites[9] = LoadBitmap(inst, MAKEINTRESOURCE(IDB_PROGRESS_9));
  progress_sprites[10] = LoadBitmap(inst, MAKEINTRESOURCE(IDB_PROGRESS_10));

  story_sprites = malloc(sizeof(HBITMAP) * 2);
  if (story_sprites == NULL) return;
  story_sprites[0] = LoadBitmap(inst, MAKEINTRESOURCE(IDB_STORY_TIMETABLE));
  story_sprites[1] = LoadBitmap(inst, MAKEINTRESOURCE(IDB_STORY_FIRST));

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
  free(dingding_sprites);
  free(coco_sprites);
  free(background_sprites);
  free(won_message_sprites);
  free(game_help_sprites);
  free(ready_start_sprites);
  free(coco_disk_sprites);
  free(dingding_disk_sprites);
  free(disk_shadow_sprites);
  free(disk_line_sprites);
  free(score_board_sprites);
  free(string_sprites);
  free(flag_sprites);
  free(logo_sprites);
  free(ment_sprites);
  free(key_sprites);
  free(sign_sprites);
  free(progress_sprites);
  free(story_sprites);
  free(coco_disk_ready_sprites);
  free(dingding_disk_ready_sprites);
  free(pull_ready_sprites);
}