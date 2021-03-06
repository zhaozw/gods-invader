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
	if(Options::SOUND_ENABLE)
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("Music/game-music.ogg", true);
	}

	this->mHeroMustJump = false;

	Options::CENTER_X = Options::CAMERA_CENTER_X + Utils::coord(50);
	Options::CENTER_Y = Options::CAMERA_CENTER_Y + Utils::coord(200);

	this->mLastLowHealthLabelShowedTime = 0;

	this->mEnemiesGroup = new EntityManagerGroup(200);

	this->mUnitsLayer = new LayerManager();
	this->mUnitsLayer->setVisible(false);

	Layer* mCloudsLayer = new Layer();
	this->mControlLayer = new Layer();
	this->mMainLayer = new Layer();

	this->mBackgroundPart1 = new Entity("main-menu/main-menu-background-part-1.png");
	this->mBackgroundPart2 = new Entity("main-menu/main-menu-background-part-2.png");

	this->mPlatformPart1 = new Platform("platform/platform-part-1.png");
	this->mPlatformPart2 = new Platform("platform/platform-part-2.png");
	
	this->mCandyDecorator = new EntityManager(10, new Entity("platform/candy-sprite.png", 3, 1), mUnitsLayer);
	this->mCandyShadowsDecorator = new EntityManager(10, new Entity("platform/candy-sprite-shadow.png", 3, 1), mUnitsLayer);

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

	this->mBackgroundPart1->setCenterPosition(Options::CAMERA_CENTER_X - this->mBackgroundPart1->getWidth() / 2, Options::CAMERA_CENTER_Y - Utils::coord(200));
	this->mBackgroundPart2->setCenterPosition(Options::CAMERA_CENTER_X + this->mBackgroundPart1->getWidth() / 2 - 1, Options::CAMERA_CENTER_Y - Utils::coord(200));

	this->mPlatformPart1->setCenterPosition(Options::CAMERA_CENTER_X - this->mPlatformPart1->getWidth() / 2, Options::CAMERA_CENTER_Y - Utils::coord(1200));
	this->mPlatformPart2->setCenterPosition(Options::CAMERA_CENTER_X + this->mPlatformPart1->getWidth() / 2 - 1, Options::CAMERA_CENTER_Y - Utils::coord(1200));

	for(int i = 0; i < 0; i++) // TODO: Candies.
	{
		Entity* decoration = this->mCandyDecorator->create();
		decoration->setCurrentFrameIndex(Utils::random(0, 2));
		decoration->setCenterPosition(Utils::random(this->mPlatformPart1->getX(), this->mPlatformPart2->getX() + this->mPlatformPart2->getWidth()),
			Utils::random(this->mPlatformPart1->getY() + Utils::coord(700), this->mPlatformPart1->getY() - this->mPlatformPart1->getHeight() + Utils::coord(700)));
		
		Entity* shadow = this->mCandyShadowsDecorator->create();
		shadow->setIsShadow();
		shadow->setIgnoreSorting(true);
		shadow->setCurrentFrameIndex(decoration->getCurrentFrameIndex());
		shadow->setCenterPosition(decoration->getCenterX(), decoration->getCenterY() - shadow->getHeight() + Utils::coord(25));
	}

	this->mMainLayer->addChild(this->mBackgroundPart1);
	this->mMainLayer->addChild(this->mBackgroundPart2);

	this->mStars = new EntityManager(20, new Star(), this->mMainLayer);
	this->mSmallClouds = new EntityManager(20, new SmallCloud(), this->mMainLayer);

	this->mMainLayer->addChild(this->mPlatformPart1);
	this->mMainLayer->addChild(this->mPlatformPart2);

	mUnitsLayer->addChild(this->mCastle, 1);
	this->mCastle->setIgnoreSorting(true);

	mUnitsLayer->addChild(this->mHero, 1);

	this->mMainLayer->addChild(this->mHero->mShadow);
	this->mHero->mGasesShadows->setParent(this->mMainLayer);
	this->mHero->mGases->setParent(this->mMainLayer);

	this->mPickups = new EntityManager(10, new Pickup(), mUnitsLayer);
	this->mBaseEnemies2 = new EntityManager(25, new CastleEnemy(), mUnitsLayer, 1);
	this->mBaseEnemies = new EntityManager(25, new FollowEnemy(mHero), mUnitsLayer, 1);

	this->mExplosions = new EntityManager(10, new BaseExplosion(), mUnitsLayer);
	this->setRegisterAsTouchable(true);
	mUnitsLayer->addChild(this->mCastleShadow);

	this->mMainLayer->addChild(mUnitsLayer);

	this->mClouds = new EntityManager(2, new Cloud(), mCloudsLayer);
	this->mMainLayer->addChild(mCloudsLayer);

	Options::BASE = new Entity("test/base-test.png");
	Options::BASE->setCenterPosition(Options::CENTER_X, Options::CENTER_Y);
	Options::BASE->setVisible(false);

	this->mMainLayer->addChild(Options::BASE);

	this->generateStartSmalClouds();

	// BUTTONS

	this->mButtonsHolder1 = new ButtonHolder("controls/context-bg.png");
	this->mButtonsHolder2 = new ButtonHolder("controls/context-bg.png");

	this->mSettingsButton = new SettingsButton(this);
	this->mSocialButton = new SocialButton(this);

	this->mCreditsButton = new CreditsButton();

	this->mMusicButton = new MusicButton();
	this->mSoundButton = new SoundButton();

	this->mMoreGamesButton = new MoreGamesButton();
	this->mFacebookButton = new FacebookButton();
	this->mTwitterButton = new TwitterButton();

	this->mButtonsHolder1->setCenterPosition(Utils::coord(90), Utils::coord(90));
	this->mButtonsHolder2->setCenterPosition(Options::CAMERA_WIDTH - Utils::coord(90), Utils::coord(90));

	this->mSettingsButton->setCenterPosition(Utils::coord(90), Utils::coord(90));
	this->mSocialButton->setCenterPosition(Options::CAMERA_WIDTH - Utils::coord(90), Utils::coord(90));

	this->mCreditsButton->setCenterPosition(Utils::coord(90), Utils::coord(0));
	this->mMusicButton->setCenterPosition(Utils::coord(90), -Utils::coord(80));
	this->mSoundButton->setCenterPosition(Utils::coord(90), -Utils::coord(170));

	this->mMoreGamesButton->setCenterPosition(Options::CAMERA_WIDTH - Utils::coord(90), Utils::coord(0));
	this->mFacebookButton->setCenterPosition(Options::CAMERA_WIDTH - Utils::coord(90), -Utils::coord(80));
	this->mTwitterButton->setCenterPosition(Options::CAMERA_WIDTH - Utils::coord(90), -Utils::coord(170));

	mControlLayer->addChild(mButtonsHolder1);
	mControlLayer->addChild(mButtonsHolder2);

	mControlLayer->addChild(this->mCreditsButton);
	mControlLayer->addChild(this->mMusicButton);
	mControlLayer->addChild(this->mSoundButton);

	mControlLayer->addChild(this->mMoreGamesButton);
	mControlLayer->addChild(this->mFacebookButton);
	mControlLayer->addChild(this->mTwitterButton);

	mControlLayer->addChild(mSettingsButton);
	mControlLayer->addChild(mSocialButton);

	this->mMusicButton->setCurrentFrameIndex(Options::MUSIC_ENABLE ? 0 : 1);
	this->mSoundButton->setCurrentFrameIndex(Options::SOUND_ENABLE ? 0 : 1);

	//

	this->mPlayButton = new PlayButton(this);
	this->mPlayButton->setCenterPosition(Options::CAMERA_CENTER_X, Options::CAMERA_CENTER_Y + Utils::coord(100));
	mControlLayer->addChild(this->mPlayButton);

	this->mHero->setVisible(false);

	this->mIsGameRunning = false;
	this->mIsMainMenu = true;
	this->mIsMainMenuAnimationRunning = false;


	this->mHero->setCenterPosition(Options::CAMERA_CENTER_X, Options::CAMERA_CENTER_Y);

	this->mStaticLayer = new Layer();
	this->mStaticPickups = new EntityManager(100, new Entity("stolen/pickup-icon.png", 1, 3), mStaticLayer);

	//

	this->mPauseButton = new PauseButton();

	this->mPauseButton->setPosition(Options::CAMERA_WIDTH - Utils::coord(20), Options::CAMERA_HEIGHT - Utils::coord(110));

	this->mStaticLayer->addChild(this->mPauseButton);

	//

	this->mSmallCubicGenerationTimeElapsed = 0;
	this->mSmallCubicGenerationTime = 1;

	this->mEnemiesGroup->add(this->mBaseEnemies);
	this->mEnemiesGroup->add(this->mBaseEnemies2);

	this->mPrepareForBattleLabel = new Label("labels/prepare.png");
	this->mLowHealthLabel = new Label("labels/low-health.png");
	this->mLevelClearedLabel = new Label("labels/level-cleared.png");
	this->mLevelNumberLabel = new Label("labels/level-number.png");

	this->mJumpButton = new JumpButton(this);

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

	this->addChild(this->mMainLayer);
	this->addChild(this->mControlLayer);
	this->addChild(this->mStaticLayer);

	this->mStaticLayer->setOpacity(0.0f);
	this->mControlLayer->setOpacity(255.0f);

	this->mMainLayer->setPosition(this->mMainLayer->getPosition().x, this->mMainLayer->getPosition().y - Utils::coord(250));
	this->mMainLayer->setScale(0.5);
}

