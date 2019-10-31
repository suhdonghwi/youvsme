#pragma once
#include <Windows.h>
#include <mmsystem.h>

// ���� ������ ���� �����͵��� �����ϴ� ����ü�Դϴ�.
typedef struct tagWaveData {
  int num_pts;
  int sample_rate;
  short int* sample_data;

  HWAVEIN wave_in;
  WAVEHDR wave_hdr;
  WAVEFORMATEX wave_format;
} WaveData;

// ���� ������ ���ؼ� WaveData ����ü�� �ʱ�ȭ�ϰ� ���۸� �غ��Ͽ� result��
// �ֽ��ϴ�. ���������� ����Ǹ� 0, ������������ ����Ǹ� 1�� ��ȯ�մϴ�.
int init_wave_data(WaveData* result);

// WaveData ����� ������ �� �޸� �Ҵ��� ������Ű�� �Լ��Դϴ�.
void deinit_wave_data(WaveData wave_data);

// WaveData�� �ް� 0.1�� ���� ������ �� �� ���� ����ũ ���� ������ 0���� 1
// ������ ������ result�� �ֽ��ϴ�. ���������� ����Ǹ� 0, ������������ ����Ǹ�
// 1�� ��ȯ�մϴ�.
int get_current_volume(WaveData wave_data, double* result);
