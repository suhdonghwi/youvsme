#include <stdio.h>

#include <Windows.h>
#include <mmsystem.h>
#include <vfw.h>

#include "Camera.h"
#include "WaveAudio.h"

int main() {
  /*CameraData camera_data = init_camera_data();
  while (1) {
    printf("%d\n", get_current_color(camera_data));
  }*/

  WaveData wave_data;
  init_wave_data(&wave_data);

  for (int i = 0; i < 100; i++) {
    double volume;
    get_current_volume(wave_data, &volume);
    printf("%lf\n", volume);
  }

  deinit_wave_data(wave_data);
  system("pause");
}