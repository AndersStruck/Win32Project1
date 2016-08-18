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
	buffer->mi.dx = (0 * (0xFFFF / GetSystemMetrics(SM_CXSCREEN) ));
	buffer->mi.dy = (0 * (0xFFFF / GetSystemMetrics(SM_CYSCREEN) ));
	buffer->mi.mouseData = 0;
	buffer->mi.dwFlags = MOUSEEVENTF_ABSOLUTE;
	buffer->mi.time = 0;
	buffer->mi.dwExtraInfo = 0;
}

void MouseMoveAbsolute(INPUT *buffer, int x, int y) {
	buffer->mi.dx = (x * (0xFFFF / GetSystemMetrics(SM_CXSCREEN) ));
	buffer->mi.dy = (y * (0xFFFF / GetSystemMetrics(SM_CYSCREEN) ));
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

void autoClick(INPUT *buffer, int x, int y, int count, int delay) {
//	int Count = 2;
//	int Delay = 1000;
	int i;
	for (i = 0; i < count; i++) {
		MouseMoveAbsolute(buffer, x, y);
		Sleep(1);
		MouseClick(buffer);
		Sleep(delay);
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
//	LPPOINT MousePos;
//	GetCursorPos(MousePos);
//	char str[128];
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
		hWnd_Count = CreateWindow(TEXT("EDIT"), TEXT("378"),	// set Count
					 WS_VISIBLE | WS_CHILD | WS_BORDER | ES_NUMBER,
					 20, 160,
					 50, 30,
					 hWnd, (HMENU)20,
					 NULL, NULL);
		hWnd_Delay = CreateWindow(TEXT("EDIT"), TEXT("3000"),	// Set Delay
					 WS_VISIBLE | WS_CHILD | WS_BORDER | ES_NUMBER,
					 95, 160,
					 50, 30,
					 hWnd, (HMENU)21,
					 NULL, NULL);
		CreateWindow(TEXT("EDIT"), TEXT("0"),
					 WS_VISIBLE | WS_CHILD | WS_BORDER | ES_NUMBER,
					 170, 160,
					 50, 30,
					 hWnd, (HMENU)22,
					 NULL, NULL);
		CreateWindow(TEXT("EDIT"), TEXT(""), // current x 
					 WS_VISIBLE | WS_CHILD | WS_BORDER | ES_NUMBER,
					 250, 50,
					 50, 30,
					 hWnd, (HMENU)23,
					 NULL, NULL);
		CreateWindow(TEXT("EDIT"), TEXT(""), // current y
					 WS_VISIBLE | WS_CHILD | WS_BORDER | ES_NUMBER,
					 250, 100,
					 50, 30,
					 hWnd, (HMENU)24,
					 NULL, NULL);
		CreateWindow(TEXT("STATIC"), TEXT("X:"),
					 WS_VISIBLE | WS_CHILD | WS_BORDER ,
					 225, 50,
					 25, 30,
					 hWnd, (HMENU)22,
					 NULL, NULL);
		CreateWindow(TEXT("STATIC"), TEXT("Y:"),
					 WS_VISIBLE | WS_CHILD | WS_BORDER,
					 225, 100,
					 25, 30,
					 hWnd, (HMENU)22,
					 NULL, NULL);
		CreateWindow(TEXT("EDIT"), TEXT("500"),// Click x
					 WS_VISIBLE | WS_CHILD | WS_BORDER | ES_NUMBER,
					 250, 200,
					 50, 30,
					 hWnd, (HMENU)25,
					 NULL, NULL);
		CreateWindow(TEXT("EDIT"), TEXT("350"), // click y
					 WS_VISIBLE | WS_CHILD | WS_BORDER | ES_NUMBER,
					 250, 250,
					 50, 30,
					 hWnd, (HMENU)26,
					 NULL, NULL);
		CreateWindow(TEXT("STATIC"), TEXT("X:"),
					 WS_VISIBLE | WS_CHILD | WS_BORDER,
					 225, 200,
					 25, 30,
					 hWnd, (HMENU)22,
					 NULL, NULL);
		CreateWindow(TEXT("STATIC"), TEXT("Y:"),
					 WS_VISIBLE | WS_CHILD | WS_BORDER,
					 225, 250,
					 25, 30,
					 hWnd, (HMENU)22,
					 NULL, NULL);
		CreateWindow(TEXT("Button"), TEXT("Click"),
					 WS_VISIBLE | WS_CHILD,
					 20, 200,
					 200, 40,
					 hWnd, (HMENU)10,
					 NULL, NULL);
		hWnd_TEXT = CreateWindow(TEXT("STATIC"), TEXT("Tjek !"),
					 WS_VISIBLE | WS_CHILD | WS_BORDER,
					 20, 20,
					 200, 100,
					 hWnd, (HMENU)27,
					 NULL, NULL);
		break;
	case WM_MOUSEMOVE:
		POINT Mouse;
		GetCursorPos(&Mouse);
		ClientToScreen(hWnd, &Mouse);
		SetDlgItemInt(hWnd, 23, Mouse.x, TRUE);
		SetDlgItemInt(hWnd, 24, Mouse.y, TRUE);
	//	OutputDebugStringA("Mouse Detected:\n");
		break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId){
				case 10:
				{
				//	autoClick(&buffer, 1920, 1080, 1, 0);
					int len = GetWindowTextLength(hWnd_Count) + 1;
					INT runCount, runDelay, run ;
					POINT click;
					char str[256];
					BOOL b;
					SetDlgItemInt(hWnd, 22, GetSystemMetrics(1), FALSE);

					click.x = GetDlgItemInt(hWnd, 25, NULL, FALSE);
					click.y = GetDlgItemInt(hWnd, 26, NULL, FALSE);
					runCount = GetDlgItemInt(hWnd, 20, &b, FALSE);
					runDelay = GetDlgItemInt(hWnd, 21, NULL, FALSE);
					autoClick(&buffer, click.x, click.y, runCount, runDelay);
					sprintf_s(str, "Read Value: %d ; Sucess: %d\n", runCount, b);
					OutputDebugStringA( str );
				//	SetDlgItemInt(hWnd, 21, runCount, FALSE);
					POINT Mouse;
					GetPhysicalCursorPos(&Mouse);
				//	ClientToScreen(hWnd, &Mouse);
				//	ScreenToClient(hWnd, &Mouse);
					SetDlgItemInt(hWnd, 23, Mouse.x, TRUE);
					SetDlgItemInt(hWnd, 24, Mouse.y, TRUE);
				//	autoClick(&buffer, Mouse.x, Mouse.y, runCount, runDelay);
				//	sprintf_s(str, "Mouse Position: %d , %d \n", Mouse.x , Mouse.y);
					OutputDebugStringA(str);
				//	static char Count[10];
				//	LONG_PTR Count = 0;
				//	GetWindowTextA(hWnd_Count, Count, len);
				//	Count = GetWindowLong(hWnd_Count, GWL_USERDATA);
				//	SetWindowText(hWnd_TEXT, TEXT("Button"));
				//	SetWindowTextA(hWnd_Delay , Count);
				//	SetWindowLong(hWnd_Delay, GWL_USERDATA, Count);
				//	SetWindowLongPtr(hWnd_Count, GWL_USERDATA, (LONG_PTR) 10 );
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
