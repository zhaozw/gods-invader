#ifndef CONST_HERO
#define CONST_HERO

#include "Hero.h"

Hero::Hero(const char* pszFileName, EntityManager* pBulletsManager, int pHorizontalFramesCount, int pVerticalFramesCount) :
	HealthEntity(pszFileName, pHorizontalFramesCount, pVerticalFramesCount)
	{
		this->mBulletsManager = pBulletsManager;

		this->mShadow = new Entity("stolen/shadow.png");
		this->mShadow->setIsShadow();

		this->addChild(this->mShadow);

		this->setPatrons(100);
		this->setHealth(100);
		this->removeHealth(2);

		this->mShadow->setCenterPosition(this->getWidth() / 2, this->getHeight() / 2 - Utils::coord(50));
		this->mShadow->setScale(2);

		this->mSpeedStandart = 200;

		this->setSpeed(this->mSpeedStandart); // I should remove this

		this->setCurrentFrameIndex(2);

		this->mFollowCoordinateX = 0;
		this->mFollowCoordinateY = 0;

		this->mShootPaddingStandart = 200;
		this->mShootPadding = this->mShootPaddingStandart;
	}

float Hero::getSpeed()
{
	return this->mSpeed;
}

float Hero::getPatrons()
{
	return this->mPatrons;
}

void Hero::setSpeed(float pSpeed)
{
	this->mSpeed = pSpeed;
}

void Hero::setPatrons(float pPatrons)
{
	this->mPatrons = pPatrons;
}

void Hero::setFollowCoordinates(float pX, float pY)
{
	this->mFollowCoordinateX = pX;
	this->mFollowCoordinateY = pY;
}

void Hero::follow()
{
	if(this->mFollowCoordinateX != 0 && this->mFollowCoordinateY != 0)
	{
		float x = this->getX() - this->mFollowCoordinateX / this->getSpeed();
		float y = this->getY() - this->mFollowCoordinateY / this->getSpeed();

		if(!this->collideWith(Options::BASE))
		{
			this->setCenterPosition(x, y);
		}
		else
		{
			this->mShootPadding = 100;

			this->setSpeed(this->mSpeedStandart * 10);
		}
	}
}

void Hero::fire(float pX, float pY)
{
	((BaseBullet*) this->mBulletsManager->create())->fire(this->getX(), this->getY(), pX, pY);
	
	this->mShootPadding = 170;

	this->setSpeed(this->mSpeedStandart * 10);

	this->mPatrons--;
}

void Hero::update(float pDeltaTime)
{
	this->follow();

	int pontencialFrame = 2;

	int padding1 = Utils::coord(50);
	int padding2 = 150;
	int padding3 = 100;

	if(this->mFollowCoordinateY > padding1)
	{
		pontencialFrame++;

		if(this->mFollowCoordinateY > padding2 && abs(this->mFollowCoordinateX) < padding3)
		{
			pontencialFrame++;
		}
	}
	else if(this->mFollowCoordinateY < -padding1)
	{
		pontencialFrame--;

		if(this->mFollowCoordinateY < -padding2 && abs(this->mFollowCoordinateX) < padding3)
		{
			pontencialFrame--;
		}
	}

	if(this->mFollowCoordinateX > 0)
	{
		this->setScaleX(1);
	}
	else
	{
		this->setScaleX(-1);
	}

	if(pontencialFrame == 0 || pontencialFrame == 4)
	{
		this->setScaleX(1);
	}

	this->setCurrentFrameIndex(pontencialFrame);

	if(this->mShootPadding < this->mShootPaddingStandart)
	{
		this->setCenterPosition(this->getX() + this->mFollowCoordinateX / this->mShootPadding, this->getY() + this->mFollowCoordinateY / this->mShootPadding);

		this->mShootPadding += 3;
	}
	else if(this->getSpeed() > this->mSpeedStandart)
	{
		this->setSpeed(this->getSpeed() - 50);
	}
}

void Hero::draw()
{
	HealthEntity::draw();

	float x1;
	float x2;

	float y1;
	float y2;

	if(this->getHealth() < 100)
	{
		x1 = 27;
		x2 = this->getWidth() - 27;

		y1 = -11;
		y2 = -19;

		CCPoint vertices1[] = {
			ccp(x1, y1),
			ccp(x2, y1),
			ccp(x2, y2),
			ccp(x1, y2)
		};

		float full = (this->getWidth() - 29);

		if(this->getScaleX() > 0)
		{
			x1 = 29;
			x2 = full * (this->getHealth() / 100);
		}
		else
		{
			x1 = 29;
			x2 = full * (this->getHealth() / 100);

			x1 += full - x2;
			x2 += full - x2;
		}

		y1 = -13;
		y2 = -17;

		CCPoint vertices2[] = {
			ccp(x1, y1),
			ccp(x2, y1),
			ccp(x2, y2),
			ccp(x1, y2)
		};

		ccDrawSolidPoly(vertices1, 4, ccc4f(0.0f / 255.0f, 000.0f / 255.0f, 0.0f / 255.0f, 1));

		if(this->getHealth() > 75)
		{
			ccDrawSolidPoly(vertices2, 4, ccc4f(0.0f / 255.0f, 255.0f / 255.0f, 0.0f / 255.0f, 1));
		}
		else if(this->getHealth() > 45)
		{
			ccDrawSolidPoly(vertices2, 4, ccc4f(255.0f / 255.0f, 255.0f / 255.0f, 0.0f / 255.0f, 1));
		}
		else
		{
			ccDrawSolidPoly(vertices2, 4, ccc4f(255.0f / 255.0f, 0.0f / 255.0f, 0.0f / 255.0f, 1));
		}
	}

	if(this->getPatrons() < 100)
	{
		x1 = 27;
		x2 = this->getWidth() - 27;

		y1 = -21;
		y2 = -29;

		CCPoint vertices1[] = {
			ccp(x1, y1),
			ccp(x2, y1),
			ccp(x2, y2),
			ccp(x1, y2)
		};

		float full = (this->getWidth() - 29);

		if(this->getScaleX() > 0)
		{
			x1 = 29;
			x2 = full * (this->getPatrons() / 100);
		}
		else
		{
			x1 = 29;
			x2 = full * (this->getPatrons() / 100);

			x1 += full - x2;
			x2 += full - x2;
		}

		y1 = -23;
		y2 = -27;

		CCPoint vertices2[] = {
			ccp(x1, y1),
			ccp(x2, y1),
			ccp(x2, y2),
			ccp(x1, y2)
		};

		ccDrawSolidPoly(vertices1, 4, ccc4f(0.0f / 255.0f, 000.0f / 255.0f, 0.0f / 255.0f, 1));
		ccDrawSolidPoly(vertices2, 4, ccc4f(0.0f / 255.0f, 200.0f / 255.0f, 255.0f / 250.0f, 1));
	}
}

#endif