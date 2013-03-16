#ifndef CONST_BASECUBIC
#define CONST_BASECUBIC

#include "BaseCubic.h"

BaseCubic::BaseCubic() :
	BarEntity()
	{

	}

BaseCubic::BaseCubic(const char* pszFileName, int pHorizontalFramesCount, int pVerticalFramesCount) :
	BarEntity(pszFileName, pHorizontalFramesCount, pVerticalFramesCount)
	{
	}

void BaseCubic::reset()
{
	this->setBarsManagement(true, false);
}

Entity* BaseCubic::create()
{
	BaseCubic* entity = ((BaseCubic*) Entity::create());

	entity->reset();

	return entity;
}

#endif