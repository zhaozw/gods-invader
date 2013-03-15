#ifndef CONST_LEVEL
#define CONST_LEVEL

#include "Level.h"

// ===========================================================
// Help classes
// ===========================================================

// ===========================================================
// Constructors
// ===========================================================

Level::Level(void)
{
	if(Options::MUSIC_ENABLE)
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("Music/game-music.ogg", true);
	}

	Options::CENTER_X = Options::CAMERA_CENTER_X + Utils::coord(50);
	Options::CENTER_Y = Options::CAMERA_CENTER_Y + Utils::coord(200);

	this->mSortEntitiesTime = 0.1f;
	this->mSortEntitiesTimeElapsed = 1000;

	CCLayer* mUnitsLayer = new CCLayer();
	CCLayer* mCloudsLayer = new CCLayer();
	this->mControlLayer = new CCLayer();

	this->mBackgroundPart1 = new Entity("main-menu/main-menu-background-part-1.png");
	this->mBackgroundPart2 = new Entity("main-menu/main-menu-background-part-2.png");

	this->mPlatformPart1 = new Platform("platform/platform-part-1.png");
	this->mPlatformPart2 = new Platform("platform/platform-part-2.png");

	this->mBaseBullets = new EntityManager(100, new BaseBullet(), mUnitsLayer);
	this->mHero = new Hero("main-character/main-char-sprite.png", this->mBaseBullets, 1, 5);

	this->mCastle = new Castle("base/base.png", 4, 2);
	this->mCastle->setCenterPosition(Options::CENTER_X, Options::CENTER_Y + Utils::coord(100) - Utils::coord(700));

	this->mCastleShadow = new Entity("base/base-shadow.png", 3, 1);
	this->mCastleShadow->setCenterPosition(Options::CENTER_X + Utils::coord(18), Options::CENTER_Y - Utils::coord(110) - Utils::coord(700));
	this->mCastleShadow->setIsShadow();

	this->mBackgroundPart1->setCenterPosition(Options::CAMERA_CENTER_X - this->mBackgroundPart1->getWidth() / 2, Options::CAMERA_CENTER_Y + Utils::coord(200));
	this->mBackgroundPart2->setCenterPosition(Options::CAMERA_CENTER_X + this->mBackgroundPart1->getWidth() / 2 - 1, Options::CAMERA_CENTER_Y + Utils::coord(200));

	this->mPlatformPart1->setCenterPosition(Options::CAMERA_CENTER_X - this->mPlatformPart1->getWidth() / 2, Options::CAMERA_CENTER_Y - Utils::coord(700));
	this->mPlatformPart2->setCenterPosition(Options::CAMERA_CENTER_X + this->mPlatformPart1->getWidth() / 2 - 1, Options::CAMERA_CENTER_Y - Utils::coord(700));

	this->addChild(this->mBackgroundPart1);
	this->addChild(this->mBackgroundPart2);

	this->mSmallClouds = new EntityManager(20, new SmallCloud(), this);
	this->mStars = new EntityManager(20, new Star(), this);

	this->addChild(this->mPlatformPart1);
	this->addChild(this->mPlatformPart2);

	mUnitsLayer->addChild(this->mCastle);

	this->mHero->mGasesShadows->setParent(this);
	this->mHero->mGases->setParent(this);

	mUnitsLayer->addChild(this->mHero);

	this->mPickups = new EntityManager(100, new Pickup(), mUnitsLayer);
	this->mBaseEnemies = new EntityManager(100, new BaseEnemy(mHero), mUnitsLayer);

	this->mExplosions = new EntityManager(100, new BaseExplosion(), mUnitsLayer);
	this->setRegisterAsTouchable(true);
	mUnitsLayer->addChild(this->mCastleShadow);

	this->addChild(mUnitsLayer);

	this->mCastle->setCurrentFrameIndex(7);

	this->mClouds = new EntityManager(2, new Cloud(), mCloudsLayer);
	this->addChild(mCloudsLayer);


