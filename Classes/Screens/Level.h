#ifndef CONST_LEVEL_H
#define CONST_LEVEL_H

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

#include "Platform.h"
#include "Hero.h"
#include "BaseEnemy.h"
#include "BaseBullet.h"
#include "Pickup.h"
#include "BaseExplosion.h"
#include "Castle.h"
#include "Cloud.h"
#include "EntityManager.h"
#include "Screen.h"
#include "Options.h"
#include "Utils.h"

using namespace cocos2d;

class Level : public Screen
{
	private:
		Entity* mBackgroundSky;
		Platform* mBackground;

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
		EntityManager* mClouds;
		EntityManager* mPickups;

		Cloud* cloud;


		bool mShaking;

		float mShakeDuration;
		float mShakeDurationElapsed;
		float mShakeIntensity;

	public:
		Level(void);

		void sortEntities();

		void checkCollisions();

		void generateCloud();

		void shake(float d, float i);
		void updateShake(float pDeltaTime);

		bool ccTouchBegan(CCTouch* touch, CCEvent* event);
		void ccTouchMoved(CCTouch* touch, CCEvent* event);
		void ccTouchEnded(CCTouch* touch, CCEvent* event);

		virtual void update(float pDeltaTime);

		virtual void draw();
};

#endif