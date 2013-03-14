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
	this->mNumberOfSprites = 14;

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
	CCTextureCache::sharedTextureCache()->addImageAsync("platform/sky.png", this, callfuncO_selector(Preloader::loadingCallBack));
	CCTextureCache::sharedTextureCache()->addImageAsync("platform/platform.png", this, callfuncO_selector(Preloader::loadingCallBack));
	CCTextureCache::sharedTextureCache()->addImageAsync("platform/clouds-sprite.png", this, callfuncO_selector(Preloader::loadingCallBack));
	CCTextureCache::sharedTextureCache()->addImageAsync("platform/clouds-shadow-sprite.png", this, callfuncO_selector(Preloader::loadingCallBack));
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
		CCTransitionScene *transition = CCTransitionFade::create(1.0f, new Level());

		CCDirector::sharedDirector()->setDepthTest(true);
		CCDirector::sharedDirector()->replaceScene(transition);
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