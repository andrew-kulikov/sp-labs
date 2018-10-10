#include <Windows.h>

#define ID_TEXTBOX 221
#define ID_LISTBOX1 222
#define ID_LISTBOX2 223
#define ID_ADD_BUTTON 224
#define ID_CLEAR_BUTTON 225
#define ID_MOVE_BUTTON 226
#define ID_DELETE_BUTTON 227
#define ID_MOVE_BUTTON1 228


LPCWSTR g_szClassName = L"myWindowClass";
HWND textbox, listbox1, listbox2, btn_add, btn_clear, btn_move, btn_delete, btn_move1 = NULL;

void show_error(HWND hwnd, LPCWSTR msg);
void create_controls(HWND hwnd);
void handle_add(HWND hwnd);
void handle_delete(HWND hwnd);
void handle_clear(HWND hwnd);
void handle_move(HWND hwnd);
void handle_move1(HWND hwnd);

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CREATE:
		create_controls(hwnd);
		break;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_ADD_BUTTON:
		{
			handle_add(hwnd);
			break;
		}
		case ID_CLEAR_BUTTON:
		{
			handle_clear(hwnd);
			break;
		}
		case ID_DELETE_BUTTON:
		{
			handle_delete(hwnd);
			break;
		}
		case ID_MOVE_BUTTON: {
			handle_move(hwnd);
			break;
		}
		case ID_MOVE_BUTTON1: {
			handle_move1(hwnd);
			break;
		}
		}
	
		break;
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
	MSG msg;

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

	HWND hwnd = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		g_szClassName,
		L"Lab 7",
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

	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

void show_error(HWND hwnd, LPCWSTR msg)
{
	MessageBox(hwnd, msg, L"Error", MB_OK | MB_ICONERROR);
}

void create_controls(HWND hwnd)
{
	textbox = CreateWindow(L"EDIT", L"", 
		WS_BORDER | WS_CHILD | WS_VISIBLE, 
		40, 40, 350, 30, 
		hwnd, 
		(HMENU)ID_TEXTBOX, 
		NULL, 
		NULL);

	if (textbox == NULL)
		show_error(hwnd, L"Could not create edit box.");

	listbox1 = CreateWindow(L"LISTBOX", L"", 
		WS_BORDER | WS_CHILD | WS_VISIBLE, 
		40, 100, 350, 400, 
		hwnd, 
		(HMENU)ID_LISTBOX1, 
		NULL, 
		NULL);

	if (listbox1 == NULL)
		show_error(hwnd, L"Could not create list box 1.");

	listbox2 = CreateWindow(L"LISTBOX", L"", 
		WS_BORDER | WS_CHILD | WS_VISIBLE, 
		420, 100, 350, 400,
		hwnd, 
		(HMENU)ID_LISTBOX2, 
		NULL, 
		NULL);

	if (listbox2 == NULL)
		show_error(hwnd, L"Could not create list box 2.");

	btn_add = CreateWindow(L"Button", L"Add", 
		WS_BORDER | WS_CHILD | WS_VISIBLE, 
		400, 40, 100, 30, 
		hwnd, 
		(HMENU)ID_ADD_BUTTON, 
		NULL, 
		NULL);

	if (btn_add == NULL)
		show_error(hwnd, L"Could not create AddButton.");

	btn_clear = CreateWindow(L"Button", L"Clear All",
		WS_BORDER | WS_CHILD | WS_VISIBLE,
		650, 40, 100, 30,
		hwnd,
		(HMENU)ID_CLEAR_BUTTON,
		NULL,
		NULL);

	if (btn_clear == NULL)
		show_error(hwnd, L"Could not create ClearButton.");

	btn_move = CreateWindow(L"Button", L"Move Right",
		WS_BORDER | WS_CHILD | WS_VISIBLE,
		40, 490, 100, 30,
		hwnd,
		(HMENU)ID_MOVE_BUTTON,
		NULL,
		NULL);

	btn_move1 = CreateWindow(L"Button", L"Move Left",
		WS_BORDER | WS_CHILD | WS_VISIBLE,
		250, 490, 100, 30,
		hwnd,
		(HMENU)ID_MOVE_BUTTON1,
		NULL,
		NULL);

	if (btn_move == NULL)
		show_error(hwnd, L"Could not create ToRightButton.");

	btn_delete = CreateWindow(L"Button", L"Delete", 
		WS_BORDER | WS_CHILD | WS_VISIBLE, 
		150, 490, 100, 30, 
		hwnd, 
		(HMENU)ID_DELETE_BUTTON, 
		NULL, 
		NULL);

	if (btn_delete == NULL)
		show_error(hwnd, L"Could not create DeleteButton.");

	
}

