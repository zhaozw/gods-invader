#ifndef CONST_FOLLOWENEMY
#define CONST_FOLLOWENEMY

#include "FollowEnemy.h"

// ===========================================================
// Inner Classes
// ===========================================================

// ===========================================================
// Constants
// ===========================================================

FollowEnemy::FollowEnemy(Entity* pFollowEntity) :
	BaseEnemy("enemies/onion/onion-animation.png", 7, 2)
	{
		this->mFollowEntity = pFollowEntity;
		
		this->setAsCollidable();

		this->setBarsManagement(true, false);

		this->mShadow->setCenterPosition(this->getWidth() / 2, this->getHeight() / 2 - Utils::coord(40));

		// Pupil

		this->mPupil = new Entity("enemies/onion/onion-pupil.png");
		this->addChild(this->mPupil);
		this->mPupil->setCenterPosition(this->getWidth() / 2, this->getHeight() / 2 - Utils::coord(9));

		// Shockwave

		this->mShockwave = new Entity("stolen/alien_shockwave.png");

		this->setAnimationStartTimeout(Utils::randomf(0.0f, 1.0f));
		this->animate(0.07f);

		//

		this->mShockwaveTime = 0.2f;
		this->mShockwaveTimeElapsed = 0;

		this->mShockwaveContinueTime = 1.0f;
		this->mShockwaveContinueTimeElapsed = 0;
	}

// ===========================================================
// Fields
// ===========================================================

// ===========================================================
// Constructors
// ===========================================================

// ===========================================================
// Methods
// ===========================================================

// ===========================================================
// Virtual Methods
// ===========================================================

Entity* FollowEnemy::create()
{
	if(!this->mShockwave->getParent())
	{
		this->getParent()->addChild(this->mShockwave, 0);

		this->mShockwave->destroy();
	}

	return BaseEnemy::create();
} 

void FollowEnemy::onCollide(Hero* pEntity)
{
	BaseEnemy::onCollide(pEntity);

	if(this->mShockwaveTimeElapsed <= 0 && this->mShockwaveContinueTimeElapsed >= this->mShockwaveContinueTime)
	{
		this->mShockwaveContinueTimeElapsed = 0;

		this->mShockwave->setScale(0);
		this->mShockwave->create()->runAction(CCScaleTo::create(this->mShockwaveTime, 2.5f));

		pEntity->mShootVectorX = this->mFollowEntity->getCenterX() - this->getCenterX();
		pEntity->mShootVectorY = this->mFollowEntity->getCenterY() - this->getCenterY();

		pEntity->mShootPadding = Utils::coord(8);

		if(Options::SOUND_ENABLE)
		{
			CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Sound/powerup_1.wav");
		}
	}
}

Entity* FollowEnemy::deepCopy()
{
	return new FollowEnemy(this->mFollowEntity);
}

void FollowEnemy::move(float pDeltaTime)
{
	float vectorX = this->getCenterX() - this->mFollowEntity->getCenterX();
	float vectorY = this->getCenterY() - this->mFollowEntity->getCenterY();

	CCPoint vector = Utils::vectorNormalize(vectorX, vectorY, this->getSpeed(pDeltaTime));

	this->setCenterPosition(this->getCenterX() - vector.x, this->getCenterY() - vector.y);

	CCPoint look = Utils::vectorNormalize(vectorX, vectorY, Utils::coord(6.0f));

	this->mPupil->setCenterPosition(this->getWidth() / 2 - look.x, this->getHeight() / 2 - Utils::coord(9) - look.y);
}

void FollowEnemy::update(float pDeltaTime)
{
	BaseEnemy::update(pDeltaTime);

	this->mShockwaveContinueTimeElapsed += pDeltaTime;

	if(this->mShockwave->isVisible())
	{
		this->mShockwave->setCenterPosition(this->getCenterX(), this->getCenterY() - Utils::coord(60));

		this->mShockwaveTimeElapsed += pDeltaTime;

		if(this->mShockwaveTimeElapsed >= this->mShockwaveTime)
		{
			this->mShockwaveTimeElapsed = 0;

			this->mShockwave->destroy();
		}
	}
}

#endif