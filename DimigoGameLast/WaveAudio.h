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

// 음성 녹음을 위해서 WaveData 구조체를 초기화하고 버퍼를 준비하는 함수입니다.
WaveData init_wave_data();

// WaveData 사용을 마쳤을 때 메모리 할당을 해제시키는 함수입니다.
void deinit_wave_data(WaveData wave_data);

// WaveData를 받고 0.1초 동안 녹음을 한 뒤 현재 마이크 볼륨 레벨을 0에서 1
// 사이의 값으로 반환하는 함수입니다.
double get_current_volume(WaveData wave_data);
