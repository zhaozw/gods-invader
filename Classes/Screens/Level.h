#ifndef CONST_LEVEL_H
#define CONST_LEVEL_H

#include "cocos2d.h"
#include "AppDelegate.h"
#include "SimpleAudioEngine.h"

#include "Platform.h"
#include "Hero.h"
#include "BaseEnemy.h"
#include "CastleEnemy.h"
#include "BaseBullet.h"
#include "Pickup.h"
#include "BaseExplosion.h"
#include "Castle.h"
#include "Star.h"
#include "Cloud.h"
#include "SmallCloud.h"
#include "SmallCubic.h"
#include "EntityManager.h"
#include "EntityManagerGroup.h"
#include "LayerManager.h"
#include "Screen.h"
#include "Options.h"
#include "Utils.h"

using namespace cocos2d;

class Level : public Screen
{
	class PlayButton : public Entity
	{
		private:
			Level* mParentScreen;

		public:
			PlayButton(Level* pParentScreen) :
				Entity("main-menu/play.png")
				{
					this->mParentScreen = pParentScreen;

					this->setRegisterAsTouchable(true);
				}

			void onTouch(CCTouch* touch, CCEvent* event)
			{
				this->mParentScreen->runMainMenuanimation();
			}
	};

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

		EntityManager* mBaseEnemies;
		EntityManager* mBaseEnemies2;

		EntityManagerGroup* mEnemiesGroup;

		EntityManager* mBaseBullets;
		EntityManager* mExplosions;
		EntityManager* mPickups;
		EntityManager* mSmallClouds;
		EntityManager* mClouds;
		EntityManager* mStars;
		EntityManager* mStaticPickups;
		EntityManager* mCandyDecorator;
		EntityManager* mCandyShadowsDecorator;
		EntityManager* mSmallCubics;

		LayerManager* mUnitsLayer;
		
		Entity* mPlayButton;

		bool mShaking;

		float mShakeDuration;
		float mShakeDurationElapsed;
		float mShakeIntensity;

		bool mIsGameRunning;
		bool mIsMainMenu;
		bool mIsMainMenuAnimationRunning;

		CCLayer* mControlLayer;
		CCLayer* mStaticLayer;

		float mSmallCubicGenerationTime;
		float mSmallCubicGenerationTimeElapsed;

	public:
		Level(void);

		void restart();

		void checkCollisions();

		void generateCloud();
		void generateStartSmalClouds();
		void generateSmallCloudsAndStars();

		void runMainMenuanimation();

		void shake(float d, float i);
		void updateShake(float pDeltaTime);

		bool ccTouchBegan(CCTouch* touch, CCEvent* event);
		void ccTouchMoved(CCTouch* touch, CCEvent* event);
		void ccTouchEnded(CCTouch* touch, CCEvent* event);

		virtual void update(float pDeltaTime);

		virtual void draw();

		virtual void onEnter();
		virtual void onExit();

		static int PICKUP_1_COUNT;
		static int PICKUP_2_COUNT;
		static int PICKUP_3_COUNT;
};

#endif