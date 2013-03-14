#ifndef CONST_LEVEL_H
#define CONST_LEVEL_H

#include "cocos2d.h"
#include "AppDelegate.h"
#include "SimpleAudioEngine.h"

#include "Platform.h"
#include "Hero.h"
#include "BaseEnemy.h"
#include "BaseBullet.h"
#include "Pickup.h"
#include "BaseExplosion.h"
#include "Castle.h"
#include "Cloud.h"
#include "SmallCloud.h"
#include "EntityManager.h"
#include "Screen.h"
#include "Options.h"
#include "Utils.h"

using namespace cocos2d;

class Level : public Screen
{
	private:
		Entity* mBackgroundPart1;
		Entity* mBackgroundPart2;

		Entity* mPlatformPart1;
		Entity* mPlatformPart2;

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
		EntityManager* mSmallClouds;


		bool mShaking;

		float mShakeDuration;
		float mShakeDurationElapsed;
		float mShakeIntensity;

		bool mIsGameRunning;

	public:
		Level(void);

		void restart();

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

		virtual void onEnter();
		virtual void onExit();
};

#endif