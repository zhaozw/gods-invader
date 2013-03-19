#ifndef CONST_BASEENEMY_H
#define CONST_BASEENEMY_H

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

#include "Texture.h"
#include "BarEntity.h"
#include "EntityManager.h"
#include "BaseBullet.h"
#include "Hero.h"
#include "Options.h"
#include "Utils.h"

using namespace cocos2d;

class BaseEnemy : public BarEntity
{
	protected:
		float mSpeedStandart;

		Hero* mHero;
		EntityManager* mBullets;

		Entity* mPupil;
		Entity* mEye;

		float mShootPadding;

		float mFollowPaddingX;
		float mFollowPaddingY;

		float mShootVectorX;
		float mShootVectorY;

		float mEyeAnimationTime;
		float mEyeAnimationTimeElapsed;

	private:

	public:
		BaseEnemy(Hero* pHero, EntityManager* pBullets);
		BaseEnemy(const char* pszFileName, int pHorizontalFramesCount, int pVerticalFramesCount, Hero* pHero, EntityManager* pBullets);

		virtual Entity* create();
		virtual bool destroy();

		void onCollide(BaseBullet* pBullet);

		void update(float pDeltaTime);

		void fire();

		/**
		 *
		 * Let's take care about object copy
		 *
		 */

		virtual BaseEnemy* deepCopy();	
};

#endif