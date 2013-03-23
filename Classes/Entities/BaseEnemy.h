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

		float mShootPadding;

		float mFollowPaddingX;
		float mFollowPaddingY;

		float mShootVectorX;
		float mShootVectorY;

	private:

	public:
		BaseEnemy();
		BaseEnemy(Hero* pHero, EntityManager* pBullets);
		BaseEnemy(const char* pszFileName, int pHorizontalFramesCount, int pVerticalFramesCount);
		BaseEnemy(const char* pszFileName, int pHorizontalFramesCount, int pVerticalFramesCount, Hero* pHero, EntityManager* pBullets);

		virtual Entity* create();
		virtual bool destroy();

		virtual void onCollide(BaseBullet* pBullet);
		virtual void onCollide(Hero* pEntity);

		void update(float pDeltaTime);

		void fire();

		virtual void move(float pDeltaTime);
};

#endif