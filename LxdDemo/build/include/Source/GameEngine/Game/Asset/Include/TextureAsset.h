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
#include "Asset.h"
#include "Common/Utility/Include/Window.h"
#include "Graphics/Texture/Include/Texture.h"

namespace SpaceGameEngine
{
	struct TextureAsset :public Asset
	{
		TextureAsset();
		TextureAsset(const TextureAsset& ta);
		void InitFromFile(const String& filename);

		TextureForShader m_Content;

		TextureAsset& operator = (const TextureAsset& t);
	};
}