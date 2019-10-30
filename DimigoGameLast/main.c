#include <Windows.h>
#include <mmsystem.h>
#include <stdio.h>

#define NUMPTS 810

double current_volume(int numPts, int sampleRate, HWAVEIN hWaveIn,
                      short int* waveIn, WAVEHDR waveInHdr) {
  sizeof(WAVEHDR);
  waveInPrepareHeader(hWaveIn, &waveInHdr, sizeof(WAVEHDR));

  // Insert a wave input buffer
  if (waveInAddBuffer(hWaveIn, &waveInHdr, sizeof(WAVEHDR))) {
    printf("Failed to read block from device\n");
    return 0;
  }

  printf("Recording...");

  // Commence sampling input
  if (waveInStart(hWaveIn)) {
    printf("Failed to start recording\n");
    return 0;
  }

  Sleep(
      (DWORD)((numPts / (double)sampleRate) * 1000));  // Sleep while recording

  waveInUnprepareHeader(hWaveIn, &waveInHdr, sizeof(WAVEHDR));

  short int max = 0;
  for (int i = 0; i < numPts; i++) {
    short int data = waveIn[i];
    if (data > max) {
      max = data;
    }
  }

  return max / 32767.0;
}

int main() {
  int sampleRate = 8100;
  short int waveIn[NUMPTS];
  HWAVEIN hWaveIn;
  WAVEHDR WaveInHdr;

  // Specify recording parameters
  WAVEFORMATEX pFormat;
  pFormat.wFormatTag = WAVE_FORMAT_PCM;  // simple, uncompressed format
  pFormat.nChannels = 1;                 //  1=mono, 2=stereo
  pFormat.nSamplesPerSec = sampleRate;   // 44100
  pFormat.nAvgBytesPerSec =
      sampleRate * 2;       // = nSamplesPerSec * n.Channels * wBitsPerSample/8
  pFormat.nBlockAlign = 2;  // = n.Channels * wBitsPerSample/8
  pFormat.wBitsPerSample = 16;  //  16 for high quality, 8 for telephone-grade
  pFormat.cbSize = 0;

  MMRESULT result =
      waveInOpen(&hWaveIn, WAVE_MAPPER, &pFormat, 0L, 0L, WAVE_FORMAT_DIRECT);
  if (result) {
    char fault[256];
    waveInGetErrorText(result, fault, 256);
    printf("Failed to open waveform input device : %s\n", fault);
    return 1;
  }

  // Set up and prepare header for input
  WaveInHdr.lpData = (LPSTR)waveIn;
  WaveInHdr.dwBufferLength = NUMPTS;
  WaveInHdr.dwBytesRecorded = 0;
  WaveInHdr.dwUser = 0L;
  WaveInHdr.dwFlags = 0L;
  WaveInHdr.dwLoops = 0L;

  for (int i = 0; i < 100; i++) {
    printf("%lf\n",
           current_volume(NUMPTS, sampleRate, hWaveIn, waveIn, WaveInHdr));
  }

  waveInClose(hWaveIn);

  system("pause");
}