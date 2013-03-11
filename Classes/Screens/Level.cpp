#ifndef CONST_LEVEL
#define CONST_LEVEL

#include "Level.h"

Level::Level(void)
{
	Options::CENTER_X = Options::CAMERA_CENTER_X + Utils::coord(50);
	Options::CENTER_Y = Options::CAMERA_CENTER_Y + Utils::coord(200);

	this->mSortEntitiesTime = 1;
	this->mSortEntitiesTimeElapsed = 1000;

	CCLayer* mUnitsLayer = new CCLayer();

	this->mBackgroundSky = new Entity("platform/sky.png");
	this->mBackground = new Entity("platform/platform.png");
	this->mBaseBullets = new EntityManager(100, new BaseBullet(), mUnitsLayer);
	this->mHero = new Hero("main-character/main-char-sprite.png", this->mBaseBullets, 1, 5);

	this->mCastle = new Castle("base/base.png", 4, 2);
	this->mCastle->setCenterPosition(Options::CENTER_X, Options::CENTER_Y + Utils::coord(100));

	this->mCastleShadow = new Castle("base/base-shadow.png", 3, 1);
	this->mCastleShadow->setCenterPosition(Options::CENTER_X + Utils::coord(18), Options::CENTER_Y - Utils::coord(110));
	this->mCastleShadow->setIsShadow();

	this->mBackgroundSky->setCenterPosition(Options::CAMERA_CENTER_X, Options::CAMERA_CENTER_Y);
	this->mBackground->setCenterPosition(Options::CAMERA_CENTER_X, Options::CAMERA_CENTER_Y);
	this->mHero->setCenterPosition(Options::CAMERA_CENTER_X, Options::CAMERA_CENTER_Y);

	this->addChild(this->mBackgroundSky);
	this->addChild(this->mBackground);

	mUnitsLayer->addChild(this->mCastle);

	mUnitsLayer->addChild(this->mHero);

	this->mBaseEnemies = new EntityManager(10, new BaseEnemy(mHero), mUnitsLayer);

	this->mExplosions = new EntityManager(10, new BaseExplosion(), mUnitsLayer);
	this->setRegisterAsTouchable(true);
	mUnitsLayer->addChild(this->mCastleShadow);

	/////////////////// TEST //////////////////////

	for(int i = 0; i < 10; i++)
	{
		float x = Utils::random(-100, 100);
		float y = Utils::random(-100, 100);

		this->mBaseEnemies->create()->setCenterPosition(x, y);
	}
	this->addChild(mUnitsLayer);
	/////////////////// TEST //////////////////////

	this->mCastle->setCurrentFrameIndex(7);


Options::BASE = new Entity("test/base-test.png");
Options::BASE->setCenterPosition(Options::CENTER_X, Options::CENTER_Y);
Options::BASE->setVisible(false);
	this->addChild(Options::BASE);
}

bool Level::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
	if(Screen::ccTouchBegan(touch, event))
	{
		CCPoint location  = convertTouchToNodeSpaceAR(touch);

		this->mPointerX = location.x;
		this->mPointerY = location.y;

		this->mHero->mIsShouldFire = true;

		return true;
	}

	return false;
}

void Level::ccTouchEnded(CCTouch* touch, CCEvent* event)
{
	if(this->mHero->mIsShouldFire)
	{
		CCPoint location  = convertTouchToNodeSpaceAR(touch);

		this->mHero->fire(location.x, location.y);
	}
}

void Level::ccTouchMoved(CCTouch* touch, CCEvent* event)
{
	CCPoint location  = convertTouchToNodeSpaceAR(touch);

	if(abs(this->mPointerX - location.x) > 10 || abs(this->mPointerY - location.y) > 10 )
	{
		this->mHero->mIsShouldFire = false;
	}

	this->mPointerX = location.x;
	this->mPointerY = location.y;
}

void Level::update(float pDeltaTime)
{
	if(this->mPointerX != 0 && this->mPointerY != 0)
	{
		float x = this->mHero->getX() - this->mPointerX;
		float y = this->mHero->getY() - this->mPointerY;

		this->mHero->setFollowCoordinates(x, y);
	}

	/**
	 *
	 * Move camera to the hero coordinates
	 *
	 */

	float potencialX = -this->mHero->getX() + Options::CAMERA_CENTER_X;
	float potencialY = -this->mHero->getY() + Options::CAMERA_CENTER_Y;
	
	this->setPosition(potencialX, potencialY);

	/**
	 *
	 * Sort entities
	 *
	 */

	this->mSortEntitiesTimeElapsed += pDeltaTime;

	if(this->mSortEntitiesTimeElapsed >= this->mSortEntitiesTime)
	{
		this->mSortEntitiesTimeElapsed = 0;

		this->sortEntities();
	}

	// Castle shadow

	if(this->mCastle->getCurrentFrameIndex() >= 5)
	{
		this->mCastleShadow->setVisible(true);

		this->mCastleShadow->setCurrentFrameIndex(this->mCastle->getCurrentFrameIndex() - 5);
	}
	else
	{
		this->mCastleShadow->setVisible(false);
	}

	// Collisions

	this->checkCollisions();
}

void Level::sortEntities()
{
	this->mBaseEnemies->sortChildrenByYPosition();
}

void Level::checkCollisions()
{
	for(int i = 0; i < this->mBaseBullets->getCount(); i++)
	{
		for(int j = 0; j < this->mBaseEnemies->getCount(); j++)
		{
			BaseBullet* bullet = ((BaseBullet*) this->mBaseBullets->objectAtIndex(i));
			BaseEnemy* enemy = ((BaseEnemy*) this->mBaseEnemies->objectAtIndex(j));

			if (bullet->collideWith(enemy))
			{
				enemy->onCollide(bullet);
				bullet->destroy();

				if(enemy->getHealth() <= 0)
				{
					enemy->destroy();

					this->mExplosions->create()->setCenterPosition(enemy->getX(), enemy->getY());

					continue;
				}
			}

			if(this->mHero->collideWith(enemy))
			{
				this->mHero->setHealth(this->mHero->getHealth() - 1);
			}
		}
	}
}

#endif