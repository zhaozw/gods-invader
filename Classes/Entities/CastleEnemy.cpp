#ifndef CONST_CASTLEENEMY
#define CONST_CASTLEENEMY

#include "CastleEnemy.h"

// ===========================================================
// Inner Classes
// ===========================================================

// ===========================================================
// Constants
// ===========================================================

CastleEnemy::CastleEnemy() :
	BaseEnemy("enemies/garlic/garlic-animation.png", 8, 2)
	{
		this->setAsCollidable();
		
		this->setBarsManagement(true, false);

		this->mShadow->setCenterPosition(this->getWidth() / 2, this->getHeight() / 2 - Utils::coord(40));

		this->setAnimationStartTimeout(Utils::randomf(0.0f, 1.0f));
		this->animate(0.1f, 0, 14);
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

Entity* CastleEnemy::deepCopy()
{
	return new CastleEnemy();
}

void CastleEnemy::move(float pDeltaTime)
{
	float vectorX = this->getCenterX() - Options::CENTER_X;
	float vectorY = this->getCenterY() - Options::CENTER_Y;

	CCPoint vector = Utils::vectorNormalize(vectorX, vectorY, this->getSpeed(pDeltaTime));

	float x = this->getCenterX() - vector.x;
	float y = this->getCenterY() - vector.y;

	this->setCenterPosition(x, y);
}

void CastleEnemy::update(float pDeltaTime)
{
	BaseEnemy::update(pDeltaTime);
}

#endif