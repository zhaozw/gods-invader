#ifndef CONST_BASEENEMY
#define CONST_BASEENEMY

#include "BaseEnemy.h"

BaseEnemy::BaseEnemy(Hero* pHero)
{
	this->mHero = pHero;
}

BaseEnemy::BaseEnemy(const char* pszFileName, Hero* pHero) :
	Entity(pszFileName)
	{
		this->mHero = pHero;

		this->mFollowPaddingX = Utils::randomf(-200.0, 200.0);
		this->mFollowPaddingY = Utils::randomf(-200.0, 200.0);

		this->setSpeed(Utils::randomf(200.0, 800.0));
		this->setScale(0.7);

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

BaseEnemy* BaseEnemy::deepCopy()
{
	return new BaseEnemy("test/test-char.png", this->mHero);
}

void BaseEnemy::update(float pDeltaTime)
{
	this->previousCoordinateX = this->getX();

	float x = this->getX() - this->mHero->getX() - this->mFollowPaddingX;
	float y = this->getY() - this->mHero->getY() - this->mFollowPaddingY;

	this->setCenterPosition(this->getX() - x / this->getSpeed(), this->getY() - y / this->getSpeed());

	//this->setScaleX(this->previousCoordinateX - this->getX() > 0 ? -1 : 1);
}

#endif