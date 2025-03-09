#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <stdbool.h>

void Window_Create();
void Window_Show();
void Window_Destroy();

void Window_SwapBuffers();

bool Window_IsRunning();

#endif // _WINDOW_H