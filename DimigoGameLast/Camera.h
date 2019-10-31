#pragma once
#include <Windows.h>

typedef struct tagCameraData {
  HWND camera_window;
  HDC monitor_dc;
} CameraData;

typedef enum tagColor { COLOR_RED, COLOR_BLUE, COLOR_OTHER } Color;

// 카메라 데이터를 초기화하여 result에 저장합니다. 정상적으로 초기화되면 0,
// 오류가 있으면 1을 반환합니다.
int init_camera_data(CameraData* result);

// 카메라 윈도우의 RECT를 얻어서 result에 저장합니다.
void get_camera_rect(CameraData camera_data, RECT* result);

// 카메라 윈도우의 색 데이터를 기반으로 result에 저장합니다.
void get_current_color(CameraData camera_data, Color* result);
