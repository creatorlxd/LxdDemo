#include "LxdDemo.h"
#include "Game/Game/Include/SafeGet.h"
#include "Graphics/Mesh/Include/Mesh.h"
#include "Graphics/Material/Include/MaterialComponent.h"
#include "Graphics/Texture/Include/TextureComponent.h"
#include "Graphics/Light/Include/LightComponent.h"

using namespace SpaceGameEngine;

SpaceGameEngine::Object * CreateVisibleObject(const String & name)
{
	Object* re = GetScene()->NewObject(name, ObjectMode::Render);
	Component* ptransform, *pmesh, *pmaterial, *ptexture;
	ptransform = TransformComponent::NewComponent();
	pmesh = MeshComponent::NewComponent();
	pmaterial = MaterialComponent::NewComponent();
	ptexture = TextureComponent::NewComponent();
	re->AddComponent(ptransform);
	re->AddComponent(pmesh);
	re->AddComponent(pmaterial);
	re->AddComponent(ptexture);
	re->SetRootComponent(STRING(TransformComponent));
	pmesh->Attach(ptransform);
	pmaterial->Attach(pmesh);
	ptexture->Attach(pmaterial);
	return re;
}

void BuildBlockObject(Object * po, const XMFLOAT3& position, const SpaceGameEngine::String& texture_name)
{
	po->GetComponent(STRING(MeshComponent))->InitFromFile("./Asset/block.model", MeshComponent::ModelFileMode);
	po->GetComponent(STRING(MaterialComponent))->InitFromFile("./Asset/block.material", MaterialComponent::SingleMode);
	po->GetComponent<TransformComponent>()->SetMode(TransformComponent::ForRenderingMode);
	po->GetComponent<TransformComponent>()->SetPosition(position);
	po->GetComponent(STRING(TextureComponent))->InitFromFile(texture_name, TextureComponent::SingleMode);
}

SpaceGameEngine::Object* CreateLight(const SpaceGameEngine::String & name, const SpaceGameEngine::String & filename)
{
	Object* re = GetScene()->NewObject(name);
	Component *ptransform = TransformComponent::NewComponent(), *plight = LightComponent::NewComponent();
	re->AddComponent(ptransform);
	re->AddComponent(plight);
	re->SetRootComponent(STRING(TransformComponent));
	plight->Attach(ptransform);
	plight->InitFromFile(filename, LightComponent::DynamicMode);
	ptransform->SetMode(TransformComponent::InformationMode);
	return re;
}

SpaceGameEngine::Object * CreatePlayerObject()
{
	Object* re = GetScene()->NewObject("Player");
	Component *pcontroller = ControllerComponent::NewComponent();
	re->AddComponent(pcontroller);
	re->SetRootComponent(STRING(ControllerComponent));
	return re;
}

ControllerComponent::ControllerComponent()
{
	m_TypeName = STRING(ControllerComponent);
}

void ControllerComponent::Start()
{
	m_pTransformComponent = GetScene()->GetObjectByName("DefaultCamera")->GetComponent<TransformComponent>();
	m_pCameraComponent = GetScene()->GetObjectByName("DefaultCamera")->GetComponent<CameraComponent>();
}

void ControllerComponent::Run(float DeltaTime)
{
	if (Game::GetMainGame()->m_KeyboardDevice.IfPress(KEY(W)))
		m_pCameraComponent->GoForward(0.1f);
	if (Game::GetMainGame()->m_KeyboardDevice.IfPress(KEY(S)))
		m_pCameraComponent->GoForward(-0.1f);
	if (Game::GetMainGame()->m_KeyboardDevice.IfPress(KEY(A)))
		m_pCameraComponent->GoRight(-0.1f);
	if (Game::GetMainGame()->m_KeyboardDevice.IfPress(KEY(D)))
		m_pCameraComponent->GoRight(0.1f);
	if (Game::GetMainGame()->m_KeyboardDevice.IfPress(KEY(LSHIFT)))
		m_pCameraComponent->GoUp(-0.1f);
	if (Game::GetMainGame()->m_KeyboardDevice.IfPress(KEY(SPACE)))
		m_pCameraComponent->GoUp(0.1f);

	XMFLOAT3 rotation = m_pTransformComponent->GetRotation();
	DIMOUSESTATE mousestate = Game::GetMainGame()->m_MouseDevice.GetMouseState();
	if (mousestate.lX > 0 && Game::GetMainGame()->m_MouseDevice.IfLeftButtonPress())
		rotation.y += 0.01f;
	if (mousestate.lX < 0 && Game::GetMainGame()->m_MouseDevice.IfLeftButtonPress())
		rotation.y += -0.01f;
	if (mousestate.lY > 0 && Game::GetMainGame()->m_MouseDevice.IfLeftButtonPress())
		rotation.x += 0.01f;
	if (mousestate.lY < 0 && Game::GetMainGame()->m_MouseDevice.IfLeftButtonPress())
		rotation.x += -0.01f;

	int weight = Game::GetMainGame()->m_Window.GetWindowWidth();
	int height = Game::GetMainGame()->m_Window.GetWindowHeight();
	Game::GetMainGame()->m_Window.SetCursorPosition(weight / 2, height / 2);
	Game::GetMainGame()->m_Window.ChangeIfShowCursor(false);
	m_pTransformComponent->SetRotation(rotation);
}
