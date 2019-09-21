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
	po->GetComponent(STRING(MeshComponent))->InitFromFile("./Asset/block.model", MeshComponent::ModelFileMode | MeshComponent::WholeMode);
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

void WorldGenerate(const Vector<std::pair<XMFLOAT3, SpaceGameEngine::String>>& data)
{
	for (int i = 0; i < data.size(); i++)
	{
		BuildBlockObject(CreateVisibleObject(("Block" + std::to_string(i)).data()), data[i].first, data[i].second);
	}
}

Gameplay & GetGameplay()
{
	static GlobalVariable<Gameplay> g_Gameplay;
	return g_Gameplay.Get();
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
	/*if (Game::GetMainGame()->m_KeyboardDevice.IfPress(KEY(W)))
		m_pCameraComponent->GoForward(50.0f*DeltaTime);
	if (Game::GetMainGame()->m_KeyboardDevice.IfPress(KEY(S)))
		m_pCameraComponent->GoForward(-50.0f*DeltaTime);
	if (Game::GetMainGame()->m_KeyboardDevice.IfPress(KEY(A)))
		m_pCameraComponent->GoRight(-50.0f*DeltaTime);
	if (Game::GetMainGame()->m_KeyboardDevice.IfPress(KEY(D)))
		m_pCameraComponent->GoRight(50.0f*DeltaTime);
	if (Game::GetMainGame()->m_KeyboardDevice.IfPress(KEY(LSHIFT)))
		m_pCameraComponent->GoUp(-50.0f*DeltaTime);
	if (Game::GetMainGame()->m_KeyboardDevice.IfPress(KEY(SPACE)))
		m_pCameraComponent->GoUp(50.0f*DeltaTime);

	XMFLOAT3 rotation = m_pTransformComponent->GetRotation();
	DIMOUSESTATE mousestate = Game::GetMainGame()->m_MouseDevice.GetMouseState();
	if (mousestate.lX > 0 && Game::GetMainGame()->m_MouseDevice.IfLeftButtonPress())
		rotation.y += 5.0f*DeltaTime;
	if (mousestate.lX < 0 && Game::GetMainGame()->m_MouseDevice.IfLeftButtonPress())
		rotation.y += -5.0f*DeltaTime;
	if (mousestate.lY > 0 && Game::GetMainGame()->m_MouseDevice.IfLeftButtonPress())
		rotation.x += 5.0f*DeltaTime;
	if (mousestate.lY < 0 && Game::GetMainGame()->m_MouseDevice.IfLeftButtonPress())
		rotation.x += -5.0f*DeltaTime;

	int weight = Game::GetMainGame()->m_Window.GetWindowWidth();
	int height = Game::GetMainGame()->m_Window.GetWindowHeight();
	Game::GetMainGame()->m_Window.SetCursorPosition(weight / 2, height / 2);
	Game::GetMainGame()->m_Window.ChangeIfShowCursor(false);
	m_pTransformComponent->SetRotation(rotation);*/
	GetGameplay().Run(DeltaTime);
}

void Gameplay::Init(Object* player)
{
	m_pPlayer = CreateVisibleObject("PlayerBlock");
	BuildBlockObject(m_pPlayer, GetRealPosition(1, 1, 1), "./Asset/player.dds");
	m_pPlayer->RequireObject(player);
	m_pPlayerController = player;
}

void Gameplay::LoadLevel(const SpaceGameEngine::String & filename)
{
	m_InputBuffer = Direction::Null;
	m_Score = 0;
	m_PlayerPosition = { 7,3 };
	m_pPlayer->GetComponent<TransformComponent>()->SetPosition(GetRealPosition(m_PlayerPosition.first, m_PlayerPosition.second, 1));
	memset(m_Boxes, NULL, sizeof(m_Boxes));
	Vector<std::pair<XMFLOAT3, String>> data;
	Queue<int> indexs;
	File file(filename, FileMode::Read);
	for (int i = 0; i < 11; i++)
		for (int j = 0; j < 11; j++)
		{
			file >> (unsigned char&)m_Ground[i][j];
			if (m_Ground[i][j] != BlockType::Empty)
				data.push_back({ GetRealPosition(j,i,0) , GetTexture(m_Ground[i][j]) });
			if (m_Ground[i][j] == BlockType::Destination)
				m_Destination += 1;
		}
	for (int i = 0; i < 11; i++)
		for (int j = 0; j < 11; j++)
		{
			file >> (unsigned char&)m_Front[i][j];
			if (m_Front[i][j] != BlockType::Empty)
				data.push_back({ GetRealPosition(j,i,1) , GetTexture(m_Front[i][j]) });
			if (m_Front[i][j] == BlockType::Box)
				indexs.push(data.size() - 1);
		}
	WorldGenerate(data);
	for (int i = 0; i < 11; i++)
		for (int j = 0; j < 11; j++)
		{
			if (m_Front[i][j] == BlockType::Box)
			{
				m_Boxes[i][j] = GetScene()->GetObjectByName(("Block" + std::to_string(indexs.front())).data());
				m_Boxes[i][j]->RequireObject(m_pPlayerController);
				indexs.pop();
			}
		}
}

