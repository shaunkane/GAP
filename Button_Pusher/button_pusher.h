/*****************/
/* Pre-Processer */
/*****************/

#include <Windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#include <conio.h>
#include <iostream>
#include <fstream>
#include <Xinput.h>
#include "xbox_controller.h"

using namespace std;

/********************/
/* Global Variables */
/********************/

// The main window class name.
const TCHAR WINDOW_CLASS[] = _T("button_pusher");

// The string that appears in the application's title bar.
const TCHAR WINDOW_TITLE[] = _T("Button Pusher!");

HINSTANCE hInst;

// Forward declarations of functions included in this code module:
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);