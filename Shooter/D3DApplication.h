#ifndef D3D_APPLICATION_H
#define D3D_APPLICATION_H

#define VC_EXTRALEAN
#include <windows.h>
#include <stdexcept>

class Visualisation;

class D3DApplication
{
public:
	D3DApplication(void);
	~D3DApplication(void);
	public:
	void  run ( );
private:
	void  OnDraw   ( );
	bool  OnEvent  ( UINT msg, WPARAM wParam, LPARAM lParam );
	void  OnInit   ( );
	void  OnUpdate ( float time );
private:
	static LRESULT WINAPI wndproc ( HWND wnd, UINT msg, WPARAM wParam, LPARAM lParam );
private:
	Visualisation *vis;
	bool running;
	HWND window;
};

#endif