Options::BASE = new Entity("test/base-test.png");
Options::BASE->setCenterPosition(Options::CENTER_X, Options::CENTER_Y);
//Options::BASE->setColor(ccc3(26.0,129.0,253.0));
Options::BASE->setVisible(false);
	this->addChild(Options::BASE);

	this->generateStartSmalClouds();

mControlLayer->setScale(1);
this->addChild(mControlLayer);

	this->mPlayButton = new PlayButton(this);
	this->mPlayButton->setCenterPosition(Options::CAMERA_CENTER_X, Options::CAMERA_CENTER_Y + Utils::coord(300));
	mControlLayer->addChild(this->mPlayButton);

	this->mHero->setVisible(false);

	this->mIsGameRunning = false;
	this->mIsMainMenu = true;
	this->mIsMainMenuAnimationRunning = false;


	this->mHero->setCenterPosition(Options::CAMERA_CENTER_X, Options::CAMERA_CENTER_Y);
}

void Level::restart()
{
	this->mIsMainMenu = false;

	this->removeChild(this->mControlLayer);

	this->mPlatformPart1->setCenterPosition(Options::CAMERA_CENTER_X - this->mPlatformPart1->getWidth() / 2, Options::CAMERA_CENTER_Y);
	this->mPlatformPart2->setCenterPosition(Options::CAMERA_CENTER_X + this->mPlatformPart1->getWidth() / 2 - 1, Options::CAMERA_CENTER_Y);

	this->mCastle->setCenterPosition(Options::CENTER_X, Options::CENTER_Y + Utils::coord(100));

	this->mBaseEnemies->clear();
	this->mPickups->clear();

	this->mHero->reset();
	this->mHero->setCenterPosition(Options::CAMERA_CENTER_X, Options::CAMERA_CENTER_Y);

	/////////////////// TEST //////////////////////

	for(int i = 0; i < 5; i++)
	{
		float x = Utils::random(-100, 100);
		float y = Utils::random(-100, 100);

		this->mBaseEnemies->create()->setCenterPosition(x, y);
	}
	/////////////////// TEST //////////////////////


	this->mShaking = false;
		
	this->mShakeDuration = 0;
	this->mShakeDurationElapsed = 0;
	this->mShakeIntensity = 0;

	this->mIsGameRunning = true;
}

void Level::runMainMenuanimation()
{
	this->mIsMainMenu = false;
	this->mIsMainMenuAnimationRunning = true;

	this->mPlatformPart1->runAction(CCMoveTo::create(1.0f, ccp(Options::CAMERA_CENTER_X - this->mPlatformPart1->getWidth() / 2, Options::CAMERA_CENTER_Y)));
	this->mPlatformPart2->runAction(CCMoveTo::create(1.0f, ccp(Options::CAMERA_CENTER_X + this->mPlatformPart1->getWidth() / 2 - 1, Options::CAMERA_CENTER_Y)));

	this->mCastle->runAction(CCMoveTo::create(1.0f, ccp(Options::CENTER_X, Options::CENTER_Y + Utils::coord(100))));

	this->runAction(CCScaleTo::create(1.0f, 1.0f));
}

bool Level::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
	if(Screen::ccTouchBegan(touch, event))
	{
		CCPoint location  = convertTouchToNodeSpaceAR(touch);

		this->mPointerX = location.x;
		this->mPointerY = location.y;

		this->mHero->mIsShouldFire = true;

	if(this->mPointerX != 0 && this->mPointerY != 0)
	{
		float x = this->mHero->getCenterX() - this->mPointerX;
		float y = this->mHero->getCenterY() - this->mPointerY;

		this->mHero->setFollowCoordinates(x, y);
	}

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
	
		if(Options::MUSIC_ENABLE)
		{
			CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Sound/shot.wav");
		}
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
	if(this->mPointerX != 0 && this->mPointerY != 0)
	{
		float x = this->mHero->getCenterX() - this->mPointerX;
		float y = this->mHero->getCenterY() - this->mPointerY;

		this->mHero->setFollowCoordinates(x, y);
	}
}

