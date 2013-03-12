#ifndef CONST_ENTITY
#define CONST_ENTITY

#include "Entity.h"
#include "EntityManager.h"

void Entity::constructor(const char* pszFileName, int pHorizontalFramesCount, int pVerticalFramesCount, CCNode* pParent)
{
	CCSize screenSize = CCEGLView::sharedOpenGLView()->getFrameSize();

	this->initWithFile(pszFileName);

	if(pParent)
	{
		pParent->addChild(this);
	}

	this->mWidth  = this->getTextureRect().size.width;
	this->mHeight = this->getTextureRect().size.height;

	this->mFrameWidth = this->mWidth / pHorizontalFramesCount;
	this->mFrameHeight = this->mHeight / pVerticalFramesCount; 

	this->mFramesCount = pHorizontalFramesCount * pVerticalFramesCount;

	this->mHorizontalFramesCount = pHorizontalFramesCount;
	this->mVerticalFramesCount   = pVerticalFramesCount;

	this->mWasTouched = false;

	this->mIsShadow = false;

	/**
	 *
	 * We must remember all coordinates of each frame
	 * for quick get x and y of it.
	 *
	 */

	this->mFramesCoordinatesX = new float[this->mFramesCount];
	this->mFramesCoordinatesY = new float[this->mFramesCount];

	int counter = 0;

	for(int i = 0; i < this->mVerticalFramesCount; i++)
	{
		for(int j = 0; j < this->mHorizontalFramesCount; j++, counter++)
		{
			this->mFramesCoordinatesX[counter] = j * (this->mWidth / this->mHorizontalFramesCount);
			this->mFramesCoordinatesY[counter] = i * (this->mHeight / this->mVerticalFramesCount);
		}
	}

	/**
	 *
	 * Setting zero frame
	 *
	 */

	this->setCurrentFrameIndex(0);

	/**
	 *
	 *
	 * Take care about an animations
	 *
	 */

	this->mAnimationTime = 0;
	this->mAnimationTimeElapsed = 0;

	this->mPauseBeforeNewAnimationCircleTime = 0;
	this->mPauseBeforeNewAnimationCircleTimeElapsed = 0;

	this->mAnimationRunning = false;

	this->mAnimationScaleDownTime = 0.2;
	this->mAnimationScaleUpTime = 0.2;

	this->mAnimationScaleDownFactor = 0.8;
	this->mAnimationScaleUpFactor = 1.0;

	this->mIsRegisterAsTouchable = false;

	this->mAnimationRepeatCount = -1;

	this->scheduleUpdate();

	this->retain();
	this->release();
}


Entity::Entity()
{
}

Entity::Entity(const char* pszFileName)
{
	this->constructor(pszFileName, 1, 1, NULL);
}

Entity::Entity(const char* pszFileName, int pHorizontalFramesCount, int pVerticalFramesCount)
{
	this->constructor(pszFileName, pHorizontalFramesCount, pVerticalFramesCount, NULL);
}

Entity::Entity(const char* pszFileName, CCNode* pParent)
{
	this->constructor(pszFileName, 1, 1, pParent);
}

Entity::Entity(const char* pszFileName, int pHorizontalFramesCount, int pVerticalFramesCount, CCNode* pParent)
{
	this->constructor(pszFileName, pHorizontalFramesCount, pVerticalFramesCount, pParent);
}


float Entity::getWidth()
{
	return this->getContentSize().width;
}

float Entity::getHeight()
{
	return this->getContentSize().height;
}

void Entity::setIsShadow()
{
	this->setOpacity(80);

	this->mIsShadow = true;
}	

/**
 *
 * Take care about careful position
 *
 */

void Entity::setPosition(float pX, float pY)
{
    CCSprite::setPosition(ccp(pX + this->mWidth / 2, pY - this->mHeight / 2));
}

void Entity::setCenterPosition(float pX, float pY)
{
    CCSprite::setPosition(ccp(pX, pY));
}


float Entity::getCenterPosition()
{
	return 0;
}

float Entity::getX()
{
	return this->getPosition().x;
}

float Entity::getY()
{
	return this->getPosition().y;
}

float Entity::getCenterX()
{
	return this->getPosition().x + this->getContentSize().width / 2;
}

float Entity::getCenterY()
{
	return this->getPosition().y + this->getContentSize().height / 2;
}

bool Entity::isSetAsShadow()
{
	return this->mIsShadow;
}