void Level::restart()
{
	PICKUP_1_COUNT = 0;
	PICKUP_3_COUNT = 0;
	PICKUP_2_COUNT = 0;

	LEVEL = 0;

	this->mIsMainMenu = false;

	this->removeChild(this->mControlLayer);

	this->mPlatformPart1->setCenterPosition(Options::CAMERA_CENTER_X - this->mPlatformPart1->getWidth() / 2, Options::CAMERA_CENTER_Y);
	this->mPlatformPart2->setCenterPosition(Options::CAMERA_CENTER_X + this->mPlatformPart1->getWidth() / 2 - 1, Options::CAMERA_CENTER_Y);

	this->mBackgroundPart1->setCenterPosition(Options::CAMERA_CENTER_X - this->mBackgroundPart1->getWidth() / 2, Options::CAMERA_CENTER_Y + Utils::coord(200));
	this->mBackgroundPart2->setCenterPosition(Options::CAMERA_CENTER_X + this->mBackgroundPart1->getWidth() / 2 - 1, Options::CAMERA_CENTER_Y + Utils::coord(200));

	this->mCastle->setCenterPosition(Options::CENTER_X, Options::CENTER_Y + Utils::coord(100));

	this->mLowHealthLabel->destroy();
	this->mPrepareForBattleLabel->destroy();
	this->mLevelClearedLabel->destroy();
	this->mLevelNumberLabel->destroy();

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

	this->mUnitsLayer->setVisible(true);
}

