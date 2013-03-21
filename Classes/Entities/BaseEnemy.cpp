#ifndef CONST_BASEENEMY
#define CONST_BASEENEMY

#include "BaseEnemy.h"

BaseEnemy::BaseEnemy(Hero* pHero, EntityManager* pBullets)
{
	this->mHero = pHero;
	this->mBullets = pBullets;
}

BaseEnemy::BaseEnemy(const char* pszFileName, int pHorizontalFramesCount, int pVerticalFramesCount, Hero* pHero, EntityManager* pBullets) :
	BarEntity(pszFileName, pHorizontalFramesCount, pVerticalFramesCount)
	{
		this->mHero = pHero;
		this->mBullets = pBullets;

		this->mPupil = new Entity("enemies/onion/onion-pupil.png");
		this->addChild(this->mPupil);
		this->mPupil->setCenterPosition(this->getWidth() / 2, this->getHeight() / 2 - Utils::coord(9));

		this->mEye = new Entity("enemies/onion/onion-eye-animation.png", 7, 2);
		this->mEye->setCenterPosition(this->getWidth() / 2, this->getHeight() / 2);
		this->addChild(this->mEye);

		this->setBarsManagement(true, true);

		this->mShadow = new Entity("stolen/shadow.png");
		this->mShadow->setIsShadow();
		this->mShadow->setIsDynamicShadow();

		this->mShadow->setCenterPosition(this->getWidth() / 2, this->getHeight() / 2 - Utils::coord(40)); // I should remove this to the own class

		this->mFollowPaddingX = 0;//Utils::randomf(-500.0, 500.0); // for shooting enemies
		this->mFollowPaddingY = 0;//Utils::randomf(-500.0, 500.0);

		this->setAnimationStartTimeout(Utils::randomf(0.0f, 1.0f));
		this->animate(0.07f);

		this->mShootPadding = 0;

		this->mEyeAnimationTime = Utils::randomf(2.0f, 20.0f);
		this->mEyeAnimationTimeElapsed = 0;

		this->resumeSchedulerAndActions();
	}

Entity* BaseEnemy::create()
{
	this->mShadow->create();

	if(!this->mShadow->getParent())
	{
		this->getParent()->addChild(this->mShadow);
	}

	this->setHealth(100.0f);
	this->setFireTime(Utils::randomf(3.0f, 15.0f));

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

	this->mShadow->destroy(false);

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
	return new BaseEnemy("enemies/onion/onion-animation.png", 7, 2, this->mHero, this->mBullets);
}

void BaseEnemy::update(float pDeltaTime) // TODO: Rewrite to the Utils::vectorNormalize()
{
	if(!this->isVisible()) return;

	BarEntity::update(pDeltaTime);

	float x;
	float y;
	
    // padding on collide

	if(this->mShootPadding > 0)
	{
		x = this->mShootVectorX;
		y = this->mShootVectorY;

		float speedX = x / sqrt(x * x + y * y) * this->mShootPadding;
		float speedY = y / sqrt(x * x + y * y) * this->mShootPadding;

		x = this->getCenterX() + speedX;
		y = this->getCenterY() + speedY;

		if(!this->collideCoordinatesWith(x, y, Options::BASE))
		{
			this->setCenterPosition(x, y);
		}

		this->mShootPadding -= Utils::coord(0.3f);
	}
	else
	{
		x = this->getCenterX() - this->mHero->getCenterX() - this->mFollowPaddingX;
		y = this->getCenterY() - this->mHero->getCenterY() - this->mFollowPaddingY;

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

		CCPoint look = Utils::vectorNormalize(this->getCenterX() - this->mHero->getCenterX() - this->mFollowPaddingX, this->getCenterY() - this->mHero->getCenterY() - this->mFollowPaddingY, 6.0f);

		this->mPupil->setCenterPosition(this->getWidth() / 2 - look.x, this->getHeight() / 2 - Utils::coord(9) - look.y);
	}

	this->mEyeAnimationTimeElapsed += pDeltaTime;

	if(this->mEyeAnimationTimeElapsed >= this->mEyeAnimationTime)
	{
		this->mEyeAnimationTimeElapsed -= this->mEyeAnimationTime;

		this->mEye->animate(0.03f, 1, true);
	}

	// Fire

	if(BarEntity::fire(this->mHero->getCenterX(), this->mHero->getCenterY()))
	{
		this->fire();
	}
}

void BaseEnemy::fire()
{
	BaseBullet* bullet = ((BaseBullet*) this->mBullets->create());
	bullet->setSpeed(250);
	bullet->setPower(1);
	bullet->fire(this->getCenterX(), this->getCenterY(), this->mHero->getCenterX(), this->mHero->getCenterY());
	
	if(Options::SOUND_ENABLE)
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Sound/alienshot.wav");
	}
}

#endif