bool Entity::collideWith(Entity* pEntity)
{
	if (this->getX() - this->getWidth() / 2 < pEntity->getX() + pEntity->getWidth() / 2 &&
		this->getX() + this->getWidth() / 2 > pEntity->getX() - pEntity->getWidth() / 2 &&
		this->getY() - this->getHeight() / 2 < pEntity->getY() + pEntity->getHeight() / 2 &&
		this->getY() + this->getHeight() / 2 > pEntity->getY() - pEntity->getHeight() / 2)
	{
		return true;
	}

	return false;
}

bool Entity::collideCoordinatesWith(float x, float y, Entity* pEntity)
{
	if (x - this->getWidth() / 2 < pEntity->getX() + pEntity->getWidth() / 2 &&
		x + this->getWidth() / 2 > pEntity->getX() - pEntity->getWidth() / 2 &&
		y - this->getHeight() / 2 < pEntity->getY() + pEntity->getHeight() / 2 &&
		y + this->getHeight() / 2 > pEntity->getY() - pEntity->getHeight() / 2)
	{
		return true;
	}

	return false;
}

/**
 *
 * Take care about EntityManager
 *
 */

Entity* Entity::create()
{
	this->setVisible(true);

	return this;
}

void Entity::destroy(bool pManage)
{
	this->setVisible(false);

	if(pManage)
	{
		if(this->hasEntityManager())
		{
			this->getEntityManager()->destroy(this->id);
		}
	}
}

void Entity::destroy()
{
	this->destroy(true);
}

void Entity::setEntityManager(EntityManager* pEntityManager)
{
	this->mEntityManager = pEntityManager;
}

EntityManager* Entity::getEntityManager()
{
	return this->mEntityManager;
}

bool Entity::hasEntityManager()
{
	return this->mEntityManager != NULL;
}

void Entity::setEntityManagerId(int pId)
{
	this->id = pId;
}

int Entity::getEntityManagerId()
{
	return this->id;
}

/**
 *
 * Take care about animation
 *
 */

int Entity::getCurrentFrameIndex()
{
	return this->mCurrentFrameIndex;
}

void Entity::setCurrentFrameIndex(int pIndex)
{
	if(pIndex < this->mHorizontalFramesCount * this->mVerticalFramesCount && pIndex >= 0)
	{
		this->setTextureRect(CCRectMake(this->mFramesCoordinatesX[pIndex], this->mFramesCoordinatesY[pIndex], this->mWidth / this->mHorizontalFramesCount, this->mHeight / this->mVerticalFramesCount));

		this->mCurrentFrameIndex = pIndex;
	}
	else
	{
		this->setCurrentFrameIndex(0);
	}
}

void Entity::nextFrameIndex()
{
	int potencialNextFrame = this->getCurrentFrameIndex() + 1;

	this->setCurrentFrameIndex(potencialNextFrame > this->mFramesCount ? 0 : potencialNextFrame);
}

void Entity::changeTexture(Texture* pTexture)
{
	CCRect textureRectanle = CCRect(0, 0, pTexture->getTexture()->getContentSize().width, pTexture->getTexture()->getContentSize().height);

	this->setTexture(pTexture->getTexture());
	this->setTextureRect(textureRectanle);

	this->mWidth  = this->getTextureRect().size.width;
	this->mHeight = this->getTextureRect().size.height;

	this->mFrameWidth = this->mWidth / pTexture->mHorizontalFramesCount;
	this->mFrameHeight = this->mHeight / pTexture->mVerticalFramesCount; 

	this->mFramesCount = pTexture->mHorizontalFramesCount * pTexture->mVerticalFramesCount;

	this->mHorizontalFramesCount = pTexture->mHorizontalFramesCount;
	this->mVerticalFramesCount   = pTexture->mVerticalFramesCount;

	int counter = 0;

	for(int i = 0; i < this->mVerticalFramesCount; i++)
	{
		for(int j = 0; j < this->mHorizontalFramesCount; j++, counter++)
		{
			this->mFramesCoordinatesX[counter] = j * (this->mWidth / this->mHorizontalFramesCount);
			this->mFramesCoordinatesY[counter] = i * (this->mHeight / this->mVerticalFramesCount);
		}
	}

	this->setCurrentFrameIndex(0);
}

void Entity::animate(float pAnimationTime)
{
	this->mAnimationTime = pAnimationTime;

	this->mAnimationRunning = true;
}

