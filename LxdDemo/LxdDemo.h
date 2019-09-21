#pragma once
#include "Game/Game/Include/Game.h"
#include "Game/Component/Include/ComponentFactory.h"

SpaceGameEngine::Object* CreateVisibleObject(const SpaceGameEngine::String& name);

void BuildBlockObject(SpaceGameEngine::Object* po, const XMFLOAT3& position, const SpaceGameEngine::String& texture_name);

SpaceGameEngine::Object* CreateLight(const SpaceGameEngine::String& name, const SpaceGameEngine::String& filename);

class ControllerComponent :public SpaceGameEngine::Component
{
public:
	REGISTER_COMPONENT(ControllerComponent);

	ControllerComponent();

	virtual void Start()override;
	virtual void Run(float DeltaTime) override;
private:
	SpaceGameEngine::TransformComponent* m_pTransformComponent;
	SpaceGameEngine::CameraComponent* m_pCameraComponent;
};

SpaceGameEngine::Object* CreatePlayerObject();

void WorldGenerate(const SpaceGameEngine::Vector<std::pair<XMFLOAT3, SpaceGameEngine::String>>& data);

class Gameplay
{
public:
	enum class BlockType :unsigned char
	{
		Empty = 0,
		Solid = 1,
		Destination = 2,
		Wall = 3,
		Box = 4
	};
	enum class Direction : char
	{
		Null = -1,
		Left = 0,
		Down = 1,
		Up = 2,
		Right = 3
	};
	void Init(SpaceGameEngine::Object* player);
	void LoadLevel(const SpaceGameEngine::String& filename);
	void Run(float deltatime);
private:
	SpaceGameEngine::String GetTexture(BlockType type);
	XMFLOAT3 GetRealPosition(int x, int y, int high);
	SpaceGameEngine::Object* m_Boxes[11][11];
	BlockType m_Ground[11][11];
	BlockType m_Front[11][11];
	int m_Score, m_Destination;
	std::pair<int, int> m_PlayerPosition;
	SpaceGameEngine::Object* m_pPlayer;
	Direction m_InputBuffer;
	SpaceGameEngine::Object* m_pPlayerController;
};

Gameplay& GetGameplay();