#ifndef CONST_LEVEL
#define CONST_LEVEL

#include "Level.h"

int Level::PICKUP_1_COUNT = 0;
int Level::PICKUP_3_COUNT = 0;
int Level::PICKUP_2_COUNT = 0;

int Level::LEVEL = 0;

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

	this->mLastLowHealthLabelShowedTime = 0;

	this->mEnemiesGroup = new EntityManagerGroup(200);

	this->mUnitsLayer = new LayerManager();

	CCLayer* mCloudsLayer = new CCLayer();
	this->mControlLayer = new CCLayer();

	this->mBackgroundPart1 = new Entity("main-menu/main-menu-background-part-1.png");
	this->mBackgroundPart2 = new Entity("main-menu/main-menu-background-part-2.png");

	this->mPlatformPart1 = new Platform("platform/platform-part-1.png");
	this->mPlatformPart2 = new Platform("platform/platform-part-2.png");
	
	this->mCandyDecorator = new EntityManager(10, new Entity("platform/candy-sprite.png", 3, 1), mUnitsLayer);
	this->mCandyShadowsDecorator = new EntityManager(10, new Entity("platform/candy-sprite-shadow.png", 3, 1), mUnitsLayer);

	for(int i = 0; i < 0; i++)
	{
		Entity* decoration = this->mCandyDecorator->create();
		decoration->setCurrentFrameIndex(Utils::random(0, 2));
		decoration->setCenterPosition(Utils::random(this->mPlatformPart1->getX(), this->mPlatformPart2->getX() + this->mPlatformPart2->getWidth()), Utils::random(this->mPlatformPart1->getY() + Utils::coord(700), this->mPlatformPart1->getY() - this->mPlatformPart1->getHeight() + Utils::coord(700)));
		
		Entity* shadow = this->mCandyShadowsDecorator->create();
		shadow->setIsShadow();
		shadow->setIgnoreSorting(true);
		shadow->setCurrentFrameIndex(decoration->getCurrentFrameIndex());
		shadow->setCenterPosition(decoration->getCenterX(), decoration->getCenterY() - shadow->getHeight() / 2);
	}

	this->mSmallCubics = new EntityManager(25, new SmallCubic(), mUnitsLayer);

	this->mBaseBullets = new EntityManager(25, new BaseBullet(), mUnitsLayer);
	this->mEnemyBullets = new EntityManager(125, new BaseBullet(), mUnitsLayer);
	this->mHero = new Hero("main-character/main-char-sprite.png", this->mBaseBullets, 1, 5);


	this->mEnemyBullets->changeTexture(new Texture("stolen/alienbullet.png", 1, 1));

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

	mUnitsLayer->addChild(this->mHero);

	this->addChild(this->mHero->mShadow);
	this->mHero->mGasesShadows->setParent(this);
	this->mHero->mGases->setParent(this);

	this->mPickups = new EntityManager(10, new Pickup(), mUnitsLayer);
	this->mBaseEnemies2 = new EntityManager(25, new CastleEnemy(mHero, mEnemyBullets), mUnitsLayer);
	this->mBaseEnemies = new EntityManager(25, new BaseEnemy(mHero, mEnemyBullets), mUnitsLayer);

	this->mExplosions = new EntityManager(10, new BaseExplosion(), mUnitsLayer);
	this->setRegisterAsTouchable(true);
	mUnitsLayer->addChild(this->mCastleShadow);

	this->addChild(mUnitsLayer);

	this->mClouds = new EntityManager(2, new Cloud(), mCloudsLayer);
	this->addChild(mCloudsLayer);


	Options::BASE = new Entity("test/base-test.png");
	Options::BASE->setCenterPosition(Options::CENTER_X, Options::CENTER_Y);
	Options::BASE->setVisible(false);

	this->addChild(Options::BASE);

	this->generateStartSmalClouds();

	mControlLayer->setScale(1);
	this->addChild(mControlLayer);

	this->mPlayButton = new PlayButton(this);
	this->mPlayButton->setCenterPosition(Options::CAMERA_CENTER_X, Options::CAMERA_CENTER_Y + Utils::coord(100));
	mControlLayer->addChild(this->mPlayButton);

	this->mHero->setVisible(false);

	this->mIsGameRunning = false;
	this->mIsMainMenu = true;
	this->mIsMainMenuAnimationRunning = false;


	this->mHero->setCenterPosition(Options::CAMERA_CENTER_X, Options::CAMERA_CENTER_Y);

	this->mStaticLayer = new CCLayer();
	this->addChild(mStaticLayer);
	this->mStaticPickups = new EntityManager(100, new Entity("stolen/pickup-icon.png", 1, 3), mStaticLayer);

	this->mSmallCubicGenerationTimeElapsed = 0;
	this->mSmallCubicGenerationTime = 1;

	this->mEnemiesGroup->add(this->mBaseEnemies);
	this->mEnemiesGroup->add(this->mBaseEnemies2);

	this->mPrepareForBattleLabel = new Label("labels/prepare.png");
	this->mLowHealthLabel = new Label("labels/low-health.png");
	this->mLevelClearedLabel = new Label("labels/level-cleared.png");
	this->mLevelNumberLabel = new Label("labels/level-number.png", 1, 2);

	this->mJumpButton = new JumpButton(this->mHero);

	this->mLowHealthLabel->setCenterPosition(Options::CAMERA_CENTER_X, Options::CAMERA_CENTER_Y + Utils::coord(200));
	this->mPrepareForBattleLabel->setCenterPosition(Options::CAMERA_CENTER_X, Options::CAMERA_CENTER_Y + Utils::coord(200));
	this->mLevelClearedLabel->setCenterPosition(Options::CAMERA_CENTER_X, Options::CAMERA_CENTER_Y - Utils::coord(200));
	this->mLevelNumberLabel->setCenterPosition(Options::CAMERA_CENTER_X, Options::CAMERA_CENTER_Y - Utils::coord(200));

	this->mJumpButton->setCenterPosition(Options::CAMERA_WIDTH - Utils::coord(100), Utils::coord(200));

	this->mStaticLayer->addChild(this->mLowHealthLabel);
	this->mStaticLayer->addChild(this->mPrepareForBattleLabel);
	this->mStaticLayer->addChild(this->mLevelClearedLabel);
	this->mStaticLayer->addChild(this->mLevelNumberLabel);

	this->mStaticLayer->addChild(this->mJumpButton);

	this->mLevelShouldStart = false;
	this->mLevelStartTime = 0;
}

