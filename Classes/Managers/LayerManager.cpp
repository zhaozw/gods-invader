#ifndef CONST_LAYERMANAGER
#define CONST_LAYERMANAGER

#include "LayerManager.h"

// ===========================================================
// Init
// ===========================================================

// ===========================================================
// Constructors
// ===========================================================

LayerManager::LayerManager()
{
	this->mSortEntitiesTime = 0.1f;
	this->mSortEntitiesTimeElapsed = 1000;
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

void LayerManager::popShadows()
{
	int length = this->getChildren()->count();

	int replacesCount = 0;

	for(int i = 0; i < length; i++)
	{
		Entity* object = (Entity*) this->getChildren()->objectAtIndex(i);

		if(object->isSetAsDynamicShadow())
		{
			this->getChildren()->exchangeObjectAtIndex(replacesCount++, i);
		}
	}
}

void LayerManager::sortChildrenByYPosition() // TODO: Code refactoring.
{
	int length = this->getChildren()->count();
	int i;

	for(int j = 0; j < length; j++)
	{
		Entity* testValue = (Entity*) this->getChildren()->objectAtIndex(j);

		if(testValue->isIgnoreSorting() || testValue->isSetAsShadow())
		{
			continue;
		}

		for(i = j - 1; i >= 0 && (((Entity*) this->getChildren()->objectAtIndex(i))->getY() - ((Entity*) this->getChildren()->objectAtIndex(i))->getHeight() - ((Entity*) this->getChildren()->objectAtIndex(i))->getZ()) < (testValue->getY() - testValue->getHeight() - testValue->getZ()) && !testValue->isSetAsShadow() && !((Entity*) this->getChildren()->objectAtIndex(i))->isIgnoreSorting(); i--)
		{
			this->getChildren()->replaceObjectAtIndex(i + 1, this->getChildren()->objectAtIndex(i));
		}
		
		this->getChildren()->replaceObjectAtIndex(i + 1, testValue);
	}
}

void LayerManager::update(float pDeltaTime)
{
	CCLayer::update(pDeltaTime);

	this->mSortEntitiesTimeElapsed += pDeltaTime;

	if(this->mSortEntitiesTimeElapsed >= this->mSortEntitiesTime)
	{
		this->mSortEntitiesTimeElapsed = 0;

		this->sortChildrenByYPosition();

		this->popShadows(); // TODO: Remove this instruction to the own place.
	}
}

// ===========================================================
// Virtual methods
// ===========================================================

#endif