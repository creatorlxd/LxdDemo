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
#include "Game/Component/Include/ComponentFactory.h"
#include "Game/Object/Include/Object.h"
#include "Game/Asset/Include/ShaderAsset.h"
#include "Graphics/RenderSystem/Include/RenderObject.h"

namespace SpaceGameEngine
{
	/*
	����ʹ��DefaultEffectShader��
	�����Ҫ��ȡ�Զ����Shader��ʽ����Ҫ�̳���DefaultEffectShader����д���ִ��룬��дһ����ص�Asset��һ��Component��
	���ԣ����Component��DefaultShaderAsset���൱������ģ��������������
	*/
	class ShaderComponent :public Component
	{
	public:
		REGISTER_COMPONENT(ShaderComponent);

		ShaderComponent();

		void InitFromFile(const String& filename, int mode = 0);
		void Start();

		void Copy(Component* pc);
	};
}