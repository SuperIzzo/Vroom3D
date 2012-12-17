#ifndef __VROOM_COLOR_H__
#define __VROOM_COLOR_H__





//=================================================================
//	Inlude
//---------------------------------------
#include <Platform.h>


VROOM_BEGIN


//=================================================================
//	Class Color
//---------------------------------------
struct Color
{
	UInt8				red;
	UInt8				green;
	UInt8				blue;
	UInt8				alpha;

	// Constructors
						Color();
						Color(UInt8 r, UInt8 g, UInt8 b, UInt8 a=255);
};


VROOM_END


#endif