void Level::update(float pDeltaTime)
{
	if(this->mIsMainMenuAnimationRunning)
	{
		if(this->getScale() == 1)
		{
			this->mIsMainMenuAnimationRunning = false;

			this->restart();
		}
	}

	/**
	 *
	 * Move camera to the hero coordinates
	 *
	 */

	if(!this->mIsMainMenu)
	{
		float potencialX = -this->mHero->getCenterX()*this->getScale() + Options::CAMERA_CENTER_X;
		float potencialY = -this->mHero->getCenterY() + Options::CAMERA_CENTER_Y;
	
		float padding;

		if(this->mIsMainMenuAnimationRunning)
		{
			padding = 1.0f;
		}
		else
		{
			padding = 0;
		}

		this->setPosition(potencialX, potencialY - padding);
	}
	else
	{
		float potencialX = Options::CAMERA_CENTER_X - this->mPlayButton->getCenterX()*this->getScale();
		float potencialY = Options::CAMERA_CENTER_Y - this->mPlayButton->getCenterY() + Utils::coord(300);
	
		this->setPosition(potencialX, potencialY);
		this->setScale(0.5);
	}

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


	// Clouds
	this->generateSmallCloudsAndStars();

if(this->mIsGameRunning)
{
	// Clouds 

	this->generateCloud();

	// Collisions

	this->checkCollisions();

	/////////////////// TEST //////////////////////

	if(this->mBaseEnemies->getCount() < 10)
	{
		float x = Utils::random(-100, 100);
		float y = Utils::random(-100, 100);

		this->mBaseEnemies->create()->setCenterPosition(x, y);
	}
	this->mBaseEnemies->update(pDeltaTime);
	/////////////////// TEST //////////////////////

	this->mPickups->update(pDeltaTime);
}

	 // Shake 

	this->updateShake(pDeltaTime);
}

void Level::sortEntities()
{
	this->mBaseEnemies->sortChildrenByYPosition();
}

void Level::checkCollisions()
{
	for(int i = 0; i < this->mBaseEnemies->getCount(); i++)
	{
		BaseEnemy* enemy = ((BaseEnemy*) this->mBaseEnemies->objectAtIndex(i));

		for(int j = 0; j < this->mBaseBullets->getCount(); j++)
		{
			BaseBullet* bullet = ((BaseBullet*) this->mBaseBullets->objectAtIndex(j));

			if (bullet->collideWith(enemy))
			{
				enemy->onCollide(bullet);
				bullet->destroy();
			}
		}

		// EXPLOSIONS
		for(int j = 0; j < this->mExplosions->getCount(); j++)
		{
			Entity* explosion = ((Entity*) this->mExplosions->objectAtIndex(j));

			if(explosion->collideWith(enemy))
			{
				float padding = 3.5f;

				enemy->setCenterPosition(enemy->getCenterX() + (enemy->getCenterX() > explosion->getCenterX() ? padding : -padding), enemy->getCenterY() + (enemy->getCenterY() > explosion->getCenterY() ? padding : -padding));
				enemy->removeHealth(3.0f);
			}
		}

		// HERO

		if(this->mHero->collideWith(enemy))
		{
			this->mHero->removeHealth(1);
		}

		if(enemy->getHealth() <= 0)
		{
			if(Options::MUSIC_ENABLE)
			{
				CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Sound/ai_death.wav");
			}

			if(enemy->destroy())
			{
				this->mPickups->create()->setCenterPosition(enemy->getCenterX(), enemy->getCenterY());
			}

			this->mExplosions->create()->setCenterPosition(enemy->getCenterX(), enemy->getCenterY());

			this->shake(0.5f, 4.0f);

			continue;
		}
	}


	for(int i = 0; i < this->mPickups->getCount(); i++)
	{
		Pickup* pickup = ((Pickup*) this->mPickups->objectAtIndex(i));

		if(this->mHero->collideWith(pickup, 4.0f))
		{
			pickup->follow(this->mHero->getCenterX(), this->mHero->getCenterY());
		}

		if(this->mHero->collideWith(pickup))
		{
			switch(pickup->getCurrentFrameIndex())
			{
				case 0:
					if(Options::MUSIC_ENABLE)
					{
						CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Sound/health.wav");
					}
				break;
				case 1:
					if(Options::MUSIC_ENABLE)
					{
						CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Sound/coin.wav");
					} 
				break;
				case 2:
					if(Options::MUSIC_ENABLE)
					{
						CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Sound/health.wav");
					}

					this->mHero->addHealth(10);
				break;
			}

			pickup->destroy();
		}
	}

	if(this->mHero->getHealth() <= 0 && this->mHero->isVisible())
	{
		this->mExplosions->create()->setCenterPosition(this->mHero->getCenterX(), this->mHero->getCenterY());
	
		if(Options::MUSIC_ENABLE)
		{
			CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Sound/player_death.wav");
		}

		this->mIsGameRunning = false;

		this->mHero->setVisible(false);

		this->shake(3, 12);

		AppDelegate::screens->set(3.0f, 1);
	}
}

