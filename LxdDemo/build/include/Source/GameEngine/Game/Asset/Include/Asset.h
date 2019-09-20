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
#include "Space.h"
#include "Common/Utility/Include/File.h"
#include "Common/Utility/Include/GlobalVariable.h"

namespace SpaceGameEngine
{
	struct Asset
	{
		Asset();
		virtual ~Asset();
		String m_FileName, m_TypeName;
		virtual void InitFromFile(const String& filename);
	};

	class AssetManager
	{
	public:
		~AssetManager();
		template<typename T>
		const T* NewAssetFromFile(const String& filename);
		bool AddAsset(Asset* pa);
		const Asset* GetAsset(const String& name);
	public:
		friend struct StdAllocatorInterface;
		friend struct MemoryManagerAllocatorInterface;
	private:
		HashMap<String, Asset*> m_Content;
	};

	AssetManager& GetAssetManager();

	template<typename T>
	inline const T * AssetManager::NewAssetFromFile(const String & filename)
	{
		T* re = MemoryManager::New<T>();
		re->InitFromFile(filename);
		GetAssetManager().AddAsset((Asset*)re);
		return re;
	}

	template<typename T>
	const T* GetAssetByFileName(const String& filename)
	{
		auto rebuff = GetAssetManager().GetAsset(filename);
		if (rebuff)
		{
			return dynamic_cast<const T*>(rebuff);
		}
		else
		{
			return GetAssetManager().NewAssetFromFile<T>(filename);
		}
	}
}