void Entity::animate(float pAnimationTime, int pRepeatCount)
{
	this->mAnimationRepeatCount = pRepeatCount;

	this->animate(pAnimationTime);
}

void Entity::animate(float pAnimationTime, float pPauseBeforeNewAnimationCircleTime)
{
	this->mPauseBeforeNewAnimationCircleTime = pPauseBeforeNewAnimationCircleTime;

	this->animate(pAnimationTime);
}

void Entity::animate(float pAnimationTime, int pRepeatCount, float pPauseBeforeNewAnimationCircleTime)
{
	this->mPauseBeforeNewAnimationCircleTime = pPauseBeforeNewAnimationCircleTime;

	this->animate(pAnimationTime, pRepeatCount);
}

void Entity::onAnimationEnd()
{
}

void Entity::onAnimationCircleEnd()
{
	
}

/**
 *
 * Checing for touch detector
 *
 */

void Entity::onEnter()
{
	CCDirector* pDirector = CCDirector::sharedDirector();
	pDirector->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
	CCSprite::onEnter();
}

void Entity::onExit()
{
	CCDirector* pDirector = CCDirector::sharedDirector();
	pDirector->getTouchDispatcher()->removeDelegate(this);
	CCSprite::onExit();
}

bool Entity::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
	if(!this->mIsRegisterAsTouchable || !this->isVisible() || !this->getParent()->isVisible())
	{
		return false;
	}

	if(containsTouchLocation(touch))
	{
		this->mWasTouched = true;

		this->runAction(CCScaleTo::create(this->mAnimationScaleDownTime, this->mAnimationScaleDownFactor));

		return true;
	}

	return false;
}

void Entity::ccTouchMoved(CCTouch* touch, CCEvent* event)
{
	if(!containsTouchLocation(touch))
	{
		if(this->mWasTouched)
		{
		if(this->getScale() < this->mAnimationScaleUpFactor)
			{
				this->runAction(CCScaleTo::create(this->mAnimationScaleUpTime, this->mAnimationScaleUpFactor));

				this->mWasTouched = false;
			}
		}
	}
}

void Entity::ccTouchEnded(CCTouch* touch, CCEvent* event)
{
	if(this->mWasTouched)
	{
		this->onTouch(touch, event);

		this->runAction(CCScaleTo::create(this->mAnimationScaleUpTime, this->mAnimationScaleUpFactor));
	}

	this->mWasTouched = false;
}

bool Entity::containsTouchLocation(CCTouch* touch)
{
	return CCRectMake(-this->mFrameWidth/ 2, -this->mFrameHeight / 2, this->mFrameWidth, this->mFrameHeight).containsPoint(convertTouchToNodeSpaceAR(touch));
}

void Entity::setRegisterAsTouchable(bool pTouchable)
{
	this->mIsRegisterAsTouchable = pTouchable;
}

void Entity::onTouch(CCTouch* touch, CCEvent* event)
{
}

/**
 *
 * Let's take care about object copy
 *
 */

Entity* Entity::deepCopy()
{
	return this;
}

void Entity::update(float pDeltaTime)
{
	if(this->mAnimationRunning && (this->mAnimationRepeatCount > 0 || this->mAnimationRepeatCount < 0))
	{

		this->mAnimationTimeElapsed += pDeltaTime;

		if(this->mAnimationTimeElapsed >= this->mAnimationTime)
		{
			if(this->mAnimationRepeatCount > 0 && this->getCurrentFrameIndex() == this->mFramesCount - 1)
			{
				this->mAnimationRepeatCount--;

				if(this->mAnimationRepeatCount == 0)
				{
					this->mAnimationRunning = false;

					this->onAnimationEnd();
				}
			}

			if(this->getCurrentFrameIndex() == this->mFramesCount - 1)
			{
				this->onAnimationCircleEnd();

				if(this->mPauseBeforeNewAnimationCircleTime > 0)
				{
					this->mPauseBeforeNewAnimationCircleTimeElapsed += pDeltaTime;

					if(this->mPauseBeforeNewAnimationCircleTimeElapsed < this->mPauseBeforeNewAnimationCircleTime)
					{
						return;
					}
					else
					{
						this->mPauseBeforeNewAnimationCircleTimeElapsed = 0;
					}
				}
			}

			this->mAnimationTimeElapsed = 0;

			this->nextFrameIndex();
		}
	}
}

void Entity::draw()
{
  CCSprite::draw();
}

#endif