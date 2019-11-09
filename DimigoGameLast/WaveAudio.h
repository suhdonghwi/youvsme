#pragma once
#include <Windows.h>
#include <mmsystem.h>

// 음성 녹음을 위한 데이터들을 저장하는 구조체입니다.
typedef struct tagWaveData {
  int num_pts;
  int sample_rate;
  short int* sample_data;

  HWAVEIN wave_in;
  WAVEHDR wave_hdr;
  WAVEFORMATEX wave_format;
} WaveData;

// 음성 녹음을 위해서 WaveData 구조체를 초기화하고 버퍼를 준비하여 result에
// 넣습니다. 정상적으로 종료되면 0, 비정상적으로 종료되면 1을 반환합니다.
int init_wave_data(WaveData* result, int record_seconds);

// WaveData 사용을 마쳤을 때 메모리 할당을 해제시키는 함수입니다.
void deinit_wave_data(WaveData* wave_data);
