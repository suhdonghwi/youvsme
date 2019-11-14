#pragma once
#include <Windows.h>

HBITMAP* dingding_sprites;
HBITMAP* coco_sprites;
HBITMAP* background_sprites;
HBITMAP* won_message_sprites;
HBITMAP* game_help_sprites;
HBITMAP* ready_start_sprites;
HBITMAP* coco_disk_sprites;
HBITMAP* dingding_disk_sprites;
HBITMAP* disk_shadow_sprites;
HBITMAP* disk_line_sprites;
HBITMAP* score_board_sprites;
HBITMAP* string_sprites;
HBITMAP* flag_sprites;
HBITMAP* logo_sprites;
HBITMAP* ment_sprites;
HBITMAP* key_sprites;
HBITMAP* sign_sprites;
HBITMAP* progress_sprites;
HBITMAP* story_sprites;

HBITMAP* coco_disk_ready_sprites;
HBITMAP* dingding_disk_ready_sprites;
HBITMAP* pull_ready_sprites;

void init_sprite_resources(HINSTANCE inst);
void deinit_sprite_resources();
