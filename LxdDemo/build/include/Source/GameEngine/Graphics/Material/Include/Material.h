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

namespace SpaceGameEngine
{
	struct Material			//����
	{
		Material();

		XMFLOAT4 m_Ambient;
		XMFLOAT4 m_Diffuse;
		XMFLOAT4 m_Specular;	// Specular.w = SpecularPower
		XMFLOAT4 m_Reflect;		//TODO:do not use now
		XMFLOAT4 m_Emissive;
	};
};