void Level::restart()
{
	PICKUP_1_COUNT = 0;
	PICKUP_3_COUNT = 0;
	PICKUP_2_COUNT = 0;

	this->mIsMainMenu = false;

	this->removeChild(this->mControlLayer);

	this->mPlatformPart1->setCenterPosition(Options::CAMERA_CENTER_X - this->mPlatformPart1->getWidth() / 2, Options::CAMERA_CENTER_Y);
	this->mPlatformPart2->setCenterPosition(Options::CAMERA_CENTER_X + this->mPlatformPart1->getWidth() / 2 - 1, Options::CAMERA_CENTER_Y);

	this->mCastle->setCenterPosition(Options::CENTER_X, Options::CENTER_Y + Utils::coord(100));

	this->mBaseEnemies->clear();
	this->mBaseEnemies2->clear();
	this->mPickups->clear();
	this->mStaticPickups->clear();

	this->mHero->reset();
	this->mHero->setCenterPosition(Options::CAMERA_CENTER_X, Options::CAMERA_CENTER_Y);

	this->mShaking = false;
		
	this->mShakeDuration = 0;
	this->mShakeDurationElapsed = 0;
	this->mShakeIntensity = 0;

	this->mIsGameRunning = true;

	this->mPrepareForBattleLabel->show(3.0f, 5.0f);

	this->mLevelShouldStart = true;
	this->mLevelStartTime = 10.0f;
}

