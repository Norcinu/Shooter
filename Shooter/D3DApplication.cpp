#include "D3DApplication.h"
#include "Visualisation.h"
#include <iostream>

const int width = 640;
const int height = 480;

D3DApplication::D3DApplication(void) : running(false), window(NULL)
{
	WNDCLASS wc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = 0;
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	wc.hIcon = 0;
	wc.hInstance = 0;
	wc.lpfnWndProc = wndproc;
	wc.lpszClassName = "d3d_application";
	wc.lpszMenuName = 0;
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	
	if ( 0 == RegisterClass( &wc ) )
		throw std::runtime_error( "RegisterClass failed" );

	window = CreateWindow("d3d_application", "2D Scrolling Shooter", WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 
		CW_USEDEFAULT, CW_USEDEFAULT, width, height, 0, 0, 0, 0);
	
	if (window == 0)
		throw std::runtime_error("CreateWindow Failed.");

	SetWindowLong(window, GWL_USERDATA, (long)this);

	OnInit();
}

D3DApplication::~D3DApplication(void)
{
	delete vis;

	DestroyWindow(window);
}

void D3DApplication::run()
{
	ShowWindow(window, SW_SHOW);

	MSG msg;
	running = true;
	long start_time = timeGetTime();

	while(running)
	{
		while (PeekMessage(&msg, 0, 0, 0, PM_REMOVE) != 0)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		OnUpdate(0.001f * (timeGetTime() - start_time));
		OnDraw();
	}
}

void D3DApplication::OnDraw()
{
	if (vis!=nullptr) 
	{
		vis->BeginScene();
		vis->EndScene();
	}
}

bool D3DApplication::OnEvent(UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch ( msg )
	{
	case WM_SIZE:
		break;
	default:
		return false;
	}
	return true;
}

void D3DApplication::OnInit()
{
	vis = new Visualisation;
	if (!vis->Initialise(this->window, height, width))
		std::cerr << "DANGER DANGER!!";
}

void D3DApplication::OnUpdate(float time)
{
}

long WINAPI D3DApplication::wndproc(HWND wnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	D3DApplication *app = (D3DApplication*)GetWindowLong(wnd, GWL_USERDATA);
	if (app == 0)
		return DefWindowProc(wnd, msg, wParam, lParam);

	switch (msg)
	{
	case WM_CLOSE:
		ShowWindow(app->window, SW_HIDE);
		app->running = false;
		break;
	}

	if (!app->OnEvent(msg, wParam, lParam) /*== false*/)
		return DefWindowProc(wnd, msg, wParam, lParam);

	return 0;
}