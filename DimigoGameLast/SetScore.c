#include <stdio.h>

#include "SetScore.h"

// ��Ʈ ���ھ� �����͸� �ε��մϴ�.
void load_set_score() {
  FILE* data = fopen("score.dat", "r");
  if (data == NULL) {
    save_set_score();
    data = fopen("score.dat", "r");
  }
  fscanf(data, "%d %d", &g_coco_set_score, &g_dingding_set_score);
}

// ���� ��Ʈ ���ھ� �����͸� �����մϴ�.
void save_set_score() {
  FILE* data = fopen("score.dat", "w");
  if (data == NULL) return;
  fprintf(data, "%d %d", g_coco_set_score, g_dingding_set_score);
}

// ���� ����� bool �������� �޾Ƽ� ��Ʈ ���ھ �����մϴ�.
void update_set_score(bool coco_win) {
  if (coco_win)
    g_coco_set_score++;
  else
    g_dingding_set_score++;

  save_set_score();
}
