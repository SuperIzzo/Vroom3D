//=================================================================
//	Inlude
//---------------------------------------
#include "Color.h"


VROOM_BEGIN


//=================================================================
//	Color::Color
//---------------------------------------
Color::Color() :
	red(0),
	green(0),
	blue(0),
	alpha(0)
{
}





//=================================================================
//	Color::Color
//---------------------------------------
Color::Color( UInt8 r, UInt8 g, UInt8 b, UInt8 a) :
	red(r),
	green(g),
	blue(b),
	alpha(a)
{
}





//=================================================================
//	Color::operator==
//---------------------------------------
bool Color::operator==(const Color &other) const
{
	return(
		this->red == other.red
		&& this->green == other.green
		&& this->blue == other.blue
		&& this->alpha == other.alpha
		);
}





//=================================================================
//	Color::operator!=
//---------------------------------------
bool Color::operator!=(const Color &other) const
{
	return !((*this) == other);
}


VROOM_END
