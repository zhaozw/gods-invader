#ifndef CONST_LAYER
#define CONST_LAYER

#include "Layer.h"

// ===========================================================
// Inner Classes
// ===========================================================

// ===========================================================
// Constants
// ===========================================================

// ===========================================================
// Fields
// ===========================================================

// ===========================================================
// Constructors
// ===========================================================

Layer::Layer() :
	CCLayerColor()
	{
		this->init();
	}

// ===========================================================
// Methods
// ===========================================================

void Layer::setOpacity(GLubyte pOpacity)
{
	CCLayerColor::setOpacity(pOpacity);

	for(int i = 0; i < this->getChildren()->count(); i++)
	{
		((CCSprite*) this->getChildren()->objectAtIndex(i))->setOpacity(pOpacity);
	}
}

// ===========================================================
// Virtual Methods
// ===========================================================

void Layer::draw()
{
	glVertexAttribPointer(kCCVertexAttrib_Position, 2, GL_FLOAT, GL_FALSE, 0, m_pSquareVertices);

	CC_INCREMENT_GL_DRAWS(1);
}

#endif