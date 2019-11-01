#pragma once
#include <Windows.h>

HBITMAP* cape_char1_sprites;
HBITMAP* cape_background_sprites;

void init_sprite_resources(HINSTANCE inst);
void deinit_sprite_resources();
