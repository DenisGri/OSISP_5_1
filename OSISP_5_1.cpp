#include <Windows.h>
#include <tchar.h>

int sx = 100;
int sy = 10;
int is_fig = 1;
int is_up = 0;
int x_end = 500;
int y_end = 500;
HWND h_main_window;


void draw_rectangle(const HWND h_wnd, const int sx, const int sy, int check)
{
	PAINTSTRUCT ps;
	const HDC hdc = BeginPaint(h_wnd, &ps);
	const HBRUSH hbrush = CreateSolidBrush(RGB(
		static_cast<BYTE>(rand() % 255),
		static_cast<BYTE>(rand() % 255),
		static_cast<BYTE>(rand() % 255)
	));
	SelectObject(hdc, hbrush);
	if (check == 1)
		Rectangle(hdc, sx, sy, sx + 70, sy + 50);
	else
		Ellipse(hdc, sx, sy, sx + 70, sy + 50);
	EndPaint(h_wnd, &ps);
}


auto CALLBACK wnd_proc(HWND, UINT, WPARAM, LPARAM) -> LRESULT;
TCHAR WinName[] = _T("MainFrame");
auto APIENTRY wWinMain(HINSTANCE This,
                       HINSTANCE Prev,
                       LPTSTR cmd,
                       int mode) -> int
{
	MSG msg;
	WNDCLASS wc;
	wc.hInstance = This;
	wc.lpszClassName = WinName;
	wc.lpfnWndProc = wnd_proc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.lpszMenuName = nullptr;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);
	if (!RegisterClass(&wc)) return 0;
	const HWND hWnd = CreateWindow(WinName,
	                               _T("Laba1"),
	                               WS_OVERLAPPEDWINDOW,
	                               CW_USEDEFAULT,
	                               CW_USEDEFAULT,
	                               500,
	                               500,
	                               HWND_DESKTOP,
	                               NULL,
	                               This,
	                               NULL);
	ShowWindow(hWnd, mode);
	h_main_window = hWnd;
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}


LRESULT CALLBACK wnd_proc(HWND hWnd, UINT message,
                          WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_SIZE:
		x_end = LOWORD(lParam);
		y_end = HIWORD(lParam);
		break;
	case WM_LBUTTONDOWN:
		is_fig = -is_fig;
		InvalidateRect(h_main_window, nullptr, TRUE);
		UpdateWindow(h_main_window);
		draw_rectangle(h_main_window, sx, sy, is_fig);
		break;
	case WM_KEYUP:
		is_up = 0;
		break;
	case WM_MOUSEWHEEL:
		if (static_cast<short>(HIWORD(wParam)) > 0 && !(wParam & MK_SHIFT)) {
			if (sy > 0)
				sy -= 2;
			else
				sy += 2;
			draw_rectangle(h_main_window, sx, sy, is_fig);
			InvalidateRect(h_main_window, nullptr, TRUE);
			UpdateWindow(h_main_window);
		}
		else if (static_cast<short>(HIWORD(wParam)) < 0 && !(wParam & MK_SHIFT)) {
			if (sy + 50 < y_end)
				sy += 2;
			else
				sy -= 2;
			draw_rectangle(h_main_window, sx, sy, is_fig);
			InvalidateRect(h_main_window, nullptr, TRUE);
			UpdateWindow(h_main_window);
		}
		if (static_cast<short>(HIWORD(wParam)) > 0 && wParam & MK_SHIFT) {
			if (sx > 0)
				sx -= 2;
			else
				sx += 2;
			draw_rectangle(h_main_window, sx, sy, is_fig);
			InvalidateRect(h_main_window, nullptr, TRUE);
			UpdateWindow(h_main_window);
		}
		else if (static_cast<short>(HIWORD(wParam)) < 0 && wParam & MK_SHIFT) {
			if (sx + 70 < x_end)
				sx += 2;
			else
				sx -= 2;
			draw_rectangle(h_main_window, sx, sy, is_fig);
			InvalidateRect(h_main_window, nullptr, TRUE);
			UpdateWindow(h_main_window);
		}
		break;
	case WM_KEYDOWN:
		if (wParam == VK_UP) {
			if (is_up) {
				sy += 2;
				draw_rectangle(h_main_window, sx, sy, is_fig);
				InvalidateRect(h_main_window, nullptr, TRUE);
				UpdateWindow(h_main_window);
			}
			else {

				sy -= 2;
				draw_rectangle(h_main_window, sx, sy, is_fig);
				InvalidateRect(h_main_window, nullptr, TRUE);
				UpdateWindow(h_main_window);
				if (sy <= 0) {
					is_up = 1;
				}
			}
		}
		if (wParam == VK_DOWN) {
			if (is_up) {
				sy -= 2;
				draw_rectangle(h_main_window, sx, sy, is_fig);
				InvalidateRect(h_main_window, nullptr, TRUE);
				UpdateWindow(h_main_window);
			}
			else {
				sy += 2;
				draw_rectangle(h_main_window, sx, sy, is_fig);
				InvalidateRect(h_main_window, nullptr, TRUE);
				UpdateWindow(h_main_window);
				if (sy + 50 > y_end) {
					is_up = 1;
				}
			}
		}
		if (wParam == VK_LEFT) {
			if (is_up) {
				sx += 2;
				draw_rectangle(h_main_window, sx, sy, is_fig);
				InvalidateRect(h_main_window, nullptr, TRUE);
				UpdateWindow(h_main_window);
			}
			else {

				sx -= 2;
				draw_rectangle(h_main_window, sx, sy, is_fig);
				InvalidateRect(h_main_window, nullptr, TRUE);
				UpdateWindow(h_main_window);
				if (sx <= 0) {
					is_up = 1;
				}
			}
		}
		if (wParam == VK_RIGHT) {
			if (is_up) {
				sx -= 2;
				draw_rectangle(h_main_window, sx, sy, is_fig);
				InvalidateRect(h_main_window, nullptr, TRUE);
				UpdateWindow(h_main_window);
			}
			else {
				sx += 2;
				draw_rectangle(h_main_window, sx, sy, is_fig);
				InvalidateRect(h_main_window, nullptr, TRUE);
				UpdateWindow(h_main_window);
				if (sx + 70 > x_end) {
					is_up = 1;
				}
			}
		}
		break;
	case WM_PAINT:
		draw_rectangle(h_main_window, sx, sy, is_fig);
		break;
	case WM_DESTROY: PostQuitMessage(0);
		break;
	default: return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