void Gameplay::Run(float deltatime)
{
	static const float circle = 0.3;
	static float time_cot = 0;
	if (time_cot + deltatime >= circle)
	{
		time_cot = 0;
		switch (m_InputBuffer)
		{
		case Gameplay::Direction::Left:
			if (m_PlayerPosition.first <= 0)
				break;
			else if (m_Front[m_PlayerPosition.second][m_PlayerPosition.first - 1] == BlockType::Empty)
			{
				m_PlayerPosition.first -= 1;
				m_pPlayer->GetComponent<TransformComponent>()->SetPosition(GetRealPosition(m_PlayerPosition.first, m_PlayerPosition.second, 1));
				break;
			}
			else if (m_Front[m_PlayerPosition.second][m_PlayerPosition.first - 1] == BlockType::Box)
			{
				if (m_PlayerPosition.first == 1)
					break;
				else if (m_Front[m_PlayerPosition.second][m_PlayerPosition.first - 2] != BlockType::Empty)
					break;
				m_Front[m_PlayerPosition.second][m_PlayerPosition.first - 2] = BlockType::Box;
				m_Front[m_PlayerPosition.second][m_PlayerPosition.first - 1] = BlockType::Empty;
				m_Boxes[m_PlayerPosition.second][m_PlayerPosition.first - 2] = m_Boxes[m_PlayerPosition.second][m_PlayerPosition.first - 1];
				m_Boxes[m_PlayerPosition.second][m_PlayerPosition.first - 1] = nullptr;
				m_Boxes[m_PlayerPosition.second][m_PlayerPosition.first - 2]->GetComponent<TransformComponent>()->SetPosition(GetRealPosition(m_PlayerPosition.first - 2, m_PlayerPosition.second, 1));
				m_PlayerPosition.first -= 1;
				m_pPlayer->GetComponent<TransformComponent>()->SetPosition(GetRealPosition(m_PlayerPosition.first, m_PlayerPosition.second, 1));
				break;
			}
			break;
		case Gameplay::Direction::Down:
			if (m_PlayerPosition.second >= 10)
				break;
			else if (m_Front[m_PlayerPosition.second + 1][m_PlayerPosition.first] == BlockType::Empty)
			{
				m_PlayerPosition.second += 1;
				m_pPlayer->GetComponent<TransformComponent>()->SetPosition(GetRealPosition(m_PlayerPosition.first, m_PlayerPosition.second, 1));
				break;
			}
			else if (m_Front[m_PlayerPosition.second + 1][m_PlayerPosition.first] == BlockType::Box)
			{
				if (m_PlayerPosition.second == 9)
					break;
				else if (m_Front[m_PlayerPosition.second + 2][m_PlayerPosition.first] != BlockType::Empty)
					break;
				m_Front[m_PlayerPosition.second + 2][m_PlayerPosition.first] = BlockType::Box;
				m_Front[m_PlayerPosition.second + 1][m_PlayerPosition.first] = BlockType::Empty;
				m_Boxes[m_PlayerPosition.second + 2][m_PlayerPosition.first] = m_Boxes[m_PlayerPosition.second + 1][m_PlayerPosition.first];
				m_Boxes[m_PlayerPosition.second + 1][m_PlayerPosition.first] = nullptr;
				m_Boxes[m_PlayerPosition.second + 2][m_PlayerPosition.first]->GetComponent<TransformComponent>()->SetPosition(GetRealPosition(m_PlayerPosition.first, m_PlayerPosition.second + 2, 1));
				m_PlayerPosition.second += 1;
				m_pPlayer->GetComponent<TransformComponent>()->SetPosition(GetRealPosition(m_PlayerPosition.first, m_PlayerPosition.second, 1));
				break;
			}
			break;
		case Gameplay::Direction::Up:
			if (m_PlayerPosition.second <= 0)
				break;
			else if (m_Front[m_PlayerPosition.second - 1][m_PlayerPosition.first] == BlockType::Empty)
			{
				m_PlayerPosition.second -= 1;
				m_pPlayer->GetComponent<TransformComponent>()->SetPosition(GetRealPosition(m_PlayerPosition.first, m_PlayerPosition.second, 1));
				break;
			}
			else if (m_Front[m_PlayerPosition.second - 1][m_PlayerPosition.first] == BlockType::Box)
			{
				if (m_PlayerPosition.second == 1)
					break;
				else if (m_Front[m_PlayerPosition.second - 2][m_PlayerPosition.first] != BlockType::Empty)
					break;
				m_Front[m_PlayerPosition.second - 2][m_PlayerPosition.first] = BlockType::Box;
				m_Front[m_PlayerPosition.second - 1][m_PlayerPosition.first] = BlockType::Empty;
				m_Boxes[m_PlayerPosition.second - 2][m_PlayerPosition.first] = m_Boxes[m_PlayerPosition.second - 1][m_PlayerPosition.first];
				m_Boxes[m_PlayerPosition.second - 1][m_PlayerPosition.first] = nullptr;
				m_Boxes[m_PlayerPosition.second - 2][m_PlayerPosition.first]->GetComponent<TransformComponent>()->SetPosition(GetRealPosition(m_PlayerPosition.first, m_PlayerPosition.second - 2, 1));
				m_PlayerPosition.second -= 1;
				m_pPlayer->GetComponent<TransformComponent>()->SetPosition(GetRealPosition(m_PlayerPosition.first, m_PlayerPosition.second, 1));
				break;
			}
			break;
		case Gameplay::Direction::Right:
			if (m_PlayerPosition.first >= 10)
				break;
			else if (m_Front[m_PlayerPosition.second][m_PlayerPosition.first + 1] == BlockType::Empty)
			{
				m_PlayerPosition.first += 1;
				m_pPlayer->GetComponent<TransformComponent>()->SetPosition(GetRealPosition(m_PlayerPosition.first, m_PlayerPosition.second, 1));
				break;
			}
			else if (m_Front[m_PlayerPosition.second][m_PlayerPosition.first + 1] == BlockType::Box)
			{
				if (m_PlayerPosition.first == 9)
					break;
				else if (m_Front[m_PlayerPosition.second][m_PlayerPosition.first + 2] != BlockType::Empty)
					break;
				m_Front[m_PlayerPosition.second][m_PlayerPosition.first + 2] = BlockType::Box;
				m_Front[m_PlayerPosition.second][m_PlayerPosition.first + 1] = BlockType::Empty;
				m_Boxes[m_PlayerPosition.second][m_PlayerPosition.first + 2] = m_Boxes[m_PlayerPosition.second][m_PlayerPosition.first + 1];
				m_Boxes[m_PlayerPosition.second][m_PlayerPosition.first + 1] = nullptr;
				m_Boxes[m_PlayerPosition.second][m_PlayerPosition.first + 2]->GetComponent<TransformComponent>()->SetPosition(GetRealPosition(m_PlayerPosition.first + 2, m_PlayerPosition.second, 1));
				m_PlayerPosition.first += 1;
				m_pPlayer->GetComponent<TransformComponent>()->SetPosition(GetRealPosition(m_PlayerPosition.first, m_PlayerPosition.second, 1));
				break;
			}
			break;
		default:
			break;
		}
		m_InputBuffer = Direction::Null;
	}
	else
	{
		time_cot += deltatime;
		if (Game::GetMainGame()->m_KeyboardDevice.IfPress(KEY(W)))
			m_InputBuffer = Direction::Up;
		if (Game::GetMainGame()->m_KeyboardDevice.IfPress(KEY(S)))
			m_InputBuffer = Direction::Down;
		if (Game::GetMainGame()->m_KeyboardDevice.IfPress(KEY(A)))
			m_InputBuffer = Direction::Left;
		if (Game::GetMainGame()->m_KeyboardDevice.IfPress(KEY(D)))
			m_InputBuffer = Direction::Right;
	}
}

SpaceGameEngine::String Gameplay::GetTexture(BlockType type)
{
	switch (type)
	{
	case Gameplay::BlockType::Empty:
		break;
	case Gameplay::BlockType::Solid:
		return "./Asset/solid.dds";
		break;
	case Gameplay::BlockType::Destination:
		return "./Asset/destination.dds";
		break;
	case Gameplay::BlockType::Wall:
		return "./Asset/wall.dds";
		break;
	case Gameplay::BlockType::Box:
		return "./Asset/box.dds";
		break;
	default:
		break;
	}
}

XMFLOAT3 Gameplay::GetRealPosition(int x, int y, int high)
{
	return { (float)(-10 + x * 2), (float)(10 - y * 2), (float)(high == 0 ? 30 : 28) };
}
