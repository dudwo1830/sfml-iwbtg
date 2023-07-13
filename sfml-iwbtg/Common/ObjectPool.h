#pragma once
#include "stdafx.h"
#include <functional>

template <typename T>
class ObjectPool
{
protected:
	std::list<T*> pool;
	std::list<T*> useList;

	void CreateObjs(int count = 100);
public:
	ObjectPool() = default;
	~ObjectPool() = default;

	void Init(int cacheSize = 100);
	void Release();
	void Clear();

	T* Get();
	void Return(T* obj);

	const std::list<T*>& GetPool() const;
	const std::list<T*>& GetUseList() const;

	//매개변수 하나를 참조하는 void 함수
	std::function<void(T*)> OnCreate;
};

template<typename T>
inline void ObjectPool<T>::CreateObjs(int count)
{
	for (int i = 0; i < count; i++)
	{
		T* obj = new T();
		if (OnCreate != nullptr)
		{
			OnCreate(obj);
		}
		obj->Init();
		pool.push_back(obj);
	}
}

template<typename T>
inline void ObjectPool<T>::Init(int cacheSize)
{
	Release();
	CreateObjs(cacheSize);
}

template<typename T>
inline void ObjectPool<T>::Release()
{
	Clear();

	for (auto obj : pool)
	{
		delete obj;
	}
	pool.clear();
}

template<typename T>
inline void ObjectPool<T>::Clear()
{
	for (auto obj : useList)
	{
		obj->SetActive(false);
		pool.push_back(obj);
	}
	useList.clear();
}

template<typename T>
inline T* ObjectPool<T>::Get()
{
	if (pool.empty())
	{
		CreateObjs();
	}

	T* obj = pool.front();
	pool.pop_front();

	obj->SetActive(true);
	obj->Reset();

	useList.push_back(obj);
	return obj;
}

template<typename T>
inline void ObjectPool<T>::Return(T* obj)
{
	if (std::find(useList.begin(), useList.end(), obj) == useList.end())
	{
		std::cout << "void ObjectPool<T>::Return Error!!!" << std::endl;
		return;
	}
	useList.remove(obj);
	obj->SetActive(false);
	pool.push_back(obj);
}

template<typename T>
inline const std::list<T*>& ObjectPool<T>::GetPool() const
{
	return pool;
}

template<typename T>
inline const std::list<T*>& ObjectPool<T>::GetUseList() const
{
	return useList;
}
