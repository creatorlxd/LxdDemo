#include "Game/Game/Include/Game.h"
#include "LxdDemo.h"
#pragma comment(lib,"Space.lib")

using namespace SpaceGameEngine;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	Game game;
	Scene scene;
	game.Init(hInstance, hPrevInstance, lpCmdLine, nShowCmd);
	game.m_Window.SetWindow(L"LxdDemo", 800, 600);
	game.SetScene(&scene);
	//
	/*Vector<std::pair<XMFLOAT3, String>> data;
	for (int i = -10; i <= 10; i += 2)
		for (int j = -10; j <= 10; j += 2)
			data.push_back({ {(float)i,(float)j,30},"./Asset/solid.dds" });
	WorldGenerate(data);*/
	GetGameplay().Init(CreatePlayerObject());
	GetGameplay().LoadLevel("./Asset/level1.level");
	CreateLight("WorldLight", "./Asset/world.light");
	//CreateLight("Light1", "./Asset/test.light");

	//
	game.StartRunGame();
	return 0;
}