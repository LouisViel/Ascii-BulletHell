#pragma once
#include "RenderData.h"

template<typename T>
class Component
{
public:
	virtual ~Component();
	virtual void Update(T* const target) = 0;
	virtual void PostRender(T* const target, RenderData** const renderDataBuffer, const unsigned int xBufferSize, const unsigned int yBufferSize) { }
};

template<typename T>
inline Component<T>::~Component() { }