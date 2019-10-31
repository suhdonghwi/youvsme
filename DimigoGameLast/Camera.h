#pragma once
#include <Windows.h>

typedef struct tagCameraData {
  HWND camera_window;
  HDC monitor_dc;
} CameraData;

typedef enum tagColor { COLOR_RED, COLOR_BLUE, COLOR_OTHER } Color;

CameraData init_camera_data();
RECT get_camera_rect(CameraData camera_data);
Color get_current_color(CameraData camera_data);
