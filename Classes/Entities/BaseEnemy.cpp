#ifndef CONST_BASEENEMY
#define CONST_BASEENEMY

#include "BaseEnemy.h"

BaseEnemy::BaseEnemy()
{
}

BaseEnemy::BaseEnemy(Hero* pHero, EntityManager* pBullets)
{
	this->mHero = pHero;
	this->mBullets = pBullets;
}
BaseEnemy::BaseEnemy(const char* pszFileName, int pHorizontalFramesCount, int pVerticalFramesCount) :
	BarEntity(pszFileName, pHorizontalFramesCount, pVerticalFramesCount)
	{
		this->mShadow = new Entity("stolen/shadow.png");
		this->mShadow->setIsShadow();

		this->mShootPadding = 0;

		this->resumeSchedulerAndActions();
	}

BaseEnemy::BaseEnemy(const char* pszFileName, int pHorizontalFramesCount, int pVerticalFramesCount, Hero* pHero, EntityManager* pBullets) :
	BarEntity(pszFileName, pHorizontalFramesCount, pVerticalFramesCount)
	{
		this->mHero = pHero;
		this->mBullets = pBullets;
	}

Entity* BaseEnemy::create()
{
	this->mShadow->create();

	if(!this->mShadow->getParent())
	{
		this->getParent()->addChild(this->mShadow, 0);
	}

	this->setHealth(100.0f);
	this->setFireTime(Utils::randomf(3.0f, 15.0f));

	this->mSpeedStandart = 70.0f;//Utils::randomf(10.0f, 100.0f);

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

void BaseEnemy::onCollide(Hero* pEntity)
{
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

		this->setCenterPosition(x, y);

		this->mShootPadding -= Utils::coord(0.3f);
	}
	else
	{
		this->move(pDeltaTime);
	}

	// Fire

	//if(BarEntity::fire(this->mHero->getCenterX(), this->mHero->getCenterY()))
	//{
		//this->fire();
	//}
}

void BaseEnemy::move(float pDeltaTime)
{

}

void BaseEnemy::fire()
{
	BaseBullet* bullet = ((BaseBullet*) this->mBullets->create());
	bullet->setSpeed(250);
	bullet->setPower(1);
	//bullet->fire(this->getCenterX(), this->getCenterY(), this->mHero->getCenterX(), this->mHero->getCenterY());
	
	if(Options::SOUND_ENABLE)
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Sound/alienshot.wav");
	}
}

#endif