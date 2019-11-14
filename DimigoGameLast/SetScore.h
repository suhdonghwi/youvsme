#pragma once
#include <stdbool.h>

int g_coco_set_score;
int g_dingding_set_score;

void load_set_score();
void save_set_score();
void update_set_score(bool coco_win);