void Level::startLevel()
{
	if(Options::SOUND_ENABLE)
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Sound/start_level.wav");
	}

	/////////////////// TEST //////////////////////

	if(this->mBaseEnemies->getCount() < 1 && this->mBaseEnemies2->getCount() < 1)
	{
		float x = 100;
		float y = 100;

		for(int i = 0; i < 10; i++)
		{
			x += 40;

			if(i==5) {
				x= 100;
				y += 40;
			}

			this->mBaseEnemies->create()->setCenterPosition(x, y);
		}

		x = 400;
		y = 400;

		for(int i = 0; i < 10; i++)
		{
			x += 40;

			if(i==5) {
				x= 100;
				y += 40;
			}

			this->mBaseEnemies2->create()->setCenterPosition(x, y);
		}
	}

	/////////////////// TEST //////////////////////

	this->mLevelShouldStart = false;

	this->mLevelNumberLabel->show(3.0f);

	LEVEL++;
}

void Level::runMainMenuanimation()
{
	this->mIsMainMenu = false;
	this->mIsMainMenuAnimationRunning = true;

	this->mBackgroundPart1->runAction(CCMoveTo::create(1.0f, ccp(Options::CAMERA_CENTER_X - this->mBackgroundPart1->getWidth() / 2, Options::CAMERA_CENTER_Y + Utils::coord(200))));
	this->mBackgroundPart2->runAction(CCMoveTo::create(1.0f, ccp(Options::CAMERA_CENTER_X + this->mBackgroundPart1->getWidth() / 2 - 1, Options::CAMERA_CENTER_Y + Utils::coord(200))));

	this->mPlatformPart1->runAction(CCMoveTo::create(1.0f, ccp(Options::CAMERA_CENTER_X - this->mPlatformPart1->getWidth() / 2, Options::CAMERA_CENTER_Y)));
	this->mPlatformPart2->runAction(CCMoveTo::create(1.0f, ccp(Options::CAMERA_CENTER_X + this->mPlatformPart1->getWidth() / 2 - 1, Options::CAMERA_CENTER_Y)));

	this->mCastle->runAction(CCMoveTo::create(1.0f, ccp(Options::CENTER_X, Options::CENTER_Y + Utils::coord(100))));

	this->mMainLayer->runAction(CCScaleTo::create(1.0f, 1.0f));

	this->mControlLayer->runAction(CCFadeTo::create(1.0f, 0.0f));
	this->mStaticLayer->runAction(CCFadeTo::create(1.0f, 255.0f));
}

