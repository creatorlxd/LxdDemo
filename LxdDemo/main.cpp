#include "SpaceGameEngine.h"
#pragma comment(lib,"Space.lib")

using namespace SpaceGameEngine;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	Window window;
	window.StartRun(hInstance);
	return 0;
}