void handle_add(HWND hwnd)
{
	int text_len = GetWindowTextLength(GetDlgItem(hwnd, ID_TEXTBOX));
	if (text_len > 0)
	{
		TCHAR * buf = (TCHAR*)GlobalAlloc(GPTR, sizeof(TCHAR) * (text_len + 1));
		GetDlgItemText(hwnd, ID_TEXTBOX, buf, text_len + 1);
		if (SendDlgItemMessage(hwnd, ID_LISTBOX1, LB_FINDSTRINGEXACT, NULL, (LPARAM)buf) == LB_ERR)
			SendDlgItemMessage(hwnd, ID_LISTBOX1, LB_ADDSTRING, NULL, LPARAM(buf));
		SetDlgItemText(hwnd, ID_TEXTBOX, L"");
		GlobalFree(buf);
	}
}

void handle_delete(HWND hwnd)
{
	int selected_id = SendDlgItemMessage(hwnd, ID_LISTBOX1, LB_GETCURSEL, NULL, NULL);
	if (selected_id != LB_ERR)
		SendDlgItemMessage(hwnd, ID_LISTBOX1, LB_DELETESTRING, selected_id, NULL);

	selected_id = SendDlgItemMessage(hwnd, ID_LISTBOX2, LB_GETCURSEL, NULL, NULL);
	if (selected_id != LB_ERR)
		SendDlgItemMessage(hwnd, ID_LISTBOX2, LB_DELETESTRING, selected_id, NULL);
}

void handle_clear(HWND hwnd)
{
	SendDlgItemMessage(hwnd, ID_LISTBOX1, LB_RESETCONTENT, NULL, NULL);
	SendDlgItemMessage(hwnd, ID_LISTBOX2, LB_RESETCONTENT, NULL, NULL);
}

void handle_move(HWND hwnd)
{
	int selected_id = SendDlgItemMessage(hwnd, ID_LISTBOX1, LB_GETCURSEL, NULL, NULL);
	if (selected_id != LB_ERR)
	{
		int len = SendDlgItemMessage(hwnd, ID_LISTBOX1, LB_GETTEXTLEN, selected_id, NULL);
		TCHAR* buf = (TCHAR*)GlobalAlloc(GPTR, sizeof(TCHAR) * (len + 1));
		SendDlgItemMessage(hwnd, ID_LISTBOX1, LB_GETTEXT, selected_id, (LPARAM)buf);
		if (SendDlgItemMessage(hwnd, ID_LISTBOX2, LB_FINDSTRINGEXACT, NULL, (LPARAM)buf) == LB_ERR)
			SendDlgItemMessage(hwnd, ID_LISTBOX2, LB_ADDSTRING, NULL, (LPARAM)buf);
		GlobalFree(buf);
	}
	else
		show_error(hwnd, L"No item selected!");
}

void handle_move1(HWND hwnd)
{
	int selected_id = SendDlgItemMessage(hwnd, ID_LISTBOX2, LB_GETCURSEL, NULL, NULL);
	if (selected_id != LB_ERR)
	{
		int len = SendDlgItemMessage(hwnd, ID_LISTBOX2, LB_GETTEXTLEN, selected_id, NULL);
		TCHAR* buf = (TCHAR*)GlobalAlloc(GPTR, sizeof(TCHAR) * (len + 1));
		SendDlgItemMessage(hwnd, ID_LISTBOX2, LB_GETTEXT, selected_id, (LPARAM)buf);
		if (SendDlgItemMessage(hwnd, ID_LISTBOX1, LB_FINDSTRINGEXACT, NULL, (LPARAM)buf) == LB_ERR)
			SendDlgItemMessage(hwnd, ID_LISTBOX1, LB_ADDSTRING, NULL, (LPARAM)buf);
		GlobalFree(buf);
	}
	else
		show_error(hwnd, L"No item selected!");
}