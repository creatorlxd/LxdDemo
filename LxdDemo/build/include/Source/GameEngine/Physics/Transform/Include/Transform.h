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
	//TODO:给TransformComponent设定多个模式（包括用于渲染模式，绑定摄像机模式，绑定子物体模式（父模式）。。。）不同的Run(...)
	class TransformComponent :public Component				//物体的基本物理信息
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
		XMFLOAT3 m_Position;								//位置坐标
		XMFLOAT3 m_Rotation;								//旋转的弧度
		XMFLOAT3 m_Scale;									//缩放的比例								
	};
}