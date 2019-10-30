#include <Windows.h>
#include <mmsystem.h>
#include <stdio.h>

#define NUMPTS 810

int main() {
  int sampleRate = 8100;
  short int waveIn[NUMPTS];
  HWAVEIN hWaveIn;
  WAVEHDR WaveInHdr;
  MMRESULT result;

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

  result =
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

  for (int i = 0; i < 1000; i++) {
    waveInPrepareHeader(hWaveIn, &WaveInHdr, sizeof(WAVEHDR));

    // Insert a wave input buffer
    result = waveInAddBuffer(hWaveIn, &WaveInHdr, sizeof(WAVEHDR));
    if (result) {
      printf("Failed to read blcok from device\n");
      return 1;
    }

    printf("Recording...");

    // Commence sampling input
    result = waveInStart(hWaveIn);
    if (result) {
      printf("Failed to start recording\n");
      return;
    }

    Sleep((NUMPTS / (double)sampleRate) * 1000);  // Sleep while recording

    short int max = 0;
    for (int j = 0; j < NUMPTS; j++) {
      if (waveIn[j] > max) {
        max = waveIn[j];
      }
    }

    printf("%lf\n", max / 32767.0);

    waveInUnprepareHeader(hWaveIn, &WaveInHdr, sizeof(WAVEHDR));
  }

  waveInClose(hWaveIn);

  system("pause");
}