#ifndef CONST_HERO
#define CONST_HERO

#include "Hero.h"

Hero::Hero(const char* pszFileName, EntityManager* pBulletsManager, int pHorizontalFramesCount, int pVerticalFramesCount) :
	BarEntity(pszFileName, pHorizontalFramesCount, pVerticalFramesCount)
	{

		this->mGasesAnimationTime = 0.2f;

		this->mGasesShadows = new EntityManager(10, new GasShadow());
		this->mGases = new EntityManager(10, new Gas(this));

		this->mBulletsManager = pBulletsManager;

		this->mShootAnimators = new EntityManager(10, new ShootAnimator(), this);

		this->reset();
	}

void Hero::reset()
{
	this->setVisible(true);

	this->mAltitude = 0;
	this->mGasesAnimationTimeElapsed = 0;

	this->setBarsManagement(true, true);
	this->setFireTime(0.1);
	this->setPatrons(100);

	this->setHealth(100);
	this->removeHealth(50);

	this->mSpeedStandart = 200;

	this->setSpeed(this->mSpeedStandart); // I should remove this

	this->setCurrentFrameIndex(2);
	this->mFollowCoordinateX = 0;
	this->mFollowCoordinateY = 0;

	this->mShootPaddingStandart = 200;
	this->mShootPadding = this->mShootPaddingStandart;

	this->mIsMove = false;

	this->mHealthRegenerationTime = 3.0f;
	this->mHealthRegenerationTimeElapsed = 0;

	this->mShootFromLeftHand = true;
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
	this->mIsMove = true;

	this->mFollowCoordinateX = pX;
	this->mFollowCoordinateY = pY;
}

void Hero::follow()
{
	if(this->mIsMove)
	{
		float x = this->getX() - this->mFollowCoordinateX / this->getSpeed();
		float y = this->getY() - this->mFollowCoordinateY / this->getSpeed();

		if(!this->collideCoordinatesWith(x, y, Options::BASE))
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

void Hero::fire(float pVectorX, float pVectorY)
{
	if(BarEntity::fire(pVectorX, pVectorY))
	{
		BaseBullet* bullet = ((BaseBullet*) this->mBulletsManager->create());
		bullet->fire(this->getX(), this->getY(), pVectorX, pVectorY);
	
		// this->mShootPadding = 100; // TODO: Too big value?

		// this->setSpeed(this->mSpeedStandart * 10);

		this->mPatrons--;

		if(this->getCurrentFrameIndex() > 0)
		{
			Entity* shootAnimator = this->mShootAnimators->create();
			shootAnimator->setCenterPosition(this->getWidth() / 2, this->getHeight() / 2);
			shootAnimator->animate(0.08f, (this->getCurrentFrameIndex() - 1) * 12 + (this->mShootFromLeftHand ? 5 : 0), (this->getCurrentFrameIndex() - 1) * 12 +  + (this->mShootFromLeftHand ? 10 : 5));

			this->mShootFromLeftHand = !this->mShootFromLeftHand;

			switch(bullet->getCurrentFrameIndex())
			{
				case 0:
					shootAnimator->setColor(ccc3(26.0,141.0,254.0));
				break;
				case 1:
					shootAnimator->setColor(ccc3(27.0,230.0,27.0));
				break;
				case 2:
					shootAnimator->setColor(ccc3(254.0,51.0,22.0));
				break;
				case 3:
					shootAnimator->setColor(ccc3(254.0,105.0,215.0));
				break;
				case 4:
					shootAnimator->setColor(ccc3(25.0,242.0,254.0));
				break;
				case 5:
					shootAnimator->setColor(ccc3(254.0,224.0,26.0));
				break;
				case 6:
					shootAnimator->setColor(ccc3(154.0,44.0,254.0));
				break;
				case 7:
					shootAnimator->setColor(ccc3(254.0,141.0,27.0));
				break;
				case 8:
					shootAnimator->setColor(ccc3(38.0,237.0,162.0));
				break;
				case 9:
					shootAnimator->setColor(ccc3(163.0,253.0,23.0));
				break;
			}
		}
	}
}

bool Hero::destroy()
{
	BarEntity::destroy();

	return false;
}

void Hero::setCurrentFrameIndex(int pIndex)
{
	BarEntity::setCurrentFrameIndex(pIndex);
}

void Hero::update(float pDeltaTime)
{
	if(!this->isVisible())
	{
		return;
	}

	BarEntity::update(pDeltaTime);

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
		float x = this->getX() + this->mFollowCoordinateX / this->mShootPadding;
		float y = this->getY() + this->mFollowCoordinateY / this->mShootPadding;

		if(!this->collideCoordinatesWith(x, y, Options::BASE))
		{
			this->setCenterPosition(x, y);
		}

		this->mShootPadding += 3;
	}
	else if(this->getSpeed() > this->mSpeedStandart)
	{
		this->setSpeed(this->getSpeed() - 50);

		this->mIsMove = false;
	}

	//this->mAltitude = this->mGas->getCurrentFrameIndex();

	
		this->mGasesAnimationTimeElapsed += pDeltaTime;

		if(this->mGasesAnimationTimeElapsed >= this->mGasesAnimationTime)
		{
			this->mGasesAnimationTimeElapsed = 0;

			this->mGases->create();
		}

	this->mHealthRegenerationTimeElapsed += pDeltaTime;

	if(this->mHealthRegenerationTimeElapsed >= this->mHealthRegenerationTime)
	{
		this->mHealthRegenerationTimeElapsed = 0;

		this->addHealth(1);
	}
}

void Hero::draw()
{
	BarEntity::draw();
return;
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