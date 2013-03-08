#ifndef CONST_ENTITYMANAGER
#define CONST_ENTITYMANAGER

#include "EntityManager.h"

void EntityManager::init(int pCreateCount, int pMaxCount, Entity* pEntity, CCNode* pScreen)
{
	this->initWithCapacity(pCreateCount);

	this->mParent = pScreen;
	this->mLastElementNumber = -1;
	this->mCapacity = pCreateCount; // TODO: increase to pMaxCount

	for(int i = 0; i < pCreateCount; i++)
	{
		Entity* currentEntity = pEntity->deepCopy();

		currentEntity->setEntityManager(this);
		currentEntity->setEntityManagerId(i);

		this->addObject(currentEntity);

		this->mParent->addChild(currentEntity);
		
		currentEntity->destroy(false);
	}
}

EntityManager::EntityManager(int pCreateCount, Entity* pEntity, CCNode* pScreen)
{
	this->init(pCreateCount, -1, pEntity, pScreen);
}

EntityManager::EntityManager(int pCreateCount, int pMaxCount, Entity* pEntity, CCNode* pScreen)
{
	this->init(pCreateCount, pMaxCount, pEntity, pScreen);
}

Entity* EntityManager::create()
{
	if (++this->mLastElementNumber < this->mCapacity)
	{
		Entity* object = (Entity*) this->objectAtIndex(this->mLastElementNumber);
		object->create();

		return object;
	}

	return NULL;
}

void EntityManager::destroy(int pIndex)
{
	if(pIndex > 0 && pIndex < this->mCapacity && this->mLastElementNumber >= 0)
	{
		this->exchangeObjectAtIndex(pIndex, this->mLastElementNumber);

		((Entity*) this->objectAtIndex(pIndex))->setEntityManagerId(pIndex);
		((Entity*) this->objectAtIndex(this->mLastElementNumber))->setEntityManagerId(this->mLastElementNumber);

		this->mLastElementNumber--;
	}
}

void EntityManager::changeTexture(Texture* pTexture)
{
	for(int i = 0; i < this->getCapacity(); i++)
	{
		((Entity*) this->objectAtIndex(i))->changeTexture(pTexture);
	}
}

int EntityManager::getCount()
{
	return this->mLastElementNumber + 1;
}

int EntityManager::getCapacity()
{
	return this->mCapacity;
}

void EntityManager::clear()
{
	for(int i = 0; i < this->getCount(); i++)
	{
		((Entity*) this->objectAtIndex(i))->destroy();
	}
}

#endif