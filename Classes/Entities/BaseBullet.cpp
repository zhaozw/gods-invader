#ifndef CONST_BASEBULLET
#define CONST_BASEBULLET

#include "BaseBullet.h"

BaseBullet::BaseBullet()
{
}

BaseBullet::BaseBullet(const char* pszFileName, int pHorizontalFramesCount, int pVerticalFramesCount) :
	Entity(pszFileName, pHorizontalFramesCount, pVerticalFramesCount)
	{
		this->mShadow = new Entity("main-character/bullets-shadow.png");
		this->mShadow->setOpacity(150);

		this->addChild(this->mShadow);

		this->mShadow->setCenterPosition(this->getWidth() / 2, this->getHeight() / 2 - Utils::coord(20));
		this->mShadow->setIsShadow();

		this->setPower(10);
		this->setSpeed(20);

		this->mLifeTime = 3;

		this->mIsMoving = false;

		this->resumeSchedulerAndActions();
	}

void BaseBullet::destroy()
{
	this->mIsMoving = false;

	Entity::destroy();
}

float BaseBullet::getSpeed()
{
	return this->mSpeed;
}

float BaseBullet::getPower()
{
	return this->mPower;
}

void BaseBullet::setSpeed(float pSpeed)
{
	this->mSpeed = pSpeed;
}

void BaseBullet::setPower(float pPower)
{
	this->mPower = pPower;
}

void BaseBullet::fire(float pX, float pY, float pVectorX, float pVectorY)
{
	this->mIsMoving = true;

	this->setCenterPosition(pX, pY);

	this->mVectorX = pVectorX - pX;
	this->mVectorY = pVectorY - pY;

	this->setCurrentFrameIndex(Utils::random(0, 8));
}

BaseBullet* BaseBullet::deepCopy()
{
	return new BaseBullet("main-character/bullets.png", 5, 2);
}

void BaseBullet::update(float pDeltaTime)
{
	Entity::update(pDeltaTime);
	
	if(this->mIsMoving)
	{
		this->mLifeTimeElapsed += pDeltaTime;

		if(this->mLifeTimeElapsed >= this->mLifeTime)
		{
			this->mLifeTimeElapsed = 0;

			this->destroy();
		}

		float speedX = this->mVectorX / sqrt(this->mVectorX * this->mVectorX + this->mVectorY * this->mVectorY) * this->getSpeed();
		float speedY = this->mVectorY / sqrt(this->mVectorX * this->mVectorX + this->mVectorY * this->mVectorY) * this->getSpeed();

		this->setCenterPosition(this->getX() + speedX, this->getY() + speedY);

		float angle = atan2(this->mVectorX, this->mVectorY) * 180 / Utils::Pi + 90;

		this->setRotation(angle);
 
 		float padding = this->mVectorX / sqrt(this->mVectorX * this->mVectorX + this->mVectorY * this->mVectorY) * 40;

		this->mShadow->setCenterPosition(this->getWidth() / 2, this->getHeight() / 2 + Utils::coord(padding));

		this->mShadow->setVisible(this->isVisible());
	}
}

#endif