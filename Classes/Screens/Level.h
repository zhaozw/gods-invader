#ifndef CONST_LEVEL_H
#define CONST_LEVEL_H

#include "cocos2d.h"

#include "Hero.h"
#include "BaseEnemy.h"
#include "BaseBullet.h"
#include "BaseExplosion.h"
#include "Castle.h"
#include "EntityManager.h"
#include "Screen.h"
#include "Options.h"
#include "Utils.h"

using namespace cocos2d;

class Level : public Screen
{
	private:
		Entity* mBackgroundSky;
		Entity* mBackground;

		Hero* mHero;

		Castle* mCastle;

		Entity* mCastleShadow;

		float mPointerX;
		float mPointerY;

		float mSortEntitiesTime;
		float mSortEntitiesTimeElapsed;

		EntityManager* mBaseEnemies;
		EntityManager* mBaseBullets;
		EntityManager* mExplosions;

	public:
		Level(void);

		void sortEntities();

		void checkCollisions();

		bool ccTouchBegan(CCTouch* touch, CCEvent* event);
		void ccTouchMoved(CCTouch* touch, CCEvent* event);
		void ccTouchEnded(CCTouch* touch, CCEvent* event);

		virtual void update(float pDeltaTime);
};

#endif