#pragma once
#include <Windows.h>

HBITMAP* player1_sprites;
HBITMAP* player2_sprites;
HBITMAP* cape_background_sprites;
HBITMAP* spit_sprites;
HBITMAP* finish_flag_sprites;
HBITMAP* won_message_sprites;
HBITMAP* game_help_sprites;
HBITMAP* ready_start_sprites;

void init_sprite_resources(HINSTANCE inst);
void deinit_sprite_resources();
