#include <Windows.h>
#include <Windowsx.h>

LPCWSTR windowClassName = L"DisplayClass";

enum Color { RED, GREEN, BLUE };
enum Figure { RHOMBUS, SQUARE, CIRCLE, STAR };

struct WindowData
{
	Color color;
	Figure figure;

	bool draw = false;
} window_data;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

void DrawFigure(HDC hdc, POINT pos);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wc;
	HWND hwnd;
	MSG msg;

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = 1;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW);
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = windowClassName;
	wc.hIconSm = nullptr;

	if (!RegisterClassEx(&wc))
	{
		MessageBox(nullptr, L"Couldn't register the Window Class.",
			L"Display window error!", MB_ICONEXCLAMATION | MB_OK);
		return -1;
	}

	hwnd = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		windowClassName,
		L"Display",
		WS_OVERLAPPEDWINDOW &~WS_MAXIMIZEBOX,
		CW_USEDEFAULT, CW_USEDEFAULT, 600, 400,
		nullptr, nullptr, hInstance, nullptr
	);

	if (hwnd == nullptr)
	{
		MessageBox(nullptr, L"Couldn't create the Window Class.",
			L"Display window Error!", MB_ICONEXCLAMATION | MB_OK);
		return -1;
	}

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, nullptr, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	switch (Msg)
	{
	case WM_LBUTTONDOWN:
		if (window_data.draw)
		{
			POINT pos;
			pos.x = GET_X_LPARAM(lParam);
			pos.y = GET_Y_LPARAM(lParam);

			HDC hdc = GetDC(hWnd);
			DrawFigure(hdc, pos);
			ReleaseDC(hWnd, hdc);
		}
		break;
	case WM_COPYDATA:
	{
		PCOPYDATASTRUCT pcds = reinterpret_cast<PCOPYDATASTRUCT>(lParam);
		window_data = *reinterpret_cast<WindowData*>(pcds->lpData);
		break;
	}
	case WM_CLOSE:
		DestroyWindow(hWnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, Msg, wParam, lParam);
	}

	return 0;
}

void DrawFigure(HDC hdc, POINT pos)
{
	HBRUSH hBrush;

	switch (window_data.color)
	{
	case RED:
		hBrush = CreateSolidBrush(RGB(255, 0, 0));
		SelectObject(hdc, hBrush);
		break;
	case GREEN:
		hBrush = CreateSolidBrush(RGB(0, 255, 0));
		SelectObject(hdc, hBrush);
		break;
	case BLUE:
		hBrush = CreateSolidBrush(RGB(0, 0, 255));
		SelectObject(hdc, hBrush);
		break;
	}

	switch (window_data.figure)
	{
		case RHOMBUS:
		{
			POINT rhombus[] = {
				pos.x - 12, pos.y,
				pos.x,     pos.y - 20,
				pos.x + 12, pos.y,
				pos.x,     pos.y + 20
			};

			Polygon(hdc, rhombus, 4);
			break;
		}
		case SQUARE:
			Rectangle(hdc, pos.x - 20, pos.y - 20, pos.x + 20, pos.y + 20);
			break;
		case CIRCLE:
			Ellipse(hdc, pos.x - 20, pos.y - 20, pos.x + 20, pos.y + 20);
			break;
		case STAR:
		{
			POINT star[] = {
				pos.x - 15, pos.y - 5,
				pos.x - 5,  pos.y - 5,
				pos.x,      pos.y - 15,
				pos.x + 5,  pos.y - 5,
				pos.x + 15, pos.y - 5,
				pos.x + 6,  pos.y + 3,
				pos.x + 11,  pos.y + 12,
				pos.x,      pos.y + 6,
				pos.x - 11,  pos.y + 12,
				pos.x - 6,  pos.y + 3,
				pos.x - 15, pos.y - 5
			};
			Polygon(hdc, star, 11);
			break;
		}
	}
}