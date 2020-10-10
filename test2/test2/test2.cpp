// test2.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "test2.h"
#include <windows.h>
#include <math.h>

#define NUM    1000
#define TWOPI  (2 * 3.14159)

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

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_TEST2, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TEST2));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TEST2));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_TEST2);
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
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
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

int	num_func = 0; //1-sin, 2-cos, 3-tan, 4-ctg

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	static int  cxClient, cyClient;
	int         i;
	POINT       apt[NUM];

    switch (message)
    {
	case WM_SIZE:
	{
		cxClient = LOWORD(lParam);
		cyClient = HIWORD(lParam);
		return 0;
	}

    case WM_COMMAND:
    {
		int wmId = LOWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		case ID_FUNCTIONS_SIN:
			InvalidateRect(hWnd, NULL, TRUE);
			num_func = 1;
			UpdateWindow(hWnd);
			break;
		case ID_FUNCTIONS_COS:
			InvalidateRect(hWnd, NULL, TRUE);
			num_func = 2;
			UpdateWindow(hWnd);
			break;
		case ID_FUNCTIONS_TAN:
			InvalidateRect(hWnd, NULL, TRUE);
			num_func = 3;
			UpdateWindow(hWnd);
			break;
		case ID_FUNCTIONS_CTG:
			InvalidateRect(hWnd, NULL, TRUE);
			num_func = 4;
			UpdateWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
    }
        break;
    case WM_PAINT:
	{
		HDC hdc = BeginPaint(hWnd, &ps);
		switch (num_func)
		{
		case 1:
			MoveToEx(hdc, 0, cyClient / 2, NULL);
			LineTo(hdc, cxClient, cyClient / 2);
			for (i = 0; i < NUM; i++)
			{
				apt[i].x = i * cxClient / NUM;
				apt[i].y = (int)(cyClient / 2 * (1 - sin(TWOPI * i / NUM)));
			}
			Polyline(hdc, apt, NUM);
			break;
		case 2:
			MoveToEx(hdc, 0, cyClient / 2, NULL);
			LineTo(hdc, cxClient, cyClient / 2);
			for (i = 0; i < NUM; i++)
			{
				apt[i].x = i * cxClient / NUM;
				apt[i].y = (int)(cyClient / 2 * (1 - cos(TWOPI * i / NUM)));
			}
			Polyline(hdc, apt, NUM);
			break;
		case 3:
			MoveToEx(hdc, 0, cyClient / 2, NULL);
			LineTo(hdc, cxClient, cyClient / 2);
			for (i = 0; i < NUM; i++)
			{
				apt[i].x = i * cxClient / NUM;
				apt[i].y = (int)(cyClient / 2 * (1 - tan(TWOPI * i / NUM)));
			}
			Polyline(hdc, apt, NUM);
			break;
		case 4:
			MoveToEx(hdc, 0, cyClient / 2, NULL);
			LineTo(hdc, cxClient, cyClient / 2);
			for (i = 0; i < NUM; i++)
			{
				apt[i].x = i * cxClient / NUM;
				apt[i].y = (int)(cyClient / 2 * (1 - 1 / tan(TWOPI * i / NUM)));
			}
			Polyline(hdc, apt, NUM);
			break;
		}
		EndPaint(hWnd, &ps);
		break;
	}
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
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