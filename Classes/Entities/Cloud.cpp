#ifndef CONST_CLOUD
#define CONST_CLOUD

#include "Cloud.h"

// ===========================================================
// Init
// ===========================================================

void Cloud::constructor()
{
	this->mAltitude = 0.5;

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

void Cloud::init(float pVectorX, float pVectorY, Entity* pBounds)
{
	this->mIsMove = true;

	float x = Utils::random(pBounds->getX() - pBounds->getWidth() / 2, pBounds->getX() + pBounds->getWidth() / 2);
	float y = pBounds->getY() - (Utils::random(0, 2) == 1 ? pBounds->getHeight() / 2 : -pBounds->getHeight() / 2);

	this->setCenterPosition(x, y);

	this->mVectorX = pVectorX - x;
	this->mVectorY = pVectorY - y;
}

// ===========================================================
// Virtual methods
// ===========================================================

Entity* Cloud::create()
{
	if(!this->mShadow->getParent())
	{
		this->getParent()->addChild(this->mShadow);
	}

	this->setCurrentFrameIndex(Utils::random(0, 2));

	return Entity::create();
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

	this->setScale(2 - this->mAltitude);

	this->mShadow->setScale(this->mAltitude);
	this->mShadow->setCenterPosition(this->getX(), this->getY() - Utils::coord(550));

	if(this->mAltitude < 1)
	{
		this->mAltitude += 0.001;
	}

	if(this->mIsMove)
	{
		float speedX = this->mVectorX / sqrt(this->mVectorX * this->mVectorX + this->mVectorY * this->mVectorY) * 5;
		float speedY = this->mVectorY / sqrt(this->mVectorX * this->mVectorX + this->mVectorY * this->mVectorY) * 5;

		this->setCenterPosition(this->getX() + speedX, this->getY() + speedY);
	}
}

#endif