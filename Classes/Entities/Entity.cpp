#ifndef CONST_ENTITY
#define CONST_ENTITY

#include "Entity.h"
#include "EntityManager.h"

void Entity::constructor(const char* pszFileName, int pHorizontalFramesCount, int pVerticalFramesCount, CCNode* pParent)
{
	this->initWithFile(pszFileName);

	if(pParent)
	{
		pParent->addChild(this);
	}

	this->mTextureFileName = pszFileName;

	this->mWidth  = this->getTextureRect().size.width;
	this->mHeight = this->getTextureRect().size.height;

	this->mFrameWidth = this->mWidth / pHorizontalFramesCount;
	this->mFrameHeight = this->mHeight / pVerticalFramesCount; 

	this->mFramesCount = pHorizontalFramesCount * pVerticalFramesCount;

	this->mHorizontalFramesCount = pHorizontalFramesCount;
	this->mVerticalFramesCount   = pVerticalFramesCount;

	this->mWasTouched = false;

	this->mIsShadow = false;
	this->mIgnoreSorting = false;
	this->mIsCollidable = false;

	this->mZ = Options::MIN_Z;

	this->setAnchorPoint(ccp(0.5f, 0.5f));

	this->mShadow = NULL;
	this->mEntityManager = NULL;

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

	this->mAnimationStartTimeout = 0;

	this->mPauseBeforeNewAnimationCircleTime = 0;
	this->mPauseBeforeNewAnimationCircleTimeElapsed = 0;

	this->mAnimationRunning = false;

	this->mAnimationScaleDownTime = 0.2;
	this->mAnimationScaleUpTime = 0.2;

	this->mAnimationScaleDownFactor = 0.8;
	this->mAnimationScaleUpFactor = 1.0;

	this->mIsRegisterAsTouchable = false;

	this->mAnimationRepeatCount = -1;

	this->mAnimationStartFrame = -1;
	this->mAnimationFinishFrame = -1;

	this->mAnimationFramesElapsed = 0;

	this->mIsAnimationReverse = false;
	this->mIsAnimationReverseNeed = false;

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

void Entity::setAsCollidable()
{
	this->mIsCollidable = true;
}

/**
 *
 * Take care about careful position
 *
 */

void Entity::setPosition(float pX, float pY)
{
    CCSprite::setPosition(ccp(pX - this->getWidth() / 2, pY + this->getHeight() / 2 + this->mZ));
}

void Entity::setCenterPosition(float pX, float pY)
{
    CCSprite::setPosition(ccp(pX, pY + this->mZ));
}

void Entity::setX(float pX)
{

}

void Entity::setY(float pY)
{
	
}

void Entity::setZ(float pZ)
{
	CCAssert(pZ < Options::MIN_Z, "Z coordinate cannot be < MIN_Z"); // TODO: Don't work?

	if(this->mShadow != NULL)
	{
		this->mShadow->setScale(1.0f - this->mZ / Options::MAX_Z);
	}

	this->mZ = pZ;
}

void Entity::addZ(float pZ)
{
	if(this->mZ - pZ >= Options::MAX_Z) return;

	this->setZ(this->mZ + pZ);

	this->setCenterPosition(this->getCenterX(), this->getCenterY() + pZ);
}

void Entity::removeZ(float pZ)
{
	if(this->mZ - pZ <= Options::MIN_Z)
	{
		this->mZ = Options::MIN_Z;

		return;
	}

	this->setZ(this->mZ - pZ);

	this->setCenterPosition(this->getCenterX(), this->getCenterY() - pZ);
}

float Entity::getCenterPosition()
{
	return 0; // TODO: Write this method
}

float Entity::getX()
{
	return this->getPosition().x - this->getWidth() / 2;
}

float Entity::getY()
{
	return this->getPosition().y + this->getHeight() / 2;
}

float Entity::getZ()
{
	return this->mZ;
}

float Entity::getCenterX()
{
	if(this->mIsShadow)
	{
		return ((Entity*) this->getParent())->getX() + this->getPosition().x;
	}

	return this->getPosition().x;
}

float Entity::getCenterY()
{
	if(this->mIsShadow)
	{
		return ((Entity*) this->getParent())->getY() - this->getPosition().y - this->mZ;
	}

	return this->getPosition().y - this->mZ;
}

bool Entity::isSetAsShadow()
{
	return this->mIsShadow;
}

bool Entity::isSetAsCollidable()
{
	return this->mIsCollidable;
}

bool Entity::collideWith(Entity* pEntity)
{
	if (this->getCenterX() - this->getWidth() / 2 < pEntity->getCenterX() + pEntity->getWidth() / 2 &&
		this->getCenterX() + this->getWidth() / 2 > pEntity->getCenterX() - pEntity->getWidth() / 2 &&
		this->getCenterY() - this->getHeight() / 2 < pEntity->getCenterY() + pEntity->getHeight() / 2 &&
		this->getCenterY() + this->getHeight() / 2 > pEntity->getCenterY() - pEntity->getHeight() / 2 &&
		this->getZ() <= pEntity->getZ() + pEntity->getHeight())
	{
		return true;
	}

	return false;
}

bool Entity::collideCoordinatesWith(float x, float y, Entity* pEntity)
{
	if (x - this->getWidth() / 2 < pEntity->getCenterX() + pEntity->getWidth() / 2 &&
		x + this->getWidth() / 2 > pEntity->getCenterX() - pEntity->getWidth() / 2 &&
		y - this->getHeight() / 2 < pEntity->getCenterY() + pEntity->getHeight() / 2 &&
		y + this->getHeight() / 2 > pEntity->getCenterY() - pEntity->getHeight() / 2)
	{
		return true;
	}

	return false;
}

bool Entity::collideWithCoordinates(float pX1, float pX2, float pY1, float pY2) // TODO: This method don't work well. Need to correct and override it in the Cloud class.
{
	if (this->getX() - this->getWidth() / 2 > pX1 - this->getWidth()*3 &&
		this->getX() + this->getWidth() / 2 < pX2 + this->getWidth()*3 &&
		this->getY() + this->getHeight() / 2 < pY1 + this->getHeight()*3 &&
		this->getY() - this->getHeight() / 2 > pY2 - this->getHeight()*3)
	{
		return true;
	}

	return false;
}

bool Entity::collideWith(Entity* pEntity, float pFactor)
{
	if (this->getCenterX() - (this->getWidth() / 2) * pFactor < pEntity->getCenterX() + (pEntity->getWidth() / 2) * pFactor &&
		this->getCenterX() + (this->getWidth() / 2) * pFactor > pEntity->getCenterX() - (pEntity->getWidth() / 2) * pFactor &&
		this->getCenterY() - (this->getHeight() / 2) * pFactor < pEntity->getCenterY() + (pEntity->getHeight() / 2) * pFactor &&
		this->getCenterY() + (this->getHeight() / 2) * pFactor > pEntity->getCenterY() - (pEntity->getHeight() / 2) * pFactor &&
		this->getZ() <= (pEntity->getZ() + pEntity->getHeight()) * pFactor)
	{
		return true;
	}

	return false;
}

bool Entity::circlesCollide(Entity* entity) {
	float x = this->getCenterX() - entity->getCenterX();
	float y = this->getCenterY() - entity->getCenterY();

	float d = this->getWidth() / 2 + entity->getWidth() / 2;

	return x * x + y * y < d * d;
}

bool Entity::circlesCollideWithCoordinates(float pX, float pY, float pRadius) {
	float x = this->getCenterX() - pX;
	float y = this->getCenterY() - pY;

	float d = MAX(this->getWidth(), this->getHeight()) / 2 + pRadius;

	return x * x + y * y < d * d;
}

bool Entity::circlesCollideCoordinatesWith(float pX1, float pY1, float pX2, float pY2, float pRadius) {
	float x = pX1 - pX2;
	float y = pY1 - pY2;

	float d = MAX(this->getWidth(), this->getHeight()) / 2 + pRadius;

	return x * x + y * y < d * d;
}

void Entity::setSpeed(float pSpeed)
{
	this->mSpeed = Utils::coord(pSpeed);
}

float Entity::getSpeed(float pDeltaTime)
{
	return this->mSpeed * pDeltaTime;
}

bool Entity::hasShadow()
{
	if(!this->mShadow)
	{
		return false;
	}

	return true;
}

Entity* Entity::getShadow()
{
	return this->mShadow;
}

void Entity::setIgnoreSorting(bool pIgnoreSorting)
{
	this->mIgnoreSorting = pIgnoreSorting;
}

bool Entity::isIgnoreSorting()
{
	return this->mIgnoreSorting;
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

bool Entity::destroy(bool pManage)
{
	this->setVisible(false);

	if(pManage)
	{
		if(this->hasEntityManager())
		{
			this->getEntityManager()->destroy(this->id);
		}
	}

	return false;
}

bool Entity::destroy()
{
	return this->destroy(true);
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

void Entity::previousFrameIndex()
{
	int potencialNextFrame = this->getCurrentFrameIndex() - 1;

	this->setCurrentFrameIndex(potencialNextFrame > 0 ? potencialNextFrame : 0);
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

	this->mFrameWidth = this->mWidth / pTexture->getHorizontalFramesCount();
	this->mFrameHeight = this->mHeight / pTexture->getVerticalFramesCount(); 

	this->mFramesCount = pTexture->getHorizontalFramesCount() * pTexture->getVerticalFramesCount();

	this->mHorizontalFramesCount = pTexture->getHorizontalFramesCount();
	this->mVerticalFramesCount   = pTexture->getVerticalFramesCount();

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
	this->mAnimationFramesElapsed = 0;

	this->mAnimationTimeElapsed = 0;
	this->mAnimationTime = pAnimationTime;

	this->mAnimationRunning = true;

	this->onAnimationStart();
}

void Entity::animate(float pAnimationTime, int pRepeatCount)
{
	this->mAnimationRepeatCount = pRepeatCount;

	this->animate(pAnimationTime);
}

void Entity::animate(float pAnimationTime, int pRepeatCount, bool pReverseNeed)
{
	this->mIsAnimationReverseNeed = pReverseNeed;

	this->animate(pAnimationTime, pRepeatCount);
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

void Entity::animate(float pAnimationTime, int pStartFrame, int pFinishFrame, int pRepeatCount)
{
	this->animate(pAnimationTime);

	this->mAnimationStartFrame = pStartFrame;
	this->mAnimationFinishFrame = pFinishFrame;

	this->mAnimationRepeatCount = pRepeatCount;

	this->setCurrentFrameIndex(pStartFrame);
}

void Entity::animate(float pAnimationTime, int pStartFrame, int pFinishFrame)
{
	this->animate(pAnimationTime, pStartFrame, pFinishFrame, -1);
}

void Entity::onAnimationStart()
{
}

void Entity::onAnimationEnd()
{
}

void Entity::onAnimationCircleEnd()
{
}

void Entity::setAnimationStartTimeout(float pSecodsTimeout)
{
	this->mAnimationStartTimeout = pSecodsTimeout;
}

void Entity::setStartFrame(int pStartFrame)
{
	this->mAnimationFinishFrame = (this->mAnimationFinishFrame - this->mAnimationStartFrame) + pStartFrame;
	this->mAnimationStartFrame = pStartFrame;
}

void Entity::setFinishFrame(int pFinishFrame)
{
	this->mAnimationFinishFrame = pFinishFrame;
}

bool Entity::isAnimationRunning()
{
	return this->mAnimationRunning;
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
	if(!this->containsTouchLocation(touch) || !this->isVisible() || !this->getParent()->isVisible())
	{
		return false;
	}

	if(Touchable::ccTouchBegan(touch, event))
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
	return CCRectMake(-this->mFrameWidth/ 2, -this->mFrameHeight / 2, this->mFrameWidth, this->mFrameHeight).containsPoint(this->convertTouchToNodeSpaceAR(touch));
}

/**
 *
 * Let's take care about object copy
 *
 */

Entity* Entity::deepCopy()
{
	return new Entity(this->mTextureFileName, this->mHorizontalFramesCount, this->mVerticalFramesCount);
}

void Entity::update(float pDeltaTime)
{
	if(!this->isVisible()) return;

	if(this->mAnimationStartTimeout >= 0)
	{
		this->mAnimationStartTimeout -= pDeltaTime;
	}
	else
	{
		if(this->mAnimationRunning && (this->mAnimationRepeatCount > 0 || this->mAnimationRepeatCount < 0))
		{
			this->mAnimationTimeElapsed += pDeltaTime;

			if(this->mAnimationTimeElapsed >= this->mAnimationTime)
			{
				this->mAnimationTimeElapsed -= this->mAnimationTime;

				if(this->mAnimationStartFrame == -1 && this->mAnimationFinishFrame == -1)
				{
					if(this->mIsAnimationReverse && this->getCurrentFrameIndex() == 0) // TODO: Add animation repeat counter.
					{
						this->mAnimationRunning = false;
						this->mIsAnimationReverse = false;

						this->mAnimationRunning = false;

						this->onAnimationEnd();
							
						return;
					}

					if(this->mAnimationRepeatCount > 0 && this->getCurrentFrameIndex() == this->mFramesCount - 1)
					{
						this->mAnimationRepeatCount--;

						if(this->mAnimationRepeatCount == 0)
						{
							if(this->mIsAnimationReverseNeed)
							{
								this->mAnimationRepeatCount++;

								this->mIsAnimationReverseNeed = false;
								this->mIsAnimationReverse = true;
						
								this->previousFrameIndex();

								return;
							}
							else
							{
								this->mAnimationRunning = false;

								this->onAnimationEnd();
							}
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

					if(this->mIsAnimationReverse)
					{
						this->previousFrameIndex();
					}
					else
					{
						this->nextFrameIndex();
					}
				}
				else
				{
					if(this->getCurrentFrameIndex() < this->mAnimationFinishFrame)
					{
						this->setCurrentFrameIndex(this->mAnimationStartFrame + this->mAnimationFramesElapsed + 1);

						this->mAnimationFramesElapsed++;
					}
					else
					{
						if(this->mAnimationRepeatCount > 0)
						{
							this->mAnimationRepeatCount--;

							this->mAnimationFramesElapsed = 0;

							if(this->mAnimationRepeatCount == 0)
							{
								this->mAnimationRunning = false;

								this->onAnimationEnd();
							}
						}
						else
						{
							this->mAnimationFramesElapsed = 0;

							this->setCurrentFrameIndex(this->mAnimationStartFrame);
						}
					}
				}
			}
		}
	}

	if(this->mShadow)
	{
		if(this->mShadow->getParent())
		{
			if(this->mShadow->getParent() != this)
			{
				this->mShadow->setCenterPosition(this->getCenterX(), this->getCenterY() - Utils::coord(60)); // I must transfer this to once call.
			}
		}
	}
	
	if(this->mIsCollidable)
	{
		if(this->circlesCollideCoordinatesWith(this->getCenterX(), this->getCenterY(), Options::CENTER_X, Options::CENTER_Y + Utils::coord(30), Utils::coord((60.0f))))
		{
			float radius = MAX(this->getWidth(), this->getHeight()) + Utils::coord(120.0f);

            float dx = (Options::CENTER_X - this->getCenterX()) * 2.0f;
            float dy = (Options::CENTER_Y + Utils::coord(30) - this->getCenterY()) * 2.0f;
            {
                float dist = sqrt(dx * dx + dy * dy);

                dx = Options::CENTER_X - (float) (dx / dist) * radius * 0.5f;
               	dy = Options::CENTER_Y + Utils::coord(30) - (float) (dy / dist) * radius * 0.5f;
            }

    		this->setCenterPosition(dx, dy);
		}
	}
}

void Entity::draw()
{
	CCSprite::draw();
}

#endif