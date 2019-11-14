#include "SetScore.h"

void load_set_score() {
  // TODO
}

void save_set_score() {
  // TODO
}

void update_set_score(bool coco_win) {
  if (coco_win)
    g_coco_set_score++;
  else
    g_dingding_set_score++;
}
