#pragma once
#include <stdio.h>

#include "WaveAudio.h"

int init_wave_data(WaveData* result) {
  result->num_pts = 8100 * 30;
  result->sample_rate = 8100;
  result->sample_data = malloc(sizeof(short int) * result->num_pts);

  // Set up and prepare header for input
  result->wave_hdr.lpData = (LPSTR)result->sample_data;
  result->wave_hdr.dwBufferLength = result->num_pts;
  result->wave_hdr.dwBytesRecorded = 0;
  result->wave_hdr.dwUser = 0L;
  result->wave_hdr.dwFlags = 0L;
  result->wave_hdr.dwLoops = 0L;

  result->wave_format.wFormatTag = WAVE_FORMAT_PCM;
  result->wave_format.nChannels = 1;
  result->wave_format.nSamplesPerSec = result->sample_rate;
  result->wave_format.nAvgBytesPerSec = result->sample_rate * 2;
  result->wave_format.nBlockAlign = 2;
  result->wave_format.wBitsPerSample = 16;
  result->wave_format.cbSize = 0;

  MMRESULT open_result =
      waveInOpen(&result->wave_in, WAVE_MAPPER, &result->wave_format, 0L, 0L,
                 WAVE_FORMAT_DIRECT);
  if (open_result) {
    char fault[256];
    waveInGetErrorText(open_result, fault, 256);
    printf("오디오 입력 장치를 열 수 없습니다. : %s\n", fault);
    return 1;
  }

  waveInPrepareHeader(result->wave_in, &result->wave_hdr, sizeof(WAVEHDR));

  if (waveInAddBuffer(result->wave_in, &result->wave_hdr, sizeof(WAVEHDR))) {
    printf("장치로부터 오디오 버퍼 데이터를 읽을 수 없습니다.\n");
    return 1;
  }

  if (waveInStart(result->wave_in)) {
    printf("오디오 녹음을 시작할 수 없습니다.\n");
    return 1;
  }

  return 0;
}

void deinit_wave_data(WaveData wave_data) {
  free(wave_data.sample_data);
  waveInClose(wave_data.wave_in);
}

int get_current_volume(WaveData wave_data, double* result) {
  // Sleep((DWORD)((wave_data.num_pts / (double)wave_data.sample_rate) * 1000));
  while (waveInUnprepareHeader(wave_data.wave_in, &wave_data.wave_hdr,
                               sizeof(WAVEHDR)) == WAVERR_STILLPLAYING) {
    printf("%d\n", wave_data.sample_data[wave_data.wave_hdr.dwBytesRecorded]);
  }

  short int max = 0;
  for (int i = 0; i < wave_data.num_pts; i++) {
    short int data = wave_data.sample_data[i];
    if (data > max) {
      max = data;
    }
  }

  *result = max / 32767.0;
  return 0;
}