void Level::generateCloud()
{
	if(this->mClouds->getCount() < 2 && Utils::probably(1))
	{
		((Cloud*) this->mClouds->create())->init(this->mHero->getX(), this->mHero->getY(), this->mBackgroundPart1->getX(), this->mBackgroundPart2->getX() + this->mBackgroundPart2->getWidth(), this->mBackgroundPart1->getY(), this->mBackgroundPart2->getY() - this->mBackgroundPart2->getHeight());
	}
}

void Level::generateStartSmalClouds()
{
	for(int i = 0; i < 20; i++)
	{
		((SmallCloud*) this->mSmallClouds->create())->init(this->mBackgroundPart1->getX(), this->mBackgroundPart2->getX() + this->mBackgroundPart2->getWidth(), this->mBackgroundPart1->getY(), this->mBackgroundPart2->getY() - this->mBackgroundPart2->getHeight(), true);
	}
}

void Level::generateSmallCloudsAndStars()
{
	if(this->mSmallClouds->getCount() < 20)
	{
		((SmallCloud*) this->mSmallClouds->create())->init(this->mBackgroundPart1->getX(), this->mBackgroundPart2->getX() + this->mBackgroundPart2->getWidth(), this->mBackgroundPart1->getY(), this->mBackgroundPart2->getY() - this->mBackgroundPart2->getHeight(), false);
	}

	if(this->mStars->getCount() < 20)
	{
		((Star*) this->mStars->create())->init(this->mBackgroundPart1->getX(), this->mBackgroundPart2->getX() + this->mBackgroundPart2->getWidth(), this->mBackgroundPart1->getY(), this->mBackgroundPart2->getY() - this->mBackgroundPart2->getHeight());
	}
}

void Level::draw()
{
	Screen::draw();
}

void Level::shake(float d, float i)
{
	this->mShaking = true;
	this->mShakeDuration = d;
	this->mShakeIntensity = i;

	this->mShakeDurationElapsed = 0;
}

void Level::updateShake(float pDeltaTime)
{
	if(this->mShaking)
	{
		this->mShakeDurationElapsed += pDeltaTime;

		if(this->mShakeDurationElapsed > this->mShakeDuration)
		{
			this->mShaking = false;
			this->mShakeDuration = 0;
		}
		else
		{
			int sentitX = 1;
			int sentitY = 1;
			 	
			if(Utils::randomf(0, 1) < 0.5) sentitX = -1;
			if(Utils::randomf(0, 1) < 0.5) sentitY = -1;

			this->setPosition(this->getPosition().x + Utils::randomf(0, 1) * this->mShakeIntensity * sentitX, this->getPosition().y + Utils::randomf(0, 1) * this->mShakeIntensity * sentitY);
		}
	}
}

void Level::onEnter()
{
	Screen::onEnter();

	if(!this->mIsMainMenu)
	{
		this->restart();
	}
}

void Level::onExit()
{
	Screen::onExit();
}

#endif