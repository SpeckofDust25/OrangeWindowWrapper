#include <Windows.h>
#include "Window.h"

#ifndef UNICODE
#define UNICODE
#endif

int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR     lpCmdLine,
	_In_ int       nCmdShow) {

	Orange::Color background_color_one(150, 0, 0);
	Orange::Color background_color_two(0, 150, 0);

	Orange::Window* main_window = new Orange::Window(L"Main Window", L"DesktopApplication", hInstance, nCmdShow);
	main_window->CreateMainWindow(400, 100, CW_USEDEFAULT, CW_USEDEFAULT);
	main_window->SetBackgroundColor(background_color_one);

	Orange::Window* child_window = new Orange::Window(L"Child Window", L"ChildApplication", hInstance, nCmdShow);
	child_window->CreateChildWindow(main_window->GetHWND(), 400, 100, CW_USEDEFAULT, CW_USEDEFAULT);
	child_window->SetBackgroundColor(background_color_two);

	//Main Message Loop
	MSG msg;
	while (GetMessageW(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);	//Translates Keystrokes
		DispatchMessage(&msg);		//Tells the operating system to call the window procedure of the window that is the target of the message
	}

	delete main_window;

	return (int)msg.wParam;
}