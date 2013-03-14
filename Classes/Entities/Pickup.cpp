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

void Pickup::setFollowEntity(Entity* pEntity)
{
	this->mFollowEntity = pEntity;

	this->mIsFollow = true;
}

// ===========================================================
// Methods
// ===========================================================

void Pickup::reset()
{
	this->mAnimationTimeElapsed = 0;

	this->mVectorX = 0;
	this->mVectorY = 0;

	this->mCenterX = 0;
	this->mCenterY = 0;

	this->mPaddingY = 0;

	this->mIsAnimationReverse = false;

	this->mIsFollow = false;
}

bool Pickup::isFollow()
{
	return this->mIsFollow;
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

void Pickup::update(float pDeltaTime)
{
	Entity::update(pDeltaTime);

	if(this->mCenterX == 0 && this->mCenterY == 0)
	{
		this->mCenterX = this->getX();
		this->mCenterY = this->getY();
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

	if(this->mIsFollow)
	{
		this->mVectorX = this->mFollowEntity->getX()- this->getX();
		this->mVectorY = this->mFollowEntity->getY() - this->getY();

		float speedX = this->mVectorX / sqrt(this->mVectorX * this->mVectorX + this->mVectorY * this->mVectorY) * 1;
		float speedY = this->mVectorY / sqrt(this->mVectorX * this->mVectorX + this->mVectorY * this->mVectorY) * 1;

		this->setCenterPosition(this->mCenterX + speedX, this->mCenterY + speedY + Utils::coord(this->mPaddingY));
		this->mCenterX += speedX;
		this->mCenterY += speedY;
	}
}

#endif