bool Level::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
	if(Screen::ccTouchBegan(touch, event))
	{
		CCPoint location  = mUnitsLayer->convertTouchToNodeSpaceAR(touch);

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
		CCPoint location  = mUnitsLayer->convertTouchToNodeSpaceAR(touch);

		this->mHero->fire(location.x, location.y);
	}
}

void Level::ccTouchMoved(CCTouch* touch, CCEvent* event)
{
	CCPoint location  = mUnitsLayer->convertTouchToNodeSpaceAR(touch);

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
		if(this->mMainLayer->getScale() == 1)
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

	if(true)
	{
		float potencialX = -this->mHero->getCenterX() + Options::CAMERA_CENTER_X;
		float potencialY = -this->mHero->getCenterY() + Options::CAMERA_CENTER_Y + this->mHero->getZ();

		this->mMainLayer->setPosition(potencialX, potencialY);
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
				if(LEVEL > 10) // TODO: Last level.
				{
					AppDelegate::screens->set(3.0f, 2);
				}

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

	// Hero jump

	if(this->mHeroMustJump)
	{
			this->mHero->addZ(3);
	}
	else
	{
		if(this->mHero->getZ() > Options::MIN_Z)
		{
			this->mHero->removeZ(1);
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
			enemy->onCollide(this->mHero);

			this->mHero->removeHealth(0.1f);
		}

		if(enemy->getHealth() <= 0)
		{
			if(Options::SOUND_ENABLE)
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
			this->mHero->removeHealth(0.1f);
		}

		if(enemy->getHealth() <= 0)
		{
			if(Options::SOUND_ENABLE)
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
			pickup->follow(this->mHero->getCenterX(), this->mHero->getCenterY() + this->mHero->getZ());
		}

		if(this->mHero->collideWith(pickup) && !pickup->mIsMustDestroy)
		{
			switch(pickup->getCurrentFrameIndex())
			{
				case 0:
					if(Options::SOUND_ENABLE)
					{
						CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Sound/health.wav");
					}

					PICKUP_1_COUNT++;
				break;
				case 1:
					if(Options::SOUND_ENABLE)
					{
						CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Sound/coin.wav");
					}

					PICKUP_2_COUNT++;
				break;
				case 2:
					if(Options::SOUND_ENABLE)
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
	
		if(Options::SOUND_ENABLE)
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

			this->mMainLayer->setPosition(this->mMainLayer->getPosition().x + Utils::randomf(0, 1) * this->mShakeIntensity * sentitX, this->mMainLayer->getPosition().y + Utils::randomf(0, 1) * this->mShakeIntensity * sentitY);
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