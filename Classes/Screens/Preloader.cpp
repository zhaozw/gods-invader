#ifndef CONST_PRELOADER
#define CONST_PRELOADER

#include "Preloader.h"

// ===========================================================
// Init
// ===========================================================

// ===========================================================
// Constructors
// ===========================================================

Preloader::Preloader(void)
{
	this->mNumberOfLoadedSprites = 0;
	this->mNumberOfSprites = 21;

	this->mBackground = new Entity("start-preloader/preloader-bg.png");
	this->mBarBackground = new Entity("start-preloader/preloader-bar.png");
	this->mBar = new Entity("start-preloader/preloader-fill.png");

	this->mBackground->setCenterPosition(Options::CAMERA_CENTER_X, Options::CAMERA_CENTER_Y);
	this->mBarBackground->setCenterPosition(Options::CAMERA_CENTER_X, Options::CAMERA_CENTER_Y - Utils::coord(230));
	this->mBar->setCenterPosition(Options::CAMERA_CENTER_X, Options::CAMERA_CENTER_Y - Utils::coord(230));

	this->addChild(this->mBackground);
	this->addChild(this->mBarBackground);
	this->addChild(this->mBar);

	CCTextureCache::sharedTextureCache()->addImageAsync("base/base.png", this, callfuncO_selector(Preloader::loadingCallBack));
	CCTextureCache::sharedTextureCache()->addImageAsync("base/base-shadow.png", this, callfuncO_selector(Preloader::loadingCallBack));
	CCTextureCache::sharedTextureCache()->addImageAsync("base/cherry-shadow.png", this, callfuncO_selector(Preloader::loadingCallBack));
	CCTextureCache::sharedTextureCache()->addImageAsync("base/base.png", this, callfuncO_selector(Preloader::loadingCallBack));
	CCTextureCache::sharedTextureCache()->addImageAsync("main-character/bullets.png", this, callfuncO_selector(Preloader::loadingCallBack));
	CCTextureCache::sharedTextureCache()->addImageAsync("main-character/bullets-shadow.png", this, callfuncO_selector(Preloader::loadingCallBack));
	CCTextureCache::sharedTextureCache()->addImageAsync("main-character/gas-animation.png", this, callfuncO_selector(Preloader::loadingCallBack));
	CCTextureCache::sharedTextureCache()->addImageAsync("main-character/main-char-shadow-sprite.png", this, callfuncO_selector(Preloader::loadingCallBack));
	CCTextureCache::sharedTextureCache()->addImageAsync("main-character/main-char-sprite.png", this, callfuncO_selector(Preloader::loadingCallBack));
	CCTextureCache::sharedTextureCache()->addImageAsync("main-character/shoot-animation.png", this, callfuncO_selector(Preloader::loadingCallBack));
	CCTextureCache::sharedTextureCache()->addImageAsync("platform/platform-part-1.png", this, callfuncO_selector(Preloader::loadingCallBack));
	CCTextureCache::sharedTextureCache()->addImageAsync("platform/platform-part-2.png", this, callfuncO_selector(Preloader::loadingCallBack));
	CCTextureCache::sharedTextureCache()->addImageAsync("platform/clouds-sprite.png", this, callfuncO_selector(Preloader::loadingCallBack));
	CCTextureCache::sharedTextureCache()->addImageAsync("platform/clouds-shadow-sprite.png", this, callfuncO_selector(Preloader::loadingCallBack));
	CCTextureCache::sharedTextureCache()->addImageAsync("game-over/background.png", this, callfuncO_selector(Preloader::loadingCallBack));
	CCTextureCache::sharedTextureCache()->addImageAsync("game-passed/background.png", this, callfuncO_selector(Preloader::loadingCallBack));
	CCTextureCache::sharedTextureCache()->addImageAsync("main-menu/main-menu-background-part-1.png", this, callfuncO_selector(Preloader::loadingCallBack));
	CCTextureCache::sharedTextureCache()->addImageAsync("main-menu/main-menu-background-part-2.png", this, callfuncO_selector(Preloader::loadingCallBack));
	CCTextureCache::sharedTextureCache()->addImageAsync("main-menu/main-menu-cloud-sprite.png", this, callfuncO_selector(Preloader::loadingCallBack));
	CCTextureCache::sharedTextureCache()->addImageAsync("main-menu/main-menu-star-sprite.png", this, callfuncO_selector(Preloader::loadingCallBack));
	CCTextureCache::sharedTextureCache()->addImageAsync("game-over/play.png", this, callfuncO_selector(Preloader::loadingCallBack));
}

// ===========================================================
// Getters
// ===========================================================

// ===========================================================
// Setters
// ===========================================================

// ===========================================================
// Methods
// ===========================================================

void Preloader::loadingCallBack(CCObject *obj)
{
	++mNumberOfLoadedSprites;

	//this->mProgressTimer->setPercentage((int)(((float)mNumberOfLoadedSprites / mNumberOfSprites) * 100));

	if(mNumberOfLoadedSprites == mNumberOfSprites)
	{
		AppDelegate::screens = new ScreenManager();

		AppDelegate::screens->set(1.0f, 0);
	}
	else
	{
		
	}
}

// ===========================================================
// Virtual methods
// ===========================================================

void Preloader::update(float pDeltaTime)
{
	Screen::update(pDeltaTime);

	this->mBar->setRotation(this->mBar->getRotation() + 1);
}

#endif