#include "Volume.h"

#include <SFML/Graphics.hpp>



Volume::Volume()
	: data(0)
{
}



Volume::~Volume()
{
	delete[] data;
}



void Volume::LoadFromXZImage( const char * imgFile, int wid )
{
	sf::Image the3DImage;
	the3DImage.loadFromFile( imgFile );

	int width	= width;
	int height	= the3DImage.getSize().y;
	int depth	= the3DImage.getSize().x / width;
}