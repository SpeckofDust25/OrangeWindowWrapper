#include "Window.h"

namespace Orange {

    //Constructor and Destructor
    Window::Window(std::wstring _title, std::wstring _class_name, HINSTANCE _h_instance, int _n_cmd_show) {
        w_title = _title;
        w_class_name = _class_name;
        w_h_instance = _h_instance;
        w_cmd_show = _n_cmd_show;
    }

    Window::~Window() {

    }

    //Window Types
    void Window::CreateMainWindow(int _width, int _height, int start_x, int start_y) {
        w_width = _width;
        w_height = _height;

        SetupWindowClassEx();
        RegisterWindow();
        InstanceWindow(start_x, start_y);
    }

    void Window::CreateChildWindow(HWND hwnd, int _width, int _height, int _start_x, int _start_y) {
        w_width = _width;
        w_height = _height;
        w_parent_hwnd = hwnd;

        SetupWindowClassEx();
        RegisterWindow();
        InstanceWindow(_start_x, _start_y);
    }

    //Window Procedure
    LRESULT Window::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
        PAINTSTRUCT ps;
        HDC hdc;
        TCHAR greeting[] = _T("Hello, Windows desktop!");

        switch (message)
        {
        case WM_PAINT:
            hdc = BeginPaint(hWnd, &ps);

            // Here your application is laid out.
            // For this introduction, we just print out "Hello, Windows desktop!"
            // in the top left corner.

            ;
            FillRect(hdc, &ps.rcPaint, CreateSolidBrush(RGB(150, 0, 0)));
            TextOut(hdc,
                5, 5,
                greeting, _tcslen(greeting));
            // End application-specific layout section.

            EndPaint(hWnd, &ps);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }

        return 0;
    }

    //Window Setup
    void Window::SetupWindowClassEx() {
        w_cex.cbSize = sizeof(WNDCLASSEX);
        w_cex.style = CS_HREDRAW | CS_VREDRAW;
        w_cex.lpfnWndProc = WndProc;
        w_cex.cbClsExtra = 0;
        w_cex.cbWndExtra = 0;
        w_cex.hInstance = w_h_instance;
        w_cex.hIcon = LoadIcon(w_cex.hInstance, IDI_APPLICATION);
        w_cex.hCursor = LoadCursor(NULL, IDC_ARROW);
        w_cex.hbrBackground = w_background_color;
        w_cex.lpszMenuName = NULL;
        w_cex.lpszClassName = w_class_name.c_str();
        w_cex.hIconSm = LoadIcon(w_cex.hInstance, IDI_APPLICATION);
    }

    void Window::RegisterWindow() {
        if (!RegisterClassEx(&w_cex))
        {
            MessageBox(NULL,
                _T("Call to RegisterClassEx failed!"),
                _T("Windows Desktop Guided Tour"),
                NULL);

            return;
        }
    }

    void Window::InstanceWindow(int start_x, int start_y) {
        HWND temp_hwnd = NULL;

        if (w_parent_hwnd != NULL) { //
            temp_hwnd = w_parent_hwnd;
        }

        HWND w_hwnd = CreateWindowEx(
            WS_EX_OVERLAPPEDWINDOW,
            w_class_name.c_str(),
            w_title.c_str(),
            WS_OVERLAPPEDWINDOW,
            w_width, w_height,
            start_x, start_y,
            NULL,
            NULL,
            w_cex.hInstance,
            NULL
        );

        if (!w_hwnd)
        {
            MessageBox(NULL,
                _T("Call to CreateWindow failed!"),
                _T("Windows Desktop Guided Tour"),
                NULL);

            return;
        }

        ShowWindow(w_hwnd, w_cmd_show);
        UpdateWindow(w_hwnd);
    }

    //Getters
    /*StateInfo* Window::GetAppState() {
        LONG_PTR ptr = GetWindowLongPtr(w_hwnd, GWLP_USERDATA);
        StateInfo* pState = reinterpret_cast<StateInfo*>(ptr);
        return pState;
    }*/

    HWND Window::GetHWND() {
        return w_hwnd;
    }

    //Setters
    void Window::SetTitle(LPCWSTR newTitle) {	//Param: Should be a Wide Character when passed
        SetWindowTextW(w_hwnd, newTitle);
    }

    void Window::SetBackgroundColor(Color color) {
        w_background_color = CreateSolidBrush(RGB(color.GetR(), color.GetG(), color.GetB()));
    }
}