void Level::startLevel()
{
	/////////////////// TEST //////////////////////

	if(this->mBaseEnemies->getCount() < 1)
	{
		for(int i = 0; i < 10; i++)
		{
			this->mBaseEnemies->create()->setCenterPosition(100, 100);
		}
	}

	/////////////////// TEST //////////////////////

	this->mLevelShouldStart = false;

	this->mLevelNumberLabel->setCurrentFrameIndex(LEVEL);
	this->mLevelNumberLabel->show(3.0f);

	LEVEL++;
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
		float potencialX = -this->mHero->getCenterX() * this->getScale() + Options::CAMERA_CENTER_X;
		float potencialY = -this->mHero->getCenterY() + Options::CAMERA_CENTER_Y; // TODO: Maybe I should add Z coordinate?
	
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

		potencialX = this->mHero->getCenterX() - Options::CAMERA_CENTER_X;
		potencialY = this->mHero->getCenterY() - Options::CAMERA_CENTER_Y;
		this->mStaticLayer->setPosition(potencialX, potencialY - padding);
	}
	else
	{
		float potencialX = Options::CAMERA_CENTER_X - this->mPlayButton->getCenterX()*this->getScale();
		float potencialY = Options::CAMERA_CENTER_Y - this->mPlayButton->getCenterY() + Utils::coord(100);
	
		this->setPosition(potencialX, potencialY);
		this->setScale(0.5);
	}

	//

	if(!this->mIsMainMenu)
	{
		
	if(this->mLevelShouldStart)
	{
		this->mLevelStartTime -= pDeltaTime;

		if(this->mLevelStartTime <= 0)
		{
			this->startLevel();
		}
	}
	else if(LEVEL > 0)
	{
		if(this->mBaseEnemies->getCount() == 0)
		{
			this->mLevelClearedLabel->show(5.0f);

			this->mLevelShouldStart = true;
			this->mLevelStartTime = 10.0f;
		}
	}

	// Lables

this->mLastLowHealthLabelShowedTime += pDeltaTime;

		if(this->mHero->getHealth() <= this->mHero->getMaxHealth() / 3 && this->mLastLowHealthLabelShowedTime >= 10.0f)
		{
			this->mLowHealthLabel->show(3.0f);

			this->mLastLowHealthLabelShowedTime = 0;
		}
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
	this->mUnitsLayer->update(pDeltaTime);

	// Clouds 

	this->generateCloud();

	// Collisions

	this->checkCollisions();

	this->mEnemiesGroup->update(pDeltaTime);

	this->mPickups->update(pDeltaTime);
}

	 // Shake 

	this->updateShake(pDeltaTime);

	this->mSmallCubicGenerationTimeElapsed += pDeltaTime;

	if(this->mSmallCubicGenerationTimeElapsed >= this->mSmallCubicGenerationTime)
	{
		this->mSmallCubicGenerationTimeElapsed = 0;

		if(Utils::probably(100))
		{
			//this->mSmallCubics->create()->setCenterPosition(Utils::random(this->mPlatformPart1->getX(), this->mPlatformPart2->getX() + this->mPlatformPart2->getWidth()), Utils::random(this->mPlatformPart1->getY() + Utils::coord(700), this->mPlatformPart1->getY() - this->mPlatformPart1->getHeight() + Utils::coord(700)));
		}
	}
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
				float padding = Utils::coord(3.5f);

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

	for(int i = 0; i < this->mEnemyBullets->getCount(); i++)
	{
		BaseBullet* bullet = (BaseBullet*) this->mEnemyBullets->objectAtIndex(i);

		if(this->mHero->collideWith(bullet))
		{
			this->mHero->onCollide(bullet);

			bullet->destroy();
		}
	}

 ///////////////////////////////////////// HOLY SHIIIIIIIT!!!!!!!!!!!!! ////////////////////////////


	for(int i = 0; i < this->mBaseEnemies2->getCount(); i++)
	{
		BaseEnemy* enemy = ((BaseEnemy*) this->mBaseEnemies2->objectAtIndex(i));

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
				float padding = Utils::coord(3.5f);

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
	////////////////////////////////////////////////////////////////

	for(int i = 0; i < this->mPickups->getCount(); i++)
	{
		Pickup* pickup = ((Pickup*) this->mPickups->objectAtIndex(i));

		if(this->mHero->collideWith(pickup, Utils::coord(4.0f)))
		{
			pickup->follow(this->mHero->getCenterX(), this->mHero->getCenterY());
		}

		if(this->mHero->collideWith(pickup) && !pickup->mIsMustDestroy)
		{
			switch(pickup->getCurrentFrameIndex())
			{
				case 0:
					if(Options::MUSIC_ENABLE)
					{
						CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Sound/health.wav");
					}

					PICKUP_1_COUNT++;
				break;
				case 1:
					if(Options::MUSIC_ENABLE)
					{
						CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Sound/coin.wav");
					}

					PICKUP_2_COUNT++;
				break;
				case 2:
					if(Options::MUSIC_ENABLE)
					{
						CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Sound/health.wav");
					}

					this->mHero->addHealth(10);

					PICKUP_3_COUNT++;
				break;
			}
	
			Entity* pic = this->mStaticPickups->create();
			pic->setCurrentFrameIndex(pickup->getCurrentFrameIndex());
			pic->setCenterPosition(50 + pic->getWidth()/2 * (this->mStaticPickups->getCount() + 1), pic->getHeight() - Utils::coord(25));

			pickup->startDestroy();
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