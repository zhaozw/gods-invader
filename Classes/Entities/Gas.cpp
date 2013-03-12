#ifndef CONST_GAS
#define CONST_GAS

#include "Gas.h"

// ===========================================================
// Init
// ===========================================================

void Gas::constructor(Entity* pHero)
{
	this->mHero = pHero;
}

// ===========================================================
// Constructors
// ===========================================================

Gas::Gas(Entity* pHero)
{
	this->constructor(pHero);
}

Gas::Gas(const char* pszFileName, int pHorizontalFramesCount, int pVerticalFramesCount, Entity* pHero) :
	Entity(pszFileName, pHorizontalFramesCount, pVerticalFramesCount)
	{
		this->constructor(pHero);
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

Entity* Gas::create()
{
	this->animate(0.08f);

	return Entity::create();
}

void Gas::onAnimationCircleEnd()
{
	// this->destroy(); // Some trouble here
}

Gas* Gas::deepCopy()
{
	return new Gas("main-character/gas-animation.png", 12, 1, this->mHero);
}

void Gas::setCurrentFrameIndex(int pIndex)
{
	Entity::setCurrentFrameIndex(pIndex);
}

void Gas::update(float pDeltaTime)
{
	Entity::update(pDeltaTime);

	if(this->getCurrentFrameIndex() < 1)
	{
		this->setCenterPosition(this->mHero->getX(), this->mHero->getY() - Utils::coord(45));
	}
}

#endif