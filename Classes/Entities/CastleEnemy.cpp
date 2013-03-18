#ifndef CONST_CASTLEENEMY
#define CONST_CASTLEENEMY

#include "CastleEnemy.h"

CastleEnemy::CastleEnemy(Hero* pHero) :
 BaseEnemy(pHero)
{
}

CastleEnemy::CastleEnemy(const char* pszFileName, int pHorizontalFramesCount, int pVerticalFramesCount, Hero* pHero) :
	BaseEnemy(pszFileName, pHorizontalFramesCount, pVerticalFramesCount, pHero)
	{
		
	}

CastleEnemy* CastleEnemy::deepCopy()
{
	return new CastleEnemy("stolen/alien1.png", 8, 1, this->mHero);
}

#endif