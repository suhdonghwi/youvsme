#include <stdio.h>

#include "SetScore.h"

// 세트 스코어 데이터를 로딩합니다.
void load_set_score() {
  FILE* data = fopen("score.dat", "r");
  if (data == NULL) {
    save_set_score();
    data = fopen("score.dat", "r");
  }
  fscanf(data, "%d %d", &g_coco_set_score, &g_dingding_set_score);
}

// 현재 세트 스코어 데이터를 저장합니다.
void save_set_score() {
  FILE* data = fopen("score.dat", "w");
  if (data == NULL) return;
  fprintf(data, "%d %d", g_coco_set_score, g_dingding_set_score);
}

// 게임 결과를 bool 형식으로 받아서 세트 스코어를 갱신합니다.
void update_set_score(bool coco_win) {
  if (coco_win)
    g_coco_set_score++;
  else
    g_dingding_set_score++;

  save_set_score();
}
