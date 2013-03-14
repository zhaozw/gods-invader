#ifndef CONST_SMALLCLOUD
#define CONST_SMALLCLOUD

#include "SmallCloud.h"

// ===========================================================
// Init
// ===========================================================

// ===========================================================
// Constructors
// ===========================================================

SmallCloud::SmallCloud()
{
}

SmallCloud::SmallCloud(const char* pszFileName, int pHorizontalFramesCount, int pVerticalFramesCount) :
	Entity(pszFileName, pHorizontalFramesCount, pVerticalFramesCount)
	{
	}

// ===========================================================
// Getters
// ===========================================================

// ===========================================================
// Setters
// ===========================================================

// ===========================================================
// Methods
// ===========================================================

// ===========================================================
// Virtual methods
// ===========================================================

Entity* SmallCloud::create()
{
	SmallCloud* entity = ((SmallCloud*) Entity::create());

	entity->setCurrentFrameIndex(Utils::random(0, 2));

	return entity;
}

SmallCloud* SmallCloud::deepCopy()
{
	return new SmallCloud("platform/clouds-sprite.png", 1, 3);
}

#endif