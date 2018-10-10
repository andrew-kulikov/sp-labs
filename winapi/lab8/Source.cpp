#include <Windows.h>
#include <conio.h>

#define ID_BUTTON_DRAW 321
#define ID_BUTTON_CLEAR 322

void draw(HDC hdc, int x, int y);

LPCWSTR g_szClassName = L"myWindowClass";

void init_btn(HWND hwnd) {
	HWND btn_draw = CreateWindow(L"Button", L"Draw", 
		WS_CHILD | WS_VISIBLE | BS_OWNERDRAW, 
		290, 30, 100, 50, 
		hwnd, 
		(HMENU)ID_BUTTON_DRAW, NULL, NULL);

	HWND btn_clear = CreateWindow(L"Button", L"Clear", 
		WS_CHILD | WS_VISIBLE | BS_OWNERDRAW, 
		410, 30, 100, 50, 
		hwnd, 
		(HMENU)ID_BUTTON_CLEAR, NULL, NULL);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{

	case WM_CREATE:
	{
		init_btn(hwnd);

		break;
	}
	case WM_DRAWITEM:
	{
		LPDRAWITEMSTRUCT pdis = (LPDRAWITEMSTRUCT)lParam;
		FillRect(pdis->hDC, &pdis->rcItem, (HBRUSH)CreateSolidBrush(RGB(123, 123, 84)));
		
		SetBkMode(pdis->hDC, TRANSPARENT);

		switch (pdis->CtlID)
		{
		case ID_BUTTON_DRAW:
		{
			DrawText(pdis->hDC, L"Draw", -1, &pdis->rcItem, DT_CENTER | DT_SINGLELINE | DT_VCENTER);
			POINT triangle[3] = { { 25, 25 },{ 3, 42 },{ 3, 8 } };
			Polygon(pdis->hDC, triangle, sizeof(triangle) / sizeof(triangle[0]));
			break;
		}
		case ID_BUTTON_CLEAR:
		{
			DrawText(pdis->hDC, L"Clear", -1, &pdis->rcItem, DT_CENTER | DT_SINGLELINE | DT_VCENTER);
			Ellipse(pdis->hDC, 5, 15, 25, 35);
			HPEN hPen1 = CreatePen(PS_SOLID, 2, RGB(102, 0, 255));
			MoveToEx(pdis->hDC, 7, 17, NULL);
			LineTo(pdis->hDC, 23, 33);
			MoveToEx(pdis->hDC, 21, 17, NULL);
			LineTo(pdis->hDC, 7, 31);
			break;
		}
		}
		break;
	}

	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case ID_BUTTON_DRAW:
		{
			HDC hdc = GetDC(hwnd); //получаем DC(контекст устройства) для рисования
			draw(hdc, 200, 200);

			break;
		}
		case ID_BUTTON_CLEAR:
		{
			HDC hdc = GetDC(hwnd);
			RECT rect;
			GetClientRect(hwnd, &rect);
			rect.top += 80;
			FillRect(hdc, &rect, (HBRUSH)(COLOR_WINDOW + 1));
			break;
		}
		}
		break;
	}


	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

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
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = g_szClassName;
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, L"Window Registration Failed!", L"Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	hwnd = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		g_szClassName,
		L"Lab 8",
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX,
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

void draw(HDC hdc, int x, int y) {
	COLORREF color = RGB(0, 0, 0);
	HPEN pen = CreatePen(PS_SOLID, 3, color);
	HPEN old_pen = (HPEN)SelectObject(hdc, pen);
	HBRUSH hBrush = CreateSolidBrush(RGB(255, 255, 0));
	HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);

	MoveToEx(hdc, x, y, NULL);

	SelectObject(hdc, hBrush);
	Ellipse(hdc, x - 50, y - 50, x + 50, y + 50);

	hBrush = CreateSolidBrush(RGB(255, 255, 255));
	SelectObject(hdc, hBrush);
	color = RGB(255, 255, 255);
	pen = CreatePen(PS_SOLID, 0, color);
	SelectObject(hdc, pen);

	pen = CreatePen(PS_SOLID, 3, color);
	POINT triangle[3] = { { x, y },{ x + 50, y - 30 },{ x + 50, y + 30 } };
	Polygon(hdc, triangle, sizeof(triangle) / sizeof(triangle[0]));

	color = RGB(0, 0, 0);
	pen = CreatePen(PS_SOLID, 3, color);
	SelectObject(hdc, pen);

	MoveToEx(hdc, x + 42.9, y - 25.78, NULL);
	LineTo(hdc, x, y);
	MoveToEx(hdc, x + 42.9, y + 25.78, NULL);
	LineTo(hdc, x, y);

	hBrush = CreateSolidBrush(RGB(0, 0, 0));
	SelectObject(hdc, hBrush);
	Ellipse(hdc, x + 10, y - 32, x + 15, y - 27);

	MoveToEx(hdc, x - 60, y - 60, NULL);
	LineTo(hdc, x + 450, y - 60);
	MoveToEx(hdc, x - 60, y + 60, NULL);
	LineTo(hdc, x + 350, y + 60);
	MoveToEx(hdc, x + 350, y + 60, NULL);
	LineTo(hdc, x + 350, y + 150);
	MoveToEx(hdc, x + 450, y - 60, NULL);
	LineTo(hdc, x + 450, y + 150);

	Ellipse(hdc, x + 65, y - 5, x + 75, y + 5);
	Ellipse(hdc, x + 85, y - 5, x + 95, y + 5);
	Ellipse(hdc, x + 105, y - 5, x + 115, y + 5);
	Ellipse(hdc, x + 125, y - 5, x + 135, y + 5);
	Ellipse(hdc, x + 145, y - 5, x + 155, y + 5);

	SelectObject(hdc, hOldBrush);
	DeleteObject(hBrush);
	SelectObject(hdc, old_pen);
	DeleteObject(pen);
}

