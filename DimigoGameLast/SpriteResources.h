#pragma once
#include <Windows.h>

HBITMAP* dingding_sprites;
HBITMAP* coco_sprites;
HBITMAP* background_sprites;
HBITMAP* spit_sprites;
HBITMAP* finish_flag_sprites;
HBITMAP* won_message_sprites;
HBITMAP* game_help_sprites;
HBITMAP* ready_start_sprites;
HBITMAP* plane_sprites;
HBITMAP* coco_turn_sprites;
HBITMAP* dingding_turn_sprites;
HBITMAP* score_board_sprites;

void init_sprite_resources(HINSTANCE inst);
void deinit_sprite_resources();
