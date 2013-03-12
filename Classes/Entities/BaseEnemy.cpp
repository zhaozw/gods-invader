#ifndef CONST_BASEENEMY
#define CONST_BASEENEMY

#include "BaseEnemy.h"

BaseEnemy::BaseEnemy(Hero* pHero)
{
	this->mHero = pHero;
}

BaseEnemy::BaseEnemy(const char* pszFileName, int pHorizontalFramesCount, int pVerticalFramesCount, Hero* pHero) :
	HealthEntity(pszFileName, pHorizontalFramesCount, pVerticalFramesCount)
	{
		this->mHero = pHero;

		this->mShadow = new Entity("stolen/shadow.png");
		this->mShadow->setIsShadow();

		this->addChild(this->mShadow);

		this->mShadow->setCenterPosition(this->getWidth() / 2, this->getHeight() / 2 - Utils::coord(20)); // I should remove this to the own class

		this->mFollowPaddingX = 0;//Utils::randomf(-200.0, 200.0); // for shooting enemies
		this->mFollowPaddingY = 0;//Utils::randomf(-200.0, 200.0);

		this->setHealth(100);

		this->mSpeedStandart = Utils::randomf(0.2, 2.0);

		this->setSpeed(this->mSpeedStandart); // I should remove this

		this->setScale(2);

		this->animate(0.3);

		this->mShootPadding = 0;

		this->resumeSchedulerAndActions();
	}

float BaseEnemy::getSpeed()
{
	return this->mSpeed;
}

void BaseEnemy::setSpeed(float pSpeed)
{
	this->mSpeed = pSpeed;
}

void BaseEnemy::onCollide(BaseBullet* pBullet)
{
	this->removeHealth(pBullet->getPower());
	
	this->mShootVectorX = pBullet->mVectorX;
	this->mShootVectorY = pBullet->mVectorY;

	this->mShootPadding = 10;
}

BaseEnemy* BaseEnemy::deepCopy()
{
	return new BaseEnemy("stolen/alien2.png", 8, 1, this->mHero);
}

void BaseEnemy::update(float pDeltaTime)
{
	Entity::update(pDeltaTime);
	
    // padding on collide

	if(this->mShootPadding > 0)
	{
		float x = this->mShootVectorX;
		float y = this->mShootVectorY;

		float speedX = x / sqrt(x * x + y * y) * this->mShootPadding;
		float speedY = y / sqrt(x * x + y * y) * this->mShootPadding;

		x = this->getX() + speedX;
		y = this->getY() + speedY;

		this->setCenterPosition(x, y);

		this->mShootPadding -= 0.5;
	}
	else
	{
		float x = this->getX() - this->mHero->getX() - this->mFollowPaddingX;
		float y = this->getY() - this->mHero->getY() - this->mFollowPaddingY;

		float speedX = x / sqrt(x * x + y * y) * this->getSpeed();
		float speedY = y / sqrt(x * x + y * y) * this->getSpeed();

		x = this->getX() - speedX;
		y = this->getY() - speedY;

		if(!this->collideCoordinatesWith(x, y, Options::BASE))
		{
			this->setCenterPosition(x, y);
		}
		else
		{
			if(x < Options::BASE->getX() - Options::BASE->getWidth() / 2 - 15 || x > Options::BASE->getX() + Options::BASE->getWidth() / 2 + 15)
			{
				this->setCenterPosition(this->getX(), this->getY() - (this->getY() > this->mHero->getY() ? 1 : -1));
			}
			if(y< Options::BASE->getY() - Options::BASE->getHeight() / 2 - 15 || y > Options::BASE->getY() + Options::BASE->getHeight() / 2 + 15)
			{
				this->setCenterPosition(this->getX() - (this->getX() > this->mHero->getX() ? 1 : -1), this->getY());
			}
		}
	}
}

#endif