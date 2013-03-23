#ifndef CONST_LEVEL_H
#define CONST_LEVEL_H

#include "cocos2d.h"
#include "AppDelegate.h"
#include "SimpleAudioEngine.h"

#include "Platform.h"
#include "Layer.h"
#include "Label.h"
#include "Hero.h"
#include "BaseEnemy.h"
#include "CastleEnemy.h"
#include "FollowEnemy.h"
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
	class HiddenButton : public Entity
	{
		public:
			HiddenButton(const char* pszFileName) :
				Entity(pszFileName)
				{
				}

			HiddenButton(const char* pszFileName, int pHorizontalFrameCount, int pVerticalFrameCount) :
				Entity(pszFileName, pHorizontalFrameCount, pVerticalFrameCount)
				{
				}

			void update(float pDeltaTime)
			{
				Entity::update(pDeltaTime);

				if(this->getY() < Utils::coord(100))
				{
					this->setVisible(false);
				}
				else
				{
					this->setVisible(true);
				}
			}
	};

	class SettingsButton : public Entity
	{
		private:
			Level* mParentScreen;

			Entity* mPic;

			bool mRotated;

		public:
			SettingsButton(Level* pParentScreen) :
				Entity("controls/settings-button.png")
				{
					this->mParentScreen = pParentScreen;

					this->mPic = new Entity("controls/settings-icon.png");

					this->mPic->setCenterPosition(this->getWidth() / 2, this->getHeight() / 2 + Utils::coord(5));

					this->addChild(this->mPic);

					this->mRotated = false;

					this->setRegisterAsTouchable(true);
				}

			void onTouch(CCTouch* touch, CCEvent* event)
			{
				if(this->mParentScreen->mButtonsHolder1->numberOfRunningActions() > 0) return;

				if(this->mRotated)
				{
					this->mPic->runAction(CCRotateTo::create(0.5f, 0.0f));
					this->mParentScreen->mCreditsButton->runAction(CCMoveTo::create(0.5f, ccp(Utils::coord(90), Utils::coord(0))));
					this->mParentScreen->mMusicButton->runAction(CCMoveTo::create(0.5f, ccp(Utils::coord(90), -Utils::coord(80))));
					this->mParentScreen->mSoundButton->runAction(CCMoveTo::create(0.5f, ccp(Utils::coord(90), -Utils::coord(170))));

					this->mParentScreen->mButtonsHolder1->runAction(CCMoveTo::create(0.4f, ccp(Utils::coord(90), Utils::coord(90))));
				}
				else
				{
					this->mPic->runAction(CCRotateTo::create(0.5f, 180.0f));
					this->mParentScreen->mCreditsButton->runAction(CCMoveTo::create(0.5f, ccp(Utils::coord(90), Utils::coord(400))));
					this->mParentScreen->mMusicButton->runAction(CCMoveTo::create(0.5f, ccp(Utils::coord(90), Utils::coord(310))));
					this->mParentScreen->mSoundButton->runAction(CCMoveTo::create(0.5f, ccp(Utils::coord(90), Utils::coord(220))));

					this->mParentScreen->mButtonsHolder1->runAction(CCMoveTo::create(0.5f, ccp(Utils::coord(90), Utils::coord(300))));
				}

				this->mRotated = !this->mRotated;
			}

			void setOpacity(GLubyte pOpacity)
			{
				for(int i = 0; i < this->getChildren()->count(); i++)
				{
					((CCSprite*) this->getChildren()->objectAtIndex(i))->setOpacity(pOpacity);
				}
			}
	};

	class SocialButton : public Entity
	{
		private:
			Level* mParentScreen;

			Entity* mPic;

			bool mRotated;

		public:
			SocialButton(Level* pParentScreen) :
				Entity("controls/settings-button.png")
				{
					this->mParentScreen = pParentScreen;

					this->mPic = new Entity("controls/social-icon.png");

					this->mPic->setCenterPosition(this->getWidth() / 2, this->getHeight() / 2);

					this->addChild(this->mPic);

					this->mRotated = false;

					this->setRegisterAsTouchable(true);
				}

			void onTouch(CCTouch* touch, CCEvent* event)
			{
				if(this->mParentScreen->mButtonsHolder2->numberOfRunningActions() > 0) return;

				if(this->mRotated)
				{
					this->mPic->runAction(CCRotateTo::create(0.5f, 0.0f));
					this->mParentScreen->mMoreGamesButton->runAction(CCMoveTo::create(0.5f, ccp(Options::CAMERA_WIDTH - Utils::coord(90), Utils::coord(0))));
					this->mParentScreen->mFacebookButton->runAction(CCMoveTo::create(0.5f, ccp(Options::CAMERA_WIDTH - Utils::coord(90), -Utils::coord(80))));
					this->mParentScreen->mTwitterButton->runAction(CCMoveTo::create(0.5f, ccp(Options::CAMERA_WIDTH - Utils::coord(90), -Utils::coord(170))));

					this->mParentScreen->mButtonsHolder2->runAction(CCMoveTo::create(0.4f, ccp(Options::CAMERA_WIDTH - Utils::coord(90), Utils::coord(90))));
				}
				else
				{
					this->mPic->runAction(CCRotateTo::create(0.5f, 90.0f));
					this->mParentScreen->mMoreGamesButton->runAction(CCMoveTo::create(0.5f, ccp(Options::CAMERA_WIDTH - Utils::coord(90), Utils::coord(400))));
					this->mParentScreen->mFacebookButton->runAction(CCMoveTo::create(0.5f, ccp(Options::CAMERA_WIDTH - Utils::coord(90), Utils::coord(310))));
					this->mParentScreen->mTwitterButton->runAction(CCMoveTo::create(0.5f, ccp(Options::CAMERA_WIDTH - Utils::coord(90), Utils::coord(220))));

					this->mParentScreen->mButtonsHolder2->runAction(CCMoveTo::create(0.5f, ccp(Options::CAMERA_WIDTH - Utils::coord(90), Utils::coord(300))));
				}

				this->mRotated = !this->mRotated;
			}

			void setOpacity(GLubyte pOpacity)
			{
				for(int i = 0; i < this->getChildren()->count(); i++)
				{
					((CCSprite*) this->getChildren()->objectAtIndex(i))->setOpacity(pOpacity);
				}
			}
	};
	
	class CreditsButton : public HiddenButton
	{
		private:

		public:
			CreditsButton() :
				HiddenButton("controls/context-credits-button.png")
				{
					this->setRegisterAsTouchable(true);
				}

			void onTouch(CCTouch* touch, CCEvent* event)
			{
				
			}
	};
	
	class MusicButton : public HiddenButton
	{
		private:

		public:
			MusicButton() :
				HiddenButton("controls/music-context-button.png", 1, 2)
				{
					this->setRegisterAsTouchable(true);
				}

			void onTouch(CCTouch* touch, CCEvent* event)
			{
				Options::MUSIC_ENABLE = !Options::MUSIC_ENABLE;

				this->setCurrentFrameIndex(Options::MUSIC_ENABLE ? 0 : 1);
			}
	};
	
	class SoundButton : public HiddenButton
	{
		private:

		public:
			SoundButton() :
				HiddenButton("controls/sound-context-button.png", 1, 2)
				{
					this->setRegisterAsTouchable(true);
				}

			void onTouch(CCTouch* touch, CCEvent* event)
			{
				Options::SOUND_ENABLE = !Options::SOUND_ENABLE;

				this->setCurrentFrameIndex(Options::SOUND_ENABLE ? 0 : 1);
			}
	};
	
	class MoreGamesButton : public HiddenButton
	{
		private:

		public:
			MoreGamesButton() :
				HiddenButton("controls/context-moregames-button.png")
				{
					this->setRegisterAsTouchable(true);
				}

			void onTouch(CCTouch* touch, CCEvent* event)
			{
			}
	};
	
	class FacebookButton : public HiddenButton
	{
		private:

		public:
			FacebookButton() :
				HiddenButton("controls/context-facebook-button.png")
				{
					this->setRegisterAsTouchable(true);
				}

			void onTouch(CCTouch* touch, CCEvent* event)
			{
			}
	};
	
	class TwitterButton : public HiddenButton
	{
		private:

		public:
			TwitterButton() :
				HiddenButton("controls/context-twitter-button.png")
				{
					this->setRegisterAsTouchable(true);
				}

			void onTouch(CCTouch* touch, CCEvent* event)
			{
			}
	};
	
	class PauseButton : public Entity
	{
		private:

		public:
			PauseButton() :
				Entity("controls/pause-button.png")
				{
					this->setOpacity(155.0f);

					this->setRegisterAsTouchable(true);
				}

			void onTouch(CCTouch* touch, CCEvent* event)
			{
			}
	};

	class PlayButton : public Entity
	{
		private:
			Level* mParentScreen;

		public:
			PlayButton(Level* pParentScreen) :
				Entity("labels/start.png")
				{
					this->mParentScreen = pParentScreen;

					this->setRegisterAsTouchable(true);
				}

			void onTouch(CCTouch* touch, CCEvent* event)
			{
				this->mParentScreen->runMainMenuanimation();
			}
	};

	class ButtonHolder : public Entity
	{
		int i;
		public:
			ButtonHolder(const char* pszFileName) :
				Entity(pszFileName)
				{
				}

			void update(float pDeltaTime)
			{
				Entity::update(pDeltaTime);

				i = this->getTexture()->getContentSize().height - (Utils::coord(300) - this->getCenterY());

				CCRect textureRectanle = CCRect(0, 0, this->getTexture()->getContentSize().width, i);

				this->setTextureRect(textureRectanle);
			}
	};

	class JumpButton : public Entity
	{
		private:
			Level* mParentClass;

		public:
			JumpButton(Level* pParentClass) :
				Entity("controls/jump.png")
				{
					this->mParentClass = pParentClass;

					this->setRegisterAsTouchable(true);
				}


			bool ccTouchBegan(CCTouch* touch, CCEvent* event)
			{
				if(Entity::ccTouchBegan(touch, event))
				{
					this->mParentClass->mHeroMustJump = true;
				}

				return Entity::ccTouchBegan(touch, event);
			}

			void ccTouchEnded(CCTouch* touch, CCEvent* event)
			{
				this->mParentClass->mHeroMustJump = false;
			}
	};

	private:
		float a;
		
		SettingsButton* mSettingsButton;
		SocialButton* mSocialButton;

		CreditsButton* mCreditsButton;

		MusicButton* mMusicButton;
		SoundButton* mSoundButton;

		MoreGamesButton* mMoreGamesButton;
		FacebookButton* mFacebookButton;
		TwitterButton* mTwitterButton;

		ButtonHolder* mButtonsHolder1;
		ButtonHolder* mButtonsHolder2;

		PauseButton* mPauseButton;

		static int LEVEL;

		bool mHeroMustJump;

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
		EntityManager* mEnemyBullets;
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

		Label* mLowHealthLabel;
		Label* mPrepareForBattleLabel;
		Label* mLevelClearedLabel;
		Label* mLevelNumberLabel;

		JumpButton* mJumpButton;
		
		Entity* mPlayButton;

		bool mShaking;

		float mShakeDuration;
		float mShakeDurationElapsed;
		float mShakeIntensity;

		bool mIsGameRunning;
		bool mIsMainMenu;
		bool mIsMainMenuAnimationRunning;

		Layer* mControlLayer;
		Layer* mStaticLayer;
		Layer* mMainLayer;

		float mSmallCubicGenerationTime;
		float mSmallCubicGenerationTimeElapsed;

		float mLastLowHealthLabelShowedTime;

		bool mLevelShouldStart;
		float mLevelStartTime;

	public:
		Level(void);

		void restart();
		void startLevel();

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