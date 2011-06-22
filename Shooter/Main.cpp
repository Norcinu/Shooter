#include "D3DApplication.h"

int WINAPI WinMain (HINSTANCE instance, HINSTANCE prevInstance, char* cmdLine, int showMode)
{
	D3DApplication app;
	
	app.run();

	return 0;
}