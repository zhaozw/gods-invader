#ifndef CONST_BASEENEMY_H
#define CONST_BASEENEMY_H

#include "cocos2d.h"

#include "BarEntity.h"
#include "BaseBullet.h"
#include "Hero.h"
#include "Options.h"
#include "Utils.h"

using namespace cocos2d;

class BaseEnemy : public BarEntity
{
	protected:
		float mSpeed;
		float mSpeedStandart;

		Hero* mHero;

		float mShootPadding;

		float mFollowPaddingX;
		float mFollowPaddingY;

		float mShootVectorX;
		float mShootVectorY;

		Entity* mShadow;

	private:

	public:
		BaseEnemy(Hero* pHero);
		BaseEnemy(const char* pszFileName, int pHorizontalFramesCount, int pVerticalFramesCount, Hero* pHero);

		float getSpeed(float pDeltaTime);

		void setSpeed(float pSpeed);

		void onCollide(BaseBullet* pBullet);

		void update(float pDeltaTime);

		/**
		 *
		 * Let's take care about object copy
		 *
		 */

		virtual BaseEnemy* deepCopy();	
};

#endif