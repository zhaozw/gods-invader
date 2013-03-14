#ifndef CONST_BASEENEMY
#define CONST_BASEENEMY

#include "BaseEnemy.h"

BaseEnemy::BaseEnemy(Hero* pHero)
{
	this->mHero = pHero;
}

BaseEnemy::BaseEnemy(const char* pszFileName, int pHorizontalFramesCount, int pVerticalFramesCount, Hero* pHero) :
	BarEntity(pszFileName, pHorizontalFramesCount, pVerticalFramesCount)
	{
		this->mHero = pHero;

		this->setBarsManagement(true, false);

		this->mShadow = new Entity("stolen/shadow.png");
		this->mShadow->setIsShadow();

		this->addChild(this->mShadow);

		this->mShadow->setCenterPosition(this->getWidth() / 2, this->getHeight() / 2 - Utils::coord(40)); // I should remove this to the own class

		this->mFollowPaddingX = 0;//Utils::randomf(-500.0, 500.0); // for shooting enemies
		this->mFollowPaddingY = 0;//Utils::randomf(-500.0, 500.0);

		this->animate(0.3);

		this->mShootPadding = 0;

		this->resumeSchedulerAndActions();
	}

Entity* BaseEnemy::create()
{
	this->setHealth(100);

	this->mSpeedStandart = Utils::randomf(20.0, 100.0);

	this->setSpeed(this->mSpeedStandart); // I should remove this

	return BarEntity::create();
}

bool BaseEnemy::destroy()
{
	BarEntity::destroy();

	if(Utils::probably(100))
	{
		return true;
	}

	return false;
}

float BaseEnemy::getSpeed(float pDeltaTime)
{
	return this->mSpeed * pDeltaTime;
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
	BarEntity::update(pDeltaTime);
	
    // padding on collide

	if(this->mShootPadding > 0)
	{
		float x = this->mShootVectorX;
		float y = this->mShootVectorY;

		float speedX = x / sqrt(x * x + y * y) * this->mShootPadding;
		float speedY = y / sqrt(x * x + y * y) * this->mShootPadding;

		x = this->getX() + speedX;
		y = this->getY() + speedY;

		if(!this->collideCoordinatesWith(x, y, Options::BASE))
		{
			this->setCenterPosition(x, y);
		}

		this->mShootPadding -= 0.5;
	}
	else
	{
		float x = this->getX() - this->mHero->getX() - this->mFollowPaddingX;
		float y = this->getY() - this->mHero->getY() - this->mFollowPaddingY;

		float speedX = x / sqrt(x * x + y * y) * this->getSpeed(pDeltaTime);
		float speedY = y / sqrt(x * x + y * y) * this->getSpeed(pDeltaTime);

		x = this->getX() - speedX;
		y = this->getY() - speedY;

		if(!this->collideCoordinatesWith(x, y, Options::BASE))
		{
			this->setCenterPosition(x, y);
		}
		else
		{
			if(x < Options::BASE->getX() - Options::BASE->getWidth() / 2 - 25 || x > Options::BASE->getX() + Options::BASE->getWidth() / 2 + 25)
			{
				this->setCenterPosition(this->getX(), this->getY() - (this->getY() > this->mHero->getY() ? 1 : -1));
			}
			if(y< Options::BASE->getY() - Options::BASE->getHeight() / 2 - 25 || y > Options::BASE->getY() + Options::BASE->getHeight() / 2 + 25)
			{
				this->setCenterPosition(this->getX() - (this->getX() > this->mHero->getX() ? 1 : -1), this->getY());
			}
		}
	}
}

#endif