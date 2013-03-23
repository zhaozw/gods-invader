#ifndef CONST_HERO
#define CONST_HERO

#include "Hero.h"
#include "BaseBullet.h"

Hero::Hero(const char* pszFileName, EntityManager* pBulletsManager, int pHorizontalFramesCount, int pVerticalFramesCount) :
	BarEntity(pszFileName, pHorizontalFramesCount, pVerticalFramesCount)
	{
		this->setAsCollidable();

		this->mShadow = new Entity("stolen/shadow.png");
		this->mShadow->setIsShadow();

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
	this->setFireTime(0.05);
	this->setPatrons(100);

	this->setZ(Options::MIN_Z);

	this->setHealth(100);

	this->mSpeedStandart = 200;

	this->setSpeed(this->mSpeedStandart); // I should remove this

	this->setCurrentFrameIndex(2);

	this->mFollowCoordinateX = 0;
	this->mFollowCoordinateY = 0;

	this->mShootPaddingStandart = 0;
	this->mShootPadding = this->mShootPaddingStandart;

	this->mIsMove = false;

	this->mHealthRegenerationTime = 3.0f;
	this->mHealthRegenerationTimeElapsed = 0;

	this->mShootFromLeftHand = true;
}

float Hero::getPatrons()
{
	return this->mPatrons;
}

void Hero::setPatrons(float pPatrons)
{
	this->mPatrons = pPatrons;
}

void Hero::setFollowCoordinates(float pX, float pY)
{
	this->mIsMove = true;

	this->mFollowCoordinateX = pX;
	this->mFollowCoordinateY = pY + this->getZ();
}

void Hero::follow(float pDeltaTime)
{
	if(this->mIsMove)
	{
		float x = this->mFollowCoordinateX / this->getSpeed(1); // TODO: I should use Utils::vectorNormalize here.
		float y = this->mFollowCoordinateY / this->getSpeed(1);

		float maxSpeed = Utils::coord(3);
		
		if(x < 0) x = x < -maxSpeed ? -maxSpeed : x;
		if(x > 0) x = x > maxSpeed ? maxSpeed : x;

		if(y < 0) y = y < -maxSpeed ? -maxSpeed : y;
		if(y > 0) y = y > maxSpeed ? maxSpeed : y;

		x = this->getCenterX() - x;
		y = this->getCenterY() - y;

		this->setCenterPosition(x, y);
	}
}

void Hero::fire(float pVectorX, float pVectorY)
{
	if(BarEntity::fire(pVectorX, pVectorY))
	{
		BaseBullet* bullet = ((BaseBullet*) this->mBulletsManager->create());
		bullet->fire(this->getCenterX(), this->getCenterY() + this->getZ(), pVectorX, pVectorY);
	
		// this->mShootPadding = 100; // TODO: Too big value?

		// this->setSpeed(this->mSpeedStandart * 10);

		this->mPatrons--;

		if(this->getCurrentFrameIndex() > 0)
		{
			Entity* shootAnimator = this->mShootAnimators->create();
			shootAnimator->setCenterPosition(this->getWidth() / 2, this->getHeight() / 2);
			shootAnimator->animate(0.08f, (this->getCurrentFrameIndex() - 1) * 12 + (this->mShootFromLeftHand ? 5 : 0), (this->getCurrentFrameIndex() - 1) * 12 +  + (this->mShootFromLeftHand ? 10 : 5), 1);

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
	
		if(Options::SOUND_ENABLE)
		{
			CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Sound/shot.wav");
		}
	}
}

void Hero::onCollide(BaseBullet* pBullet)
{
	this->removeHealth(pBullet->getPower());
	
	this->mShootVectorX = pBullet->mVectorX;
	this->mShootVectorY = pBullet->mVectorY;

	this->mShootPadding = Utils::coord(5); // UPGRADE
}

bool Hero::destroy()
{
	BarEntity::destroy();

	this->mShadow->destroy();

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

	this->follow(pDeltaTime);

	int pontencialFrame = 2;

	int padding1 = Utils::coord(50);
	int padding2 = Utils::coord(150);
	int padding3 = Utils::coord(100);

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

	
    // padding on collide

	if(this->mShootPadding > 0)
	{
		float x = this->mShootVectorX;
		float y = this->mShootVectorY;

		float speedX = x / sqrt(x * x + y * y) * this->mShootPadding;
		float speedY = y / sqrt(x * x + y * y) * this->mShootPadding;

		x = this->getCenterX() + speedX;
		y = this->getCenterY() + speedY;

		this->setCenterPosition(x, y);

		this->mShootPadding -= Utils::coord(0.3f);
	}
	else if(this->getSpeed(pDeltaTime) > this->mSpeedStandart)
	{
		//this->setSpeed(this->getSpeed(pDeltaTime) - 50);

		this->mIsMove = false;
	}

	//this->mAltitude = this->mGas->getCurrentFrameIndex();

	
	this->mGasesAnimationTimeElapsed += pDeltaTime;

	if(this->mGasesAnimationTimeElapsed >= this->mGasesAnimationTime && this->getZ() <= Options::MIN_Z)
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

#endif