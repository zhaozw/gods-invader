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
		this->constructor();
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
	Cloud* entity = ((Cloud*) Entity::create());

	if(!entity->mShadow->getParent())
	{
		entity->getParent()->addChild(entity->mShadow);
	}

	entity->setCurrentFrameIndex(Utils::random(0, 2));

	return entity;
}

SmallCloud* SmallCloud::deepCopy()
{
	return new SmallCloud("platform/clouds-sprite.png", 1, 3);
}

#endif