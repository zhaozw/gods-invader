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

		if(pScreen != NULL)
		{
			this->mParent->addChild(currentEntity);
		}
		
		currentEntity->destroy(false);
	}

	this->mIsSortY = true;

	this->mIsUnpacking = true; // TODO: change to false and write setter
}

EntityManager::EntityManager(int pCreateCount, Entity* pEntity)
{
	this->init(pCreateCount, -1, pEntity, NULL);
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
	if(this->mLastElementNumber >= 0)
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

void EntityManager::clear() // Some problem in this method with elements which will change and thir ID
{
	for(int i = 0; i < this->getCapacity(); i++)
	{
		((Entity*) this->objectAtIndex(i))->destroy(true);
	}

	for(int i = 0; i < this->getCapacity(); i++)
	{
		((Entity*) this->objectAtIndex(i))->destroy();
	}
}

void EntityManager::setParent(CCNode* pScreen)
{
	this->mParent = pScreen;

	for(int i = 0; i < this->getCapacity(); i++)
	{
		this->mParent->addChild((Entity*) this->objectAtIndex(i));
	}
}

void EntityManager::sortChildrenByYPosition()
{
	if(!this->mIsSortY)
	{
		return;
	}

	int length = this->mParent->getChildren()->count();
	int i;

	for(int j = 0; j < length; j++)
	{
		Entity* testValue = (Entity*) this->mParent->getChildren()->objectAtIndex(j);

		for(i = j - 1; i >= 0 && ((Entity*) this->mParent->getChildren()->objectAtIndex(i))->getY() < testValue->getY() && !testValue->isSetAsShadow(); i--)
		{
			this->mParent->getChildren()->replaceObjectAtIndex(i + 1, this->mParent->getChildren()->objectAtIndex(i));
		}
		
		this->mParent->getChildren()->replaceObjectAtIndex(i + 1, testValue);
	}
}

void EntityManager::disableSort()
{
	this->mIsSortY = false;
}

void EntityManager::unpacking() // TODO: Maybe some perfomance refactoring?
{
	for(int i = 0; i < this->getCount(); i++)
	{
		Entity* entity1 = ((Entity*) this->objectAtIndex(i));

		for(int j = 0; j < this->getCount(); j++)
		{
			Entity* entity2 = ((Entity*) this->objectAtIndex(j));

			if(i == j || !entity1->hasShadow() || !entity2->hasShadow()) continue;

			if(entity1->getShadow()->collideWith(entity2->getShadow()))
			{
				float x1 = entity1->getCenterX();
				float x2 = entity2->getCenterX();

				float y1 = entity1->getCenterY();
				float y2 = entity2->getCenterY();

				float padding = 0.5f;

				entity1->setCenterPosition(x1 + (x1 > x2 ? padding : -padding), y1 + (y1 > y2 ? padding : -padding));
				entity2->setCenterPosition(x2 + (x2 > x1 ? padding : -padding), y2 + (y2 > y1 ? padding : -padding));
			}
		}
	}
}

void EntityManager::update(float pDeltaTime)
{
	if(this->mIsUnpacking)
	{
		this->unpacking();
	}
}

#endif