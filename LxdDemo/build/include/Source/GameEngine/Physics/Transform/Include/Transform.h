/*
Copyright 2018 creatorlxd

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/
#pragma once 
#include "Game/Object/Include/Object.h"
#include "Common/Utility/Include/Window.h"
#include "Game/Scene/Include/SceneData.h"
#include "Game/Asset/Include/TransformAsset.h"
#include "Math/Common/Include/XMathExtension.h"
#include "Graphics/RenderSystem/Include/RenderSystem.h"


namespace SpaceGameEngine
{
	//TODO:��TransformComponent�趨���ģʽ������������Ⱦģʽ���������ģʽ����������ģʽ����ģʽ������������ͬ��Run(...)
	class TransformComponent :public Component				//����Ļ���������Ϣ
	{
	public:
		REGISTER_COMPONENT(TransformComponent);

		static const int ForRenderingMode = 1 << 0;
		static const int InformationMode = 1 << 1;
		static const int ChildTransformMode = 1 << 2;

		TransformComponent();
		~TransformComponent();

		void InitFromFile(const String& filename, int mode = 0);
		void Start();
		void Run(float DeltaTime);
		void CleanUp();
		void Copy(Component* pc);

		void SetPosition(const XMFLOAT3& position);
		void SetRotation(const XMFLOAT3& rotation);
		void SetScale(const XMFLOAT3& scale);

		XMFLOAT3 GetPosition();
		XMFLOAT3 GetRotation();
		XMFLOAT3 GetScale();

	private:
		XMFLOAT3 m_Position;								//λ������
		XMFLOAT3 m_Rotation;								//��ת�Ļ���
		XMFLOAT3 m_Scale;									//���ŵı���								
	};
}