#ifndef CONST_HERO_H
#define CONST_HERO_H

#include "cocos2d.h"

#include "HealthEntity.h"
#include "BaseBullet.h"
#include "EntityManager.h"
#include "Utils.h"

using namespace cocos2d;

class Hero : public HealthEntity
{
	protected:
		float mSpeed;
		float mSpeedStandart;
		float mPatrons;

		float mFollowCoordinateX;
		float mFollowCoordinateY;

		float mShootPaddingStandart;
		float mShootPadding;

		EntityManager* mBulletsManager;

		Entity* mShadow;

	private:

	public:
		bool mIsShouldFire;

		Hero(const char* pszFileName, EntityManager* pBulletsManager, int pHorizontalFramesCount, int pVerticalFramesCount);

		float getSpeed();
		float getPatrons();

		void setSpeed(float pSpeed);
		void setPatrons(float pPatrons);

		void setFollowCoordinates(float pX, float pY);
		void follow();

		void fire(float pX, float pY);

		void update(float pDeltaTime);

		virtual void draw();
};

#endif