#pragma once
#include <Windows.h>
#include <string>
#include <tchar.h>
#include "Color.h"

namespace Orange {
	struct StateInfo {
		LRESULT(*handle_message) (HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	};

	class Window
	{
	public:		//Constructor and Destructor
		Window(std::wstring _title, std::wstring _class_name, HINSTANCE _h_instance, int _n_cmd_show);
		~Window();

	private:	//Member Variables
		HBRUSH w_background_color;	//Background Color
		int w_cmd_show;				//Startup Info: Command Line Arguments
		HINSTANCE w_h_instance;		//Stored instance handle for use in Win32 API calls such as FindResource
		std::wstring w_class_name;	//Window Class Name
		std::wstring w_title;		//Window Title Bar Name
		HWND w_hwnd;				//Window Handle
		HWND w_parent_hwnd;			//Window Handle of Parent Window
		WNDCLASSEX w_cex;			//Window Data Struct
		StateInfo* pState = nullptr;//Window State Information
		int w_width, w_height;		//Window width and height

	public:		//Window Creation
		void CreateMainWindow(int _width, int _height, int start_x, int start_y);
		void CreateChildWindow(HWND hwnd, int _width, int _height, int start_x, int start_y);

	private:	//Window Procedure
		static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam); 

		//Window Setup
		void SetupWindowClassEx();
		void RegisterWindow();
		void InstanceWindow(int start_x, int start_y);

	public:
		//Getters
		//StateInfo* GetAppState();
		HWND GetHWND();

		//Setters
		void SetTitle(LPCWSTR _title);
		void SetBackgroundColor(Color color);
	};
}

