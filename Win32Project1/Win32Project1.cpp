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

void MouseSetup(INPUT *buffer) {
	buffer->type = INPUT_MOUSE;
	buffer->mi.dx = (0);
	buffer->mi.dy = (0);
	buffer->mi.mouseData = 0;
	buffer->mi.dwFlags = MOUSEEVENTF_ABSOLUTE;
	buffer->mi.time = 0;
	buffer->mi.dwExtraInfo = 0;
}
void MouseMoveAbsolute(INPUT *buffer, int x, int y) {
	buffer->mi.dx = ( x );
	buffer->mi.dy = ( y );
	buffer->mi.dwFlags = (MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE);

	SendInput(1, buffer, sizeof(INPUT));
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.
	INPUT buffer;
	int i = 0;
	
	MouseSetup( &buffer );
	//for (i = 0; i < 100; i++) {
		MouseMoveAbsolute(&buffer, 10, 10);
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
    while (GetMessage(&msg, nullptr, 0, 0))
    {
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
	static HWND hWnd_TEXT;
    switch (message){
	case WM_CREATE:
		CreateWindow(TEXT("EDIT"), TEXT("edit"),
					 WS_VISIBLE | WS_CHILD | WS_BORDER,
					 20, 160,
					 50, 30,
					 hWnd, (HMENU)20,
					 NULL, NULL);
		CreateWindow(TEXT("EDIT"), TEXT("edit"),
					 WS_VISIBLE | WS_CHILD | WS_BORDER,
					 95, 160,
					 50, 30,
					 hWnd, (HMENU)21,
					 NULL, NULL);
		CreateWindow(TEXT("EDIT"), TEXT("edit"),
					 WS_VISIBLE | WS_CHILD | WS_BORDER,
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
					SetWindowText(hWnd_TEXT ,TEXT("Text nu!"));
					break;
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
