#ifndef CONST_CASTLE
#define CONST_CASTLE

#include "Castle.h"

Castle::Castle(const char* pszFileName, int pHorizontalFramesCount, int pVerticalFramesCount) :
	BarEntity(pszFileName, pHorizontalFramesCount, pVerticalFramesCount)
{
	this->setBarsWidth(this->getWidth() - this->getWidth() / 4);

	this->setFireTime(1.1f);

	this->setHealth(1000);
	this->removeHealth(100);

	this->setBarsManagement(true, true);

	this->mCherries = new EntityManager(2, new Cherry(), this);
}

void Castle::update(float pDeltaTime)
{
	BarEntity::update(pDeltaTime);

	if(this->mCherries->getCount() < 1)
	{
		this->mCherries->create()->setCenterPosition(this->getWidth() / 2, this->getHeight());
	}
}

void Castle::fire(float pVectorX, float pVectorY)
{
	if(BarEntity::fire(pVectorX, pVectorY))
	{
	}
}

void Castle::draw()
{
	Entity::draw();
}

#endif