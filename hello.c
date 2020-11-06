/* hello.c with icon resource */
#include <windows.h>
#include "resource.h"

LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);

#pragma clang diagnostic ignored "-Wdll-attribute-on-redeclaration"
__declspec(dllexport) //https://stackoverflow.com/a/25341688/8006810
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR szCmdLine, int iCmdShow)
{
  TCHAR szAppName[] = TEXT("Hello");
  HWND hwnd;
  MSG msg;
  WNDCLASS wndclass;
  wndclass.style = CS_HREDRAW | CS_VREDRAW;
  wndclass.lpfnWndProc = WindowProc;
  wndclass.cbClsExtra = 0;
  wndclass.cbWndExtra = 0;
  wndclass.hInstance = hInstance;
  wndclass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_HELLO));
  wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
  wndclass.hbrBackground = GetStockObject(WHITE_BRUSH);
  wndclass.lpszMenuName = NULL;
  wndclass.lpszClassName = szAppName;

  // error handling
  DWORD dLastError;
  LPCTSTR szErrorMessage;

  if (!RegisterClass(&wndclass))
  {

    dLastError = GetLastError();
    LPCTSTR szErrorMessage = NULL;

    FormatMessage(
        FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS | FORMAT_MESSAGE_ARGUMENT_ARRAY | FORMAT_MESSAGE_ALLOCATE_BUFFER,
        NULL,
        dLastError,
        0,
        (LPTSTR)&szErrorMessage,
        0,
        NULL);

    MessageBox(NULL, szErrorMessage, szAppName, MB_ICONERROR);

    // release memory allocated by FormatMessage()
    LocalFree((LPTSTR)szErrorMessage);
    szErrorMessage = NULL;

    return 0;
  }

  hwnd = CreateWindow(szAppName, TEXT("Hello"),
                      WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);
  ShowWindow(hwnd, iCmdShow);
  UpdateWindow(hwnd);

  while (GetMessage(&msg, NULL, 0, 0))
  {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

  return msg.wParam;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{

  HDC hdc;
  PAINTSTRUCT ps;

  switch (message)
  {

  case WM_CREATE:
    return 0;

  case WM_PAINT:
    hdc = BeginPaint(hwnd, &ps);
    EndPaint(hwnd, &ps);
    return 0;

  case WM_DESTROY:
    PostQuitMessage(0);
    return 0;
  }

  return DefWindowProc(hwnd, message, wParam, lParam);
}
