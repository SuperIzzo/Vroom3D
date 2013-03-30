//=================================================================
// Include
//---------------------------------------
#include "GraphicsFixture.h"

#include <SFML/Window/Context.hpp>





//=================================================================
//	GraphicsFixture::GraphicsFixture
//---------------------------------------
GraphicsFixture::GraphicsFixture()
{
	InitGraphicsTestingOnce();
}





//=================================================================
//	GraphicsFixture::InitGraphicsTestingOnce
//---------------------------------------
void GraphicsFixture::InitGraphicsTestingOnce()
{
	// Create a dummy OpenGL context
	static sf::Context theContext;
}