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
	auto block_1 = CreateVisibleObject("Block1");
	auto block_2 = CreateVisibleObject("Block2");
	BuildBlockObject(block_1, { 0,0,10 }, "./Asset/test.dds");
	BuildBlockObject(block_2, { 0,0,-10 }, "./Asset/test.dds");
	CreateLight("WorldLight", "./Asset/world.light");
	CreateLight("Light1", "./Asset/test.light");
	CreatePlayerObject();
	//
	game.StartRunGame();
	return 0;
}