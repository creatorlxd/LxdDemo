#include "Game/Game/Include/Game.h"
#pragma comment(lib,"Space.lib")

using namespace SpaceGameEngine;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	Game game;
	game.Init(hInstance, hPrevInstance, lpCmdLine, nShowCmd);
	game.StartRunGame();
	return 0;
}