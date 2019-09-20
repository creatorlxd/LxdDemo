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
#include "Component.h"
#include <functional>

namespace SpaceGameEngine
{
	struct ComponentInformation
	{
		String m_Name;
		size_t m_MemorySize;
		std::function<Component*(void)> m_FactoryFunction;

		ComponentInformation();
		ComponentInformation(const String& name, size_t size);
		ComponentInformation(const String& name, size_t size, std::function<Component*(void)> func);
	};

	class ComponentInformationManager
	{
	public:
		bool AddInformation(const ComponentInformation& info);
		const ComponentInformation& GetInformation(const String& name);
	public:
		friend struct StdAllocatorInterface;
		friend struct MemoryManagerAllocatorInterface;
	private:
		Map<String, ComponentInformation> m_Content;
	};

	ComponentInformationManager& GetComponentInformationManager();
}