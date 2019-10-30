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

// ���� ������ ���ؼ� WaveData ����ü�� �ʱ�ȭ�ϰ� ���۸� �غ��ϴ� �Լ��Դϴ�.
WaveData init_wave_data();

// WaveData ����� ������ �� �޸� �Ҵ��� ������Ű�� �Լ��Դϴ�.
void deinit_wave_data(WaveData wave_data);

// WaveData�� �ް� 0.1�� ���� ������ �� �� ���� ����ũ ���� ������ 0���� 1
// ������ ������ ��ȯ�ϴ� �Լ��Դϴ�.
double get_current_volume(WaveData wave_data);
