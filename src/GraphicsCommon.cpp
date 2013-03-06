//=================================================================
//	Inlude
//---------------------------------------
#include "GraphicsCommon.h"


VROOM_BEGIN


//=================================================================
//	InitGraphicsOnce
//---------------------------------------
bool InitGraphicsCoreOnce()
{
	static bool isInitialized = false;
	if( !isInitialized )
	{
		GLenum glewErr= glewInit();

		if( glewErr == GLEW_OK )
		{
			isInitialized = true;			
		}
	}
	
	return isInitialized;
}


VROOM_END