﻿/*
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
#include "Common/Utility/Include/File.h"

namespace SpaceGameEngine
{
	class TransformComponent;

	template<typename T, typename AllocatorInterface = MemoryManagerAllocatorInterface>
	class DoubleBuffer
	{
	public:
		template<typename... Arg>
		DoubleBuffer(Arg&&... arg)
		{
			m_pNow = AllocatorInterface::template New<T>(std::forward<Arg>(arg)...);
			m_pLast = AllocatorInterface::template NewSize<T>(sizeof(T));
			memcpy(m_pLast, m_pNow, sizeof(T));
		}
		~DoubleBuffer()
		{
			AllocatorInterface::Delete(m_pNow);
			AllocatorInterface::Delete(reinterpret_cast<uint8_t*>(m_pLast));
		}

		void Swap()
		{
			memcpy(m_pLast, m_pNow, sizeof(T));
		}

		T& GetNow()
		{
			return *m_pNow;
		}

		T& GetLast()
		{
			return *m_pLast;
		}
	private:
		T * m_pLast;
		T * m_pNow;
	};

	class RenderObject;

	Vector<std::pair<String, std::pair<String, int>>> ReadAssetListFromFile(const String& filename);	//从文件中读取资产文件列表

	enum ObjectMode :uint32_t
	{
		Common = 0,
		Render = 1
	};

	class Object			//基本物体对象
	{
	public:
		Object();
		~Object();
		Component* GetComponent(const String& name);		//获取组件的指针
		template<typename T>
		T* GetComponent();
		/*
		添加组件，并不连接
		注意：如果是在Scene运行过程中添加的，并且该Object是在Scene开始运行之前就已经创建好的，则应手动调用该Componentd的Start方法
		*/
		bool AddComponent(Component* pc);
		bool DeleteComponent(const String& name);			//删除组件，并去除连接

		void Start();											//开始时运行
		void InitFromFile(const Vector<std::pair<String, std::pair<String, int>>>& filenames);	//从文件初始化
		void InitFromFile(const String& filename);										//通过资产文件列表来初始化
		void InitFromXMLFile(const String& filename);
		void Run(float DeltaTime);								//每帧运行时的操作
		void EveryFrameCleanUp();

		bool SetRootComponent(const String& name);			//设置根组件
		Component* GetRootComponent();							//获取根组件

		bool IfRun();						//是否每帧运行
		bool IfUse();						//是否使用
		void ChangeIfRun(bool b);			//更改每帧是否运行
		void ChangeIfUse(bool b);			//更改是否使用

		void ClearRunState();				//将m_IfRun设为false
		bool GetIfHaveRun();

		void ProduceMessage(Component* from, unsigned int message);
		Component* GetComponentByMessage(unsigned int message);
		void ClearMessage();

		Vector<Object*>& GetChildren();
		void AddChildObject(Object* po);
		void DeleteChildObject(Object* po);
		Object* GetFatherObject();
		void SetFatherObject(Object* po);
		bool IfChild();

		friend void ConnectObject(Object* father, Object* child);
		friend void DisconObject(Object* child);

		void SetRenderObject(RenderObject* pro);
		RenderObject* GetRenderObject();

		void ReleaseComponentWhenRuntime();

		void RequireObject(Object* po);
		void UnrequireObject(Object* po);
		const Vector<Object*>& GetRequiredObject();

		void SetMode(ObjectMode mode);
		ObjectMode GetMode();
	private:
		void Attach(Object* po);
		void Discon();						//断开
		/*
		作为子组件所要进行的更新方法。
		state:
			0:connect state
			1:update state
		*/
		void ChildObjectUpdate(int state);
	protected:
		Map<String, Component*> m_Components;			//组件们...
		Component* m_pRootComponent;							//根组件
		Map<unsigned int, Component*> m_Message;
		Object* m_pFather;									//父对象
		Vector<Object*> m_Children;							//子对象
		RenderObject* m_pRenderObject;						//渲染对象
		Vector<Object*> m_RequiredObject;

		bool m_IfHaveRun;										//是否已经Run过了
		bool m_IfUse;											//是否使用
		bool m_IfRun;											//是否每帧运行
		bool m_IfChild;											//是否是子对象
		ObjectMode m_Mode;

		XMFLOAT3 m_PositionBuffer;
		XMFLOAT3 m_RotationBuffer;
		XMFLOAT3 m_ScaleBuffer;
		TransformComponent* m_pFatherTransformBuffer;
		TransformComponent* m_pTransformBuffer;
		bool m_IfSyncTransform;
	};

	void RunComponentOnTree(Component* node, float DeltaTime);	//在树上运行组件(DFS)

	template<typename T>
	inline T * Object::GetComponent()
	{
		return dynamic_cast<T*>(GetComponent(T::GetComponentFactory().m_Name));
	}

}