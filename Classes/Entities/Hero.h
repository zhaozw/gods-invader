#ifndef CONST_HERO_H
#define CONST_HERO_H

#include "cocos2d.h"

#include "BarEntity.h"
#include "BaseBullet.h"
#include "Gas.h"
#include "EntityManager.h"
#include "Utils.h"

using namespace cocos2d;

class GasShadow : public Entity
{
	public:
	GasShadow() :
		Entity()
		{
		}

	GasShadow(const char* pszFileName, int pHorizontalFramesCount, int pVerticalFramesCount) :
		Entity(pszFileName, pHorizontalFramesCount, pVerticalFramesCount)
		{
			this->setIsShadow();
		}

	GasShadow* deepCopy()
	{
		return new GasShadow("main-character/main-char-shadow-sprite.png", 12, 1);
	}
};

class Hero : public BarEntity
{
	class ShootAnimator : public Entity
	{
		public:
		ShootAnimator() :
			Entity("main-character/shoot-animation.png", 12, 4)
			{
			}

		void onAnimationEnd()
		{
			this->destroy();
		}

		void onAnimationStart()
		{
		}

		Entity* deepCopy()
		{
			return new ShootAnimator();
		}
	};

	protected:
		float mAltitude;
		float mSpeedStandart;
		float mPatrons;

		float mFollowCoordinateX;
		float mFollowCoordinateY;

		float mShootPaddingStandart;
		float mShootPadding;

		float mGasesAnimationTime;
		float mGasesAnimationTimeElapsed;

		float mHealthRegenerationTime;
		float mHealthRegenerationTimeElapsed;

		bool mIsMove;

		bool mShootFromLeftHand;

		EntityManager* mBulletsManager;
		EntityManager* mShootAnimators;

	private:

	public:
		EntityManager* mGases;
		EntityManager* mGasesShadows;

		bool mIsShouldFire;

		Hero(const char* pszFileName, EntityManager* pBulletsManager, int pHorizontalFramesCount, int pVerticalFramesCount);

		void reset();
		
		float getPatrons();

		virtual bool destroy();

		void setPatrons(float pPatrons);

		void setFollowCoordinates(float pX, float pY);
		void follow(float pDeltaTime);

		virtual void setCurrentFrameIndex(int pIndex);

		void fire(float pVectorX, float pVectorY);

		void update(float pDeltaTime);

		virtual void draw();
};

#endif