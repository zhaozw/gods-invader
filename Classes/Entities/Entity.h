#ifndef CONST_ENTITY_H
#define CONST_ENTITY_H

#include "cocos2d.h"

#include "Texture.h"

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

		int* mFramesCoordinatesX;
		int* mFramesCoordinatesY;

		bool mWasTouched;
		bool mIsRegisterAsTouchable;

		float mAnimationScaleDownTime;
		float mAnimationScaleUpTime;

		float mAnimationScaleDownFactor;
		float mAnimationScaleUpFactor;

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
		
		/**
		 *
		 * Take care about careful position
		 *
		 */

		void setPosition(int pX, int pY);
		void setCenterPosition(int pX, int pY);

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

		Entity* create();

		void destroy();
		void destroy(bool pManage);

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

		virtual void onTouch(CCTouch* touch, CCEvent* event);

		virtual void update(float pDeltaTime);

		/**
		 *
		 * Let's take care about object copy
		 *
		 */

		virtual Entity* deepCopy();
};

#endif