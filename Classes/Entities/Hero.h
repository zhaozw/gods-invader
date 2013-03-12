#ifndef CONST_HERO_H
#define CONST_HERO_H

#include "cocos2d.h"

#include "BarEntity.h"
#include "BaseBullet.h"
#include "Gas.h"
#include "EntityManager.h"
#include "Utils.h"

using namespace cocos2d;

class Hero : public BarEntity
{
	protected:
		float mAltitude;
		float mSpeed;
		float mSpeedStandart;
		float mPatrons;

		float mFollowCoordinateX;
		float mFollowCoordinateY;

		float mShootPaddingStandart;
		float mShootPadding;

		float mGasesAnimationTime;
		float mGasesAnimationTimeElapsed;

		bool mIsMove;

		EntityManager* mBulletsManager;


	private:

	public:
		EntityManager* mGases;

		Entity* mShadow;

		bool mIsShouldFire;

		Hero(const char* pszFileName, EntityManager* pBulletsManager, int pHorizontalFramesCount, int pVerticalFramesCount);

		float getSpeed();
		float getPatrons();

		void setSpeed(float pSpeed);
		void setPatrons(float pPatrons);

		void setFollowCoordinates(float pX, float pY);
		void follow();

		void fire(float pVectorX, float pVectorY);

		void update(float pDeltaTime);

		virtual void draw();
};

#endif