#include "Camera.h"

#define GetRValue(rgb) ((BYTE)(rgb))
#define GetGValue(rgb) ((BYTE)(((WORD)(rgb)) >> 8))
#define GetBValue(rgb) ((BYTE)((rgb) >> 16))

CameraData init_camera_data() {
  CameraData result;
  result.camera_window = FindWindow(NULL, TEXT("Ä«¸Þ¶ó"));
  result.monitor_dc = GetDC(NULL);
  return result;
}

RECT get_camera_rect(CameraData camera_data) {
  RECT result;
  GetWindowRect(camera_data.camera_window, &result);
  return result;
}

Color get_current_color(CameraData camera_data) {
  RECT rect = get_camera_rect(camera_data);
  int center_x = (rect.left + rect.right) / 2,
      center_y = (rect.top + rect.bottom) / 2;

  int r_sum = 0, g_sum = 0, b_sum = 0;

  for (int x = center_x - 1; x <= center_x; x++) {
    for (int y = center_y - 1; y <= center_y; y++) {
      COLORREF ref = GetPixel(camera_data.monitor_dc, x, y);
      int r = GetRValue(ref), g = GetGValue(ref), b = GetBValue(ref);
      r_sum += r;
      g_sum += g;
      b_sum += b;
    }
  }

  printf("%d %d %d\n", r_sum, g_sum, b_sum);

  if (r_sum >= g_sum + 70 && r_sum >= b_sum + 70)
    return COLOR_RED;
  else if (b_sum >= r_sum + 70 && b_sum >= g_sum + 70)
    return COLOR_BLUE;
  else
    return COLOR_OTHER;
}