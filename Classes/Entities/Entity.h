#ifndef CONST_ENTITY_H
#define CONST_ENTITY_H

#include "cocos2d.h"

#include "Texture.h"
#include "Utils.h"

using namespace cocos2d;

class EntityManager;

class Entity : public CCSprite, public CCTargetedTouchDelegate
{
	protected:
		int mWidth;
		int mHeight;

		int mFrameWidth;
		int mFrameHeight;

		int mFramesCount;

		int mHorizontalFramesCount;
		int mVerticalFramesCount;

		int mCurrentFrameIndex;

		float* mFramesCoordinatesX;
		float* mFramesCoordinatesY;

		bool mWasTouched;
		bool mIsRegisterAsTouchable;
		bool mAnimationRunning;

		bool mIsShadow;

		float mAnimationTime;
		float mAnimationTimeElapsed;

		float mAnimationScaleDownTime;
		float mAnimationScaleUpTime;

		float mAnimationScaleDownFactor;
		float mAnimationScaleUpFactor;

		int mAnimationRepeatCount;

		int id; // For the entities which is childs of EntityManagers
		EntityManager* mEntityManager;

	private:
		void init(const char* pszFileName, int pHorizontalFramesCount, int pVerticalFramesCount, CCNode* pParent);

	public:
		Entity();
		Entity(const char* pszFileName);
		Entity(const char* pszFileName, int pHorizontalFramesCount, int pVerticalFramesCount);
		Entity(const char* pszFileName, CCNode* pParent);
		Entity(const char* pszFileName, int pHorizontalFramesCount, int pVerticalFramesCount, CCNode* pParent);
		
		float getWidth();
		float getHeight();

		void setIsShadow();

		bool isSetAsShadow();
		bool collideWith(Entity* pEntity);
		bool collideCoordinatesWith(float x, float y, Entity* pEntity);
		
		/**
		 *
		 * Take care about careful position
		 *
		 */

		void setPosition(float pX, float pY);
		void setCenterPosition(float pX, float pY);

		float getCenterPosition();
		float getX();
		float getY();
		float getCenterX();
		float getCenterY();

		/**
		 *
		 * Take care about EntityManager
		 *
		 */

		virtual Entity* create();

		virtual void destroy();
		virtual void destroy(bool pManage);

		void setEntityManager(EntityManager* pEntityManager);

		EntityManager* getEntityManager();

		bool hasEntityManager();

		void setEntityManagerId(int pId);

		int getEntityManagerId();

		/**
		 *
		 * Take care about animation
		 *
		 */

		int getCurrentFrameIndex();

		void setCurrentFrameIndex(int pIndex);

		void nextFrameIndex();

		void changeTexture(Texture* pTexture);

		void animate(float pAnimationTime);
		void animate(float pAnimationTime, int pRepeatCount);

		virtual void onAnimationEnd();

		/**
		 *
		 * Checing for touch detector
		 *
		 */

		void onEnter();

		void onExit();

		bool ccTouchBegan(CCTouch* touch, CCEvent* event);

		void ccTouchMoved(CCTouch* touch, CCEvent* event);

		void ccTouchEnded(CCTouch* touch, CCEvent* event);

		bool containsTouchLocation(CCTouch* touch);

		void setRegisterAsTouchable(bool pTouchable);

		virtual void update(float pDeltaTime);

		virtual void draw();
		
		virtual void onTouch(CCTouch* touch, CCEvent* event);

		/**
		 *
		 * Let's take care about object copy
		 *
		 */

		virtual Entity* deepCopy();
};

#endif