#include "celesteclone_lib.h"
//Plataform globals



static bool running = true;

//Plataform Functions 

bool platform_create_window(int width, int height, const char* title);
void platform_update();

//Windows Plataform

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>


//win globals
static HWND window;

//win plataform iplementation
LRESULT CALLBACK windows_window_callback(HWND window, UINT message, WPARAM wparam, LPARAM lparam)
{
  LRESULT result = 0;

  switch(message)
  {
    case WM_CLOSE:
    {
      running = false;
      break;
    }
    
    default:
    {
      result = DefWindowProcA(window, message, wparam, lparam);
    }
  }

  return result;
}

bool platform_create_window(int width, int height, const char* title)
{
  HINSTANCE instance = GetModuleHandleA(0);

  WNDCLASSA wc = {};
  wc.hIcon = LoadIcon(instance, IDI_APPLICATION);
  wc.hCursor = LoadCursor(NULL, IDC_ARROW);
  wc.lpszClassName = title;
  wc.lpfnWndProc = windows_window_callback;

  if(!RegisterClassA(&wc))
  {
    return false;
  }

  int dwStyle = WS_OVERLAPPEDWINDOW;
  window = CreateWindowExA(0, title, title, dwStyle, 100, 100, width, height, NULL, NULL, instance, NULL);

  if(window == NULL)
  {
    return false;
  }

  ShowWindow(window, SW_SHOW);
  return true;

}
void platform_update()
{
  MSG msg;

  while(PeekMessageA(&msg, window, 0, 0, PM_REMOVE))
  {
    TranslateMessage(&msg);
    DispatchMessageA(&msg);
  }
}


#endif


int main()
{
  platform_create_window(1200, 720, "Celeste Clone");
  while (running)
  {
    platform_update();

    SM_TRACE("Hello World");
    SM_WARN("Hello World");
    SM_ERROR("Hello World");
  }
  
}