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