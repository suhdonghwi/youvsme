#pragma once
#include <stdio.h>

#include "WaveAudio.h"

WaveData init_wave_data() {
  WaveData wave_data;
  wave_data.num_pts = 8100 / 10;
  wave_data.sample_rate = 8100;
  wave_data.sample_data = malloc(sizeof(short int) * wave_data.num_pts);

  // Set up and prepare header for input
  wave_data.wave_hdr.lpData = (LPSTR)wave_data.sample_data;
  wave_data.wave_hdr.dwBufferLength = wave_data.num_pts;
  wave_data.wave_hdr.dwBytesRecorded = 0;
  wave_data.wave_hdr.dwUser = 0L;
  wave_data.wave_hdr.dwFlags = 0L;
  wave_data.wave_hdr.dwLoops = 0L;

  wave_data.wave_format.wFormatTag = WAVE_FORMAT_PCM;
  wave_data.wave_format.nChannels = 1;
  wave_data.wave_format.nSamplesPerSec = wave_data.sample_rate;
  wave_data.wave_format.nAvgBytesPerSec = wave_data.sample_rate * 2;
  wave_data.wave_format.nBlockAlign = 2;
  wave_data.wave_format.wBitsPerSample = 16;
  wave_data.wave_format.cbSize = 0;

  MMRESULT result =
      waveInOpen(&wave_data.wave_in, WAVE_MAPPER, &wave_data.wave_format, 0L,
                 0L, WAVE_FORMAT_DIRECT);
  if (result) {
    char fault[256];
    waveInGetErrorText(result, fault, 256);
    printf("Failed to open waveform input device : %s\n", fault);
  }

  return wave_data;
}

void deinit_wave_data(WaveData wave_data) {
  free(wave_data.sample_data);
  waveInClose(wave_data.wave_in);
}

double get_current_volume(WaveData wave_data) {
  waveInPrepareHeader(wave_data.wave_in, &wave_data.wave_hdr, sizeof(WAVEHDR));

  // Insert a wave input buffer
  if (waveInAddBuffer(wave_data.wave_in, &wave_data.wave_hdr,
                      sizeof(WAVEHDR))) {
    printf("Failed to read block from device\n");
    return 0;
  }

  // Commence sampling input
  if (waveInStart(wave_data.wave_in)) {
    printf("Failed to start recording\n");
    return 0;
  }

  Sleep((DWORD)((wave_data.num_pts / (double)wave_data.sample_rate) *
                1000));  // Sleep while recording

  waveInUnprepareHeader(wave_data.wave_in, &wave_data.wave_hdr,
                        sizeof(WAVEHDR));

  short int max = 0;
  for (int i = 0; i < wave_data.num_pts; i++) {
    short int data = wave_data.sample_data[i];
    if (data > max) {
      max = data;
    }
  }

  return max / 32767.0;
}
