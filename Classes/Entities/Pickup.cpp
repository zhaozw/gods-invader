#ifndef CONST_PICKUP
#define CONST_PICKUP

#include "Pickup.h"

// ===========================================================
// Init
// ===========================================================

void Pickup::constructor()
{
	this->mShadow = new Entity("stolen/shadow-small.png");

	this->mShadow->setIsShadow();
	this->mShadow->setCenterPosition(this->getWidth() / 2, this->getHeight() / 2 - Utils::coord(20));

	this->addChild(this->mShadow);

	this->mAnimationTime = 2.0f;
	this->mDeathAnimationTime = 1.0f;

	this->reset();
}

// ===========================================================
// Constructors
// ===========================================================

Pickup::Pickup()
{
}

Pickup::Pickup(const char* pszFileName, int pHorizontalFramesCount, int pVerticalFramesCount) :
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

void Pickup::reset()
{
	this->mAnimationTimeElapsed = 0.0f;
	this->mDeathAnimationTimeElapsed = 0.0f;

	this->mCenterX = 0;
	this->mCenterY = 0;

	this->mPaddingY = 0;

	this->mIsAnimationReverse = false;
	this->mIsMustDestroy = false;

	this->setScale(0.0f);
	this->setOpacity(255.0f);

	this->runAction(CCScaleTo::create(0.5f, 1.0f));
}

// ===========================================================
// Virtual methods
// ===========================================================

Entity* Pickup::create()
{
	Pickup* entity = ((Pickup*) Entity::create());

	entity->setCurrentFrameIndex(Utils::random(0, 2));

	entity->reset();

	return entity;
}

Pickup* Pickup::deepCopy()
{
	return new Pickup("stolen/pickup.png", 1, 3);
}

void Pickup::follow(float pVectorX, float pVectorY)
{
	if(this->mCenterX == 0 && this->mCenterY == 0) return;

	float vectorX = pVectorX- this->getCenterX();
	float vectorY = pVectorY - this->getCenterY();

	CCPoint vector = Utils::vectorNormalize(vectorX, vectorY, 1.0f);

	this->setCenterPosition(this->mCenterX + vector.x, this->mCenterY + vector.y + Utils::coord(this->mPaddingY));

	this->mCenterX += vector.x;
	this->mCenterY += vector.y;
}

void Pickup::startDestroy()
{
	this->mIsMustDestroy = true;

	this->runAction(CCFadeTo::create(1.0f, 0.0f));
}

void Pickup::update(float pDeltaTime)
{
	Entity::update(pDeltaTime);

	if(this->mCenterX == 0 && this->mCenterY == 0)
	{
		this->mCenterX = this->getCenterX();
		this->mCenterY = this->getCenterY();
	}
	else
	{
		this->mAnimationTimeElapsed += pDeltaTime;

		if(this->mAnimationTimeElapsed >= this->mAnimationTime)
		{
			this->mAnimationTimeElapsed = 0;

			this->mIsAnimationReverse = !this->mIsAnimationReverse;
		}

		this->mPaddingY -= this->mIsAnimationReverse ? 0.15f : -0.15f;

		this->setCenterPosition(this->mCenterX, this->mCenterY + Utils::coord(this->mPaddingY));
		this->mShadow->setCenterPosition(this->getWidth() / 2, this->getHeight() / 2 - Utils::coord(20) - Utils::coord(this->mPaddingY));

		this->mShadow->setScale(this->getScale() - Utils::coord(this->mPaddingY) / 35);
	}

	if(this->mIsMustDestroy)
	{
		this->mDeathAnimationTimeElapsed += pDeltaTime;

		if(this->mDeathAnimationTimeElapsed >= mDeathAnimationTime)
		{
			this->mDeathAnimationTimeElapsed = 0.0f;
			this->mIsMustDestroy = false;

			this->destroy();
		}
	}
}

#endif