#ifndef CONST_CLOUD
#define CONST_CLOUD

#include "Cloud.h"

// ===========================================================
// Init
// ===========================================================

void Cloud::constructor()
{
	this->mBoundsX1 = 0;
	this->mBoundsX2 = 0;
	this->mBoundsY1 = 0;
	this->mBoundsY2 = 0;

	this->mVectorX = 0;
	this->mVectorY = 0;

	this->mIsMove = false;

	this->mShadow = new Entity("platform/clouds-shadow-sprite.png", 1, 3);
	this->mShadow->setIsShadow();
}

// ===========================================================
// Constructors
// ===========================================================

Cloud::Cloud()
{
}

Cloud::Cloud(const char* pszFileName, int pHorizontalFramesCount, int pVerticalFramesCount) :
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

void Cloud::init(float pVectorX, float pVectorY, float pBoundsX1, float pBoundsX2, float pBoundsY1, float pBoundsY2)
{
	this->mBoundsX1 = pBoundsX1;
	this->mBoundsX2 = pBoundsX2;
	this->mBoundsY1 = pBoundsY1;
	this->mBoundsY2 = pBoundsY2;

	this->mIsMove = true;

	float x = 0;//Utils::random(pBoundsX1, pBoundsX2);
	float y = Utils::random(0, 2) == 1 ? pBoundsY1 : pBoundsY2;

	this->setCenterPosition(x, y);

	this->mVectorX = pVectorX - x;
	this->mVectorY = pVectorY - y;
}

// ===========================================================
// Virtual methods
// ===========================================================

Entity* Cloud::create()
{
	Cloud* entity = ((Cloud*) Entity::create());

	if(!entity->mShadow->getParent())
	{
		entity->getParent()->addChild(entity->mShadow);
	}

	entity->setCurrentFrameIndex(Utils::random(0, 2));

	return entity;
}

void Cloud::setCurrentFrameIndex(int pIndex)
{
	Entity::setCurrentFrameIndex(pIndex);

	this->mShadow->setCurrentFrameIndex(pIndex);
}

Cloud* Cloud::deepCopy()
{
	return new Cloud("platform/clouds-sprite.png", 1, 3);
}

void Cloud::update(float pDeltaTime)
{
	Entity::update(pDeltaTime);

	this->mShadow->setCenterPosition(this->getX(), this->getY() - Utils::coord(550));

	if(this->mIsMove)
	{
		float speedX = this->mVectorX / sqrt(this->mVectorX * this->mVectorX + this->mVectorY * this->mVectorY) * 5;
		float speedY = this->mVectorY / sqrt(this->mVectorX * this->mVectorX + this->mVectorY * this->mVectorY) * 5;

		this->setCenterPosition(this->getX() + speedX, this->getY() + speedY);
	}

	if(!this->collideWithCoordinates(this->mBoundsX1, this->mBoundsX2, this->mBoundsY1, this->mBoundsY2))
	{
		this->destroy();
	}
}

#endif