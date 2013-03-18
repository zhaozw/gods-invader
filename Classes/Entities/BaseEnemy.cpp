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

		this->setAnimationStartTimeout(Utils::randomf(0.0f, 1.0f));
		this->animate(0.04);

		this->mShootPadding = 0;

		this->resumeSchedulerAndActions();
	}

Entity* BaseEnemy::create()
{
	this->setHealth(100);

	this->mSpeedStandart = Utils::randomf(10.0f, 100.0f);

	this->mShootPadding = 0;

	this->setSpeed(this->mSpeedStandart); // I should remove this

	this->setScale(0.0f);

	this->runAction(CCScaleTo::create(0.5f, 1.0f));

	return BarEntity::create();
}

bool BaseEnemy::destroy()
{
	BarEntity::destroy();

	if(Utils::probably(30))
	{
		return true;
	}

	return false;
}

void BaseEnemy::onCollide(BaseBullet* pBullet)
{
	this->removeHealth(pBullet->getPower());
	
	this->mShootVectorX = pBullet->mVectorX;
	this->mShootVectorY = pBullet->mVectorY;

	this->mShootPadding = Utils::coord(5); // UPGRADE
}

BaseEnemy* BaseEnemy::deepCopy()
{
	return new BaseEnemy("enemies/onion/onion-animation.png", 7, 2, this->mHero);
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

		x = this->getCenterX() + speedX;
		y = this->getCenterY() + speedY;

		if(!this->collideCoordinatesWith(x, y, Options::BASE))
		{
			this->setCenterPosition(x, y);
		}

		this->mShootPadding -= Utils::coord(0.5);
	}
	else
	{
		float x = this->getCenterX() - this->mHero->getCenterX() - this->mFollowPaddingX;
		float y = this->getCenterY() - this->mHero->getCenterY() - this->mFollowPaddingY;

		float speedX = x / sqrt(x * x + y * y) * this->getSpeed(pDeltaTime);
		float speedY = y / sqrt(x * x + y * y) * this->getSpeed(pDeltaTime);

		x = this->getCenterX() - speedX;
		y = this->getCenterY() - speedY;

		if(!this->collideCoordinatesWith(x, y, Options::BASE))
		{
			this->setCenterPosition(x, y);
		}
		else
		{
			if(x < Options::BASE->getX() - Options::BASE->getWidth() / 2 - 25 || x > Options::BASE->getX() + Options::BASE->getWidth() / 2 + 25)
			{
				this->setCenterPosition(this->getCenterX(), this->getCenterY() - (this->getCenterY() > this->mHero->getCenterY() ? 1 : -1));
			}
			if(y< Options::BASE->getY() - Options::BASE->getHeight() / 2 - 25 || y > Options::BASE->getY() + Options::BASE->getHeight() / 2 + 25)
			{
				this->setCenterPosition(this->getCenterX() - (this->getCenterX() > this->mHero->getCenterX() ? 1 : -1), this->getCenterY());
			}
		}
	}
}

#endif