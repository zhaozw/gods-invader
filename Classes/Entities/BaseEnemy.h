#ifndef CONST_BASEENEMY_H
#define CONST_BASEENEMY_H

#include "cocos2d.h"

#include "Entity.h"
#include "BaseBullet.h"
#include "Hero.h"
#include "Options.h"
#include "Utils.h"

using namespace cocos2d;

class BaseEnemy : public Entity
{
	protected:
		float mSpeed;
		float mSpeedStandart;
		float mHealth;

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

		float getSpeed();
		float getHealth();

		void setSpeed(float pSpeed);
		void setHealth(float pHealth);

		void onCollide(BaseBullet* pBullet);

		void update(float pDeltaTime);

		virtual void draw();

		/**
		 *
		 * Let's take care about object copy
		 *
		 */

		virtual BaseEnemy* deepCopy();	
};

#endif