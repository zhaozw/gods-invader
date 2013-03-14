#ifndef CONST_ENTITYMANAGER_H
#define CONST_ENTITYMANAGER_H

#include "cocos2d.h"

#include "Entity.h"

using namespace cocos2d;

class EntityManager : public CCArray
{
	protected:
		CCNode* mParent;

		int mLastElementNumber;
		int mCapacity;

		bool mIsSortY;

	private:
		void init(int pCreateCount, int pMaxCount, Entity* pEntity, CCNode* pScreen);

	public:
		EntityManager(int pCreateCount, Entity* pEntity);
		EntityManager(int pCreateCount, Entity* pEntity, CCNode* pScreen);
		EntityManager(int pCreateCount, int pMaxCount, Entity* pEntity, CCNode* pScreen);

		Entity* create();
		void destroy(int pIndex);

		void setParent(CCNode* pScreen);

		void changeTexture(Texture* pTexture);

		void disableSort();
		
		int getCount();
		int getCapacity();

		void clear();

		void sortChildrenByYPosition();
};

#endif