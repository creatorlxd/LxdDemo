#include "Game/Game/Include/Game.h"
#include "LxdDemo.h"
#pragma comment(lib,"Space.lib")

using namespace SpaceGameEngine;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	Game game;
	game.Init(hInstance, hPrevInstance, lpCmdLine, nShowCmd);
	game.m_Window.SetWindow(L"LxdDemo", 800, 600);
	//
	/*Vector<std::pair<XMFLOAT3, String>> data;
	for (int i = -10; i <= 10; i += 2)
		for (int j = -10; j <= 10; j += 2)
			data.push_back({ {(float)i,(float)j,30},"./Asset/solid.dds" });
	WorldGenerate(data);*/
	Vector<String> level_list = { "./Asset/level1.level" ,"./Asset/level2.level" };
	Queue<String> buffer;
	for (auto i : level_list)
		buffer.push(i);
	GetGameplay().Init(buffer);
	//CreateLight("Light1", "./Asset/test.light");

	//
	game.StartRunGame();
	return 0;
}