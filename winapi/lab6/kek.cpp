#include <Windows.h>
#include "resource.h"

LPCWSTR g_szClassName = L"myWindowClass";
const int timer_id = 1;
LPCWSTR text = L"Hellow world";
bool move = true;
int x = 0, y = 0, dx = 2, w, h;


ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
void move_text(RECT* rect);


LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CREATE:
	{
		if (!SetTimer(hwnd, timer_id, 30, NULL))
		{
			MessageBox(hwnd, L"Couldn't create a timer.", L"Error!",
				MB_ICONEXCLAMATION | MB_OK);
			return FALSE;
		}
		HDC hdc = GetDC(hwnd);
		SIZE size;

		GetTextExtentPoint32(hdc, text, lstrlen(text), &size);
		w = size.cx;
		h = size.cy;
		ReleaseDC(hwnd, hdc);
		break;
	}
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_START:
			move = true;
			break;
		case ID_STOP:
			move = false;
			break;
		}
		break;
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		KillTimer(hwnd, timer_id);
		PostQuitMessage(0);
		break;
	case WM_TIMER:
	{
		RECT rect;
		HDC hdc = GetDC(hwnd);

		GetClientRect(hwnd, &rect);

		y = rect.bottom / 2;

		move_text(&rect);
		InvalidateRect(hwnd, NULL, TRUE);
		ReleaseDC(hwnd, hdc);
		break;
	}
	case WM_PAINT:
	{
		HDC hdc;
		PAINTSTRUCT paintStruct;

		hdc = BeginPaint(hwnd, &paintStruct);
		TextOut(hdc, x, y, text, lstrlen(text));
		EndPaint(hwnd, &paintStruct);
		break;
	}
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wc;
	HWND hwnd;
	MSG Msg;

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = 0;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(GetModuleHandle(nullptr), MAKEINTRESOURCE(1));
	wc.hCursor = LoadCursor(GetModuleHandle(nullptr), MAKEINTRESOURCE(1));
	wc.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);
	wc.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
	wc.lpszClassName = g_szClassName;
	wc.hIconSm = LoadIcon(GetModuleHandle(nullptr), MAKEINTRESOURCE(1));

	if (!RegisterClassEx(&wc))
	{
		MessageBox(nullptr, L"Window Registration Failed!", L"Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return FALSE;
	}

	hwnd = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		g_szClassName,
		L"Lab 6",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
		NULL, NULL, hInstance, NULL);

	if (hwnd == NULL)
	{
		MessageBox(NULL, L"Window Creation Failed!", L"Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&Msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
	return Msg.wParam;
}

void move_text(RECT* rect)
{
	if (move)
	{
		x += dx;

		if (x < 0)
		{
			x = 0;
			dx *= -1;
		}
		else if (x + w > rect->right)
		{
			x = rect->right - w;
			dx *= -1;
		}
	}
}