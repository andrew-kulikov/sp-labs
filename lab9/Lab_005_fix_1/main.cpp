#include <Windows.h>
#include <Windowsx.h>
#include "ids.h"

LPCWSTR windowClassName = L"ControlClass";

LPCWSTR targetClassName = L"DisplayClass";
LPCWSTR targetWindowName = L"Display";

enum Color { RED, GREEN, BLUE };
enum Figure { RHOMBUS, SQUARE, CIRCLE, STAR };

struct WindowData
{
	Color color = RED;
	Figure figure = RHOMBUS;

	bool draw = false;
} window_data;

COPYDATASTRUCT copyDataStruct;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	copyDataStruct.cbData = sizeof(WindowData);
	copyDataStruct.lpData = static_cast<PVOID>(&window_data);

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
		MessageBox(nullptr, L"Couldn't register the Windwow Class",
			L"Control window error!", MB_ICONEXCLAMATION | MB_OK);
		return -1;
	}

	hwnd = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		windowClassName,
		L"Controls",
		WS_OVERLAPPEDWINDOW &~WS_MAXIMIZEBOX,
		200, 200, 600, 600,
		nullptr, nullptr, hInstance, nullptr
	);

	if (hwnd == nullptr)
	{
		MessageBox(nullptr, L"Couldn't create the Window Class.",
			L"Control window error!", MB_ICONEXCLAMATION | MB_OK);
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
	case WM_CREATE:
	{
		CreateWindow(
			L"button", L"Color",
			WS_VISIBLE | WS_CHILD | BS_GROUPBOX,
			5, 1, 100, 110,
			hWnd, nullptr, GetModuleHandle(nullptr), nullptr
		);

		HWND red = CreateWindow(
			L"button", L"Red",
			WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON | WS_GROUP,
			10, 20, 46, 20,
			hWnd, reinterpret_cast<HMENU>(IDC_RED),
			GetModuleHandle(nullptr), nullptr
		);
		SendMessage(red, BM_SETCHECK, BST_CHECKED, 0);

		CreateWindow(
			L"button", L"Green",
			WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,
			10, 40, 59, 20,
			hWnd, reinterpret_cast<HMENU>(IDC_GREEN),
			GetModuleHandle(nullptr), nullptr
		);

		CreateWindow(
			L"button", L"Blue",
			WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,
			10, 60, 55, 20,
			hWnd, reinterpret_cast<HMENU>(IDC_BLUE),
			GetModuleHandle(nullptr), nullptr
		);

		CreateWindow(
			L"button", L"Figure",
			WS_VISIBLE | WS_CHILD | BS_GROUPBOX,
			110, 1, 110, 110,
			hWnd, nullptr, GetModuleHandle(nullptr), nullptr
		);

		HWND rhombus = CreateWindow(
			L"button", L"Rhombus",
			WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON | WS_GROUP,
			120, 20, 85, 20,
			hWnd, reinterpret_cast<HMENU>(IDC_RHOMBUS),
			GetModuleHandle(nullptr), nullptr
		);
		SendMessage(rhombus, BM_SETCHECK, BST_CHECKED, 0);

		CreateWindow(
			L"button", L"Square",
			WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,
			120, 40, 66, 20,
			hWnd, reinterpret_cast<HMENU>(IDC_SQUARE),
			GetModuleHandle(nullptr), nullptr
		);

		CreateWindow(
			L"button", L"Circle",
			WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,
			120, 60, 57, 20,
			hWnd, reinterpret_cast<HMENU>(IDC_CIRCLE),
			GetModuleHandle(nullptr), nullptr
		);

		CreateWindow(
			L"button", L"Star",
			WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,
			120, 80, 47, 20,
			hWnd, reinterpret_cast<HMENU>(IDC_STAR),
			GetModuleHandle(nullptr), nullptr
		);

		CreateWindow(
			L"button", L"Draw",
			WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX,
			230, 5, 53, 20,
			hWnd, reinterpret_cast<HMENU>(IDC_DRAW),
			GetModuleHandle(nullptr), nullptr
		);
		break;
	}
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
			case IDC_RED:
				window_data.color = RED;
				break;
			case IDC_GREEN:
				window_data.color = GREEN;
				break;
			case IDC_BLUE:
				window_data.color = BLUE;
				break;
			case IDC_RHOMBUS:
				window_data.figure = RHOMBUS;
				break;
			case IDC_CIRCLE:
				window_data.figure = CIRCLE;
				break;
			case IDC_SQUARE:
				window_data.figure = SQUARE;
				break;
			case IDC_STAR:
				window_data.figure = STAR;
				break;
			case IDC_DRAW:
			{
				window_data.draw = (BST_CHECKED ==
					Button_GetCheck(GetDlgItem(hWnd, IDC_DRAW)));
				break;
			}
		}
		HWND hwDispatch = FindWindow(targetClassName, targetWindowName);
		if (hwDispatch != nullptr)
		{
			SendMessage(
				hwDispatch,
				WM_COPYDATA,
				reinterpret_cast<WPARAM>(hWnd),
				reinterpret_cast<LPARAM>(&copyDataStruct)
			);
		}
		else
		{
			MessageBox(hWnd, L"Can't send WM_COPYDATA", L"Error!",
				MB_OK | MB_ICONEXCLAMATION);
		}
		break;
	}
	case WM_GETMINMAXINFO:
	{
		MINMAXINFO* mmi = reinterpret_cast<MINMAXINFO*>(lParam);
		mmi->ptMaxTrackSize.x = mmi->ptMinTrackSize.x = 310;
		mmi->ptMaxTrackSize.y = mmi->ptMinTrackSize.y = 180;
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