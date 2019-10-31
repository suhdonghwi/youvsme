#pragma once
#include <Windows.h>

typedef struct tagCameraData {
  HWND camera_window;
  HDC monitor_dc;
} CameraData;

typedef enum tagColor { COLOR_RED, COLOR_BLUE, COLOR_OTHER } Color;

// ī�޶� �����͸� �ʱ�ȭ�Ͽ� result�� �����մϴ�. ���������� �ʱ�ȭ�Ǹ� 0,
// ������ ������ 1�� ��ȯ�մϴ�.
int init_camera_data(CameraData* result);

// ī�޶� �������� RECT�� �� result�� �����մϴ�.
void get_camera_rect(CameraData camera_data, RECT* result);

// ī�޶� �������� �� �����͸� ������� result�� �����մϴ�.
void get_current_color(CameraData camera_data, Color* result);
