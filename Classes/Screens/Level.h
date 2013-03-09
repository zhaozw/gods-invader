#ifndef CONST_LEVEL_H
#define CONST_LEVEL_H

#include "cocos2d.h"

#include "Hero.h"
#include "BaseEnemy.h"
#include "EntityManager.h"
#include "Screen.h"
#include "Options.h"
#include "Utils.h"

using namespace cocos2d;

class Level : public Screen
{
	private:
		Entity* mBackground;

		Hero* mHero;

		float mPointerX;
		float mPointerY;

		float mSortEntitiesTime;
		float mSortEntitiesTimeElapsed;

		EntityManager* mBaseEnemies;

	public:
		Level(void);

		bool ccTouchBegan(CCTouch* touch, CCEvent* event);

		void sortEntities();

		virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);

		virtual void update(float pDeltaTime);
};

#endif