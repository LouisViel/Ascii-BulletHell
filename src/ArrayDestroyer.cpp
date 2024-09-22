#include "../include/ArrayDestroyer.h"

//////////////////////////////////
//////////////////////////////////
//////////////////////////////////

ArrayDestroyer::ArrayDestroyer(
	const void* const arrayPointer
) :
	m_arrayPointer(arrayPointer)
{ }

ArrayDestroyer::~ArrayDestroyer()
{
	delete[] m_arrayPointer;
}