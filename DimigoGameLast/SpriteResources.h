#pragma once
#include <Windows.h>

HBITMAP* player1_sprites;
HBITMAP* player2_sprites;
HBITMAP* cape_background_sprites;
HBITMAP* spit_sprites;

void init_sprite_resources(HINSTANCE inst);
void deinit_sprite_resources();
