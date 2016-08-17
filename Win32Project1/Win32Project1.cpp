// Win32Project1.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Win32Project1.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

#define SCREEN_WIDTH 3840
#define SCREEN_HEIGHT 2160

void MouseSetup(INPUT *buffer) {
	buffer->type = INPUT_MOUSE;
	buffer->mi.dx = (0 * (0xFFFF / SCREEN_WIDTH));
	buffer->mi.dy = (0 * (0xFFFF / SCREEN_HEIGHT));
	buffer->mi.mouseData = 0;
	buffer->mi.dwFlags = MOUSEEVENTF_ABSOLUTE;
	buffer->mi.time = 0;
	buffer->mi.dwExtraInfo = 0;
}

void MouseMoveAbsolute(INPUT *buffer, int x, int y) {
	buffer->mi.dx = (x * (0xFFFF / SCREEN_WIDTH));
	buffer->mi.dy = (y * (0xFFFF / SCREEN_HEIGHT));
	buffer->mi.dwFlags = (MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE);
	SendInput(1, buffer, sizeof(INPUT));
}

void MouseClick(INPUT *buffer) {
	buffer->mi.dwFlags = (MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_LEFTDOWN);
	SendInput(1, buffer, sizeof(INPUT));
	Sleep(10);
	buffer->mi.dwFlags = (MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_LEFTUP);
	SendInput(1, buffer, sizeof(INPUT));
}

void autoClick(INPUT *buffer) {
	int Count = 2;
	int Delay = 1000;
	int i;
	for (i = 0; i < Count; i++) {
		MouseMoveAbsolute(buffer, 500, 500);
	//	Sleep(Delay);
	}
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.
	//INPUT buffer;
	int i = 0;
	LPPOINT MousePos;
//	GetCursorPos(MousePos);
	char str[128];
	//sprintf_s(str);
	OutputDebugStringA("Konsol Test\n");
	
	//MouseSetup( &buffer );
	//for (i = 0; i < 100; i++) {
	//	MouseMoveAbsolute(&buffer, 10, 10);
	//	Sleep(100);
	//}
	

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WIN32PROJECT1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WIN32PROJECT1));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0)){
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WIN32PROJECT1));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WIN32PROJECT1);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, 500, 500, nullptr, nullptr, hInstance, nullptr);
   
   if (!hWnd){
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);
  
   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam){
	static HWND hWnd_TEXT, hWnd_Count, hWnd_Delay;
	static INPUT buffer;
	MouseSetup(&buffer);
    switch (message){
	case WM_CREATE:
		hWnd_Count = CreateWindow(TEXT("EDIT"), TEXT("7"),
					 WS_VISIBLE | WS_CHILD | WS_BORDER | ES_NUMBER,
					 20, 160,
					 50, 30,
					 hWnd, (HMENU)20,
					 NULL, NULL);
		hWnd_Delay = CreateWindow(TEXT("EDIT"), TEXT("Delay"),
					 WS_VISIBLE | WS_CHILD | WS_BORDER | ES_NUMBER,
					 95, 160,
					 50, 30,
					 hWnd, (HMENU)21,
					 NULL, NULL);
		CreateWindow(TEXT("EDIT"), TEXT("edit"),
					 WS_VISIBLE | WS_CHILD | WS_BORDER | ES_NUMBER,
					 170, 160,
					 50, 30,
					 hWnd, (HMENU)22,
					 NULL, NULL);
		CreateWindow(TEXT("Button"), TEXT("Click"),
					 WS_VISIBLE | WS_CHILD,
					 20, 200,
					 200, 40,
					 hWnd, (HMENU)23,
					 NULL, NULL);
		hWnd_TEXT = CreateWindow(TEXT("STATIC"), TEXT("Tjek !"),
					 WS_VISIBLE | WS_CHILD | WS_BORDER,
					 20, 20,
					 200, 100,
					 hWnd, (HMENU)24,
					 NULL, NULL);
		break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId){
				case 23:
				{
					autoClick(&buffer);
					int len = GetWindowTextLength(hWnd_Count) + 1;
					INT k;
					char str[256];
					BOOL b;
					k = GetDlgItemInt(hWnd, 20, &b, FALSE);
					sprintf_s(str, "Read Value: %d ; Sucess: %d\n", k, b);
					OutputDebugStringA( str );
				//	static char Count[10];
					LONG_PTR Count = 0;
				//	GetWindowTextA(hWnd_Count, Count, len);
					Count = GetWindowLong(hWnd_Count, GWL_USERDATA);
					SetWindowText(hWnd_TEXT, TEXT("Button"));
				//	SetWindowTextA(hWnd_Delay , Count);
				//	SetWindowLong(hWnd_Delay, GWL_USERDATA, Count);
					SetWindowLongPtr(hWnd_Count, GWL_USERDATA, (LONG_PTR) 10 );
					break; 
				}
				case IDM_ABOUT:
					DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
					break;
				case IDM_EXIT:
					DestroyWindow(hWnd);
					break;
				default:
					return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam){
    UNREFERENCED_PARAMETER(lParam);
	
    switch (message){
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
