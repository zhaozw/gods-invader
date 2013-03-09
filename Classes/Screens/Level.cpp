#ifndef CONST_LEVEL
#define CONST_LEVEL

#include "Level.h"

Level::Level(void)
{
	this->mSortEntitiesTime = 1;
	this->mSortEntitiesTimeElapsed = 1000;

	CCLayer* mUnitsLayer = new CCLayer();

	this->mBackground = new Entity("test/platform.png");
	this->mHero = new Hero("test/pr.png");

	this->mBackground->setCenterPosition(Options::CAMERA_CENTER_X, Options::CAMERA_CENTER_Y);
	this->mHero->setCenterPosition(Options::CAMERA_CENTER_X, Options::CAMERA_CENTER_Y);

	this->addChild(this->mBackground);
	mUnitsLayer->addChild(this->mHero);

	this->mBaseEnemies = new EntityManager(10, new BaseEnemy(mHero), mUnitsLayer);

	this->setRegisterAsTouchable(true);

	/////////////////// TEST //////////////////////

	for(int i = 0; i < 10; i++)
	{
		float x = Options::CAMERA_CENTER_X + 200 * cos(Utils::random(0, 360) * Utils::Pi / 180);
		float y = Options::CAMERA_CENTER_Y + 200 * sin(Utils::random(0, 360) * Utils::Pi / 180);

		this->mBaseEnemies->create()->setCenterPosition(x, y);
	}
	this->addChild(mUnitsLayer);
	/////////////////// TEST //////////////////////
}

bool Level::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
	if(Screen::ccTouchBegan(touch, event))
	{
		return true;
	}

	return false;
}

void Level::ccTouchMoved(CCTouch* touch, CCEvent* event)
{
	CCPoint location  = convertTouchToNodeSpaceAR(touch);

	this->mPointerX = location.x;
	this->mPointerY = location.y;
}

void Level::update(float pDeltaTime)
{
	if(this->mPointerX != 0 && this->mPointerY != 0)
	{
		float x = this->mHero->getX() - this->mPointerX;
		float y = this->mHero->getY() - this->mPointerY;

		this->mHero->setCenterPosition(this->mHero->getX() - x / this->mHero->getSpeed(), this->mHero->getY() - y / this->mHero->getSpeed());
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
}

void Level::sortEntities()
{
	this->mBaseEnemies->sortChildrenByYPosition();

	//this->removeChild(this->mHero);
	//this->addChild(this->mHero);
}

#endif