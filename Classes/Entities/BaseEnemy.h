#ifndef CONST_BASEENEMY_H
#define CONST_BASEENEMY_H

#include "cocos2d.h"

#include "Entity.h"
#include "Hero.h"
#include "Options.h"
#include "Utils.h"

using namespace cocos2d;

class BaseEnemy : public Entity
{
	protected:
		int mSpeed;

		Hero* mHero;

		float mFollowPaddingX;
		float mFollowPaddingY;

		float previousCoordinateX;

	private:

	public:
		BaseEnemy(Hero* pHero);
		BaseEnemy(const char* pszFileName, Hero* pHero);

		float getSpeed();

		void setSpeed(float pSpeed);

		void update(float pDeltaTime);

		/**
		 *
		 * Let's take care about object copy
		 *
		 */

		virtual BaseEnemy* deepCopy();	
};

#endif