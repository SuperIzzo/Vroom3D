#ifndef __VROOM_GRAPHICSHARDWAREEXCEPTION_H__
#define __VROOM_GRAPHICSHARDWAREEXCEPTION_H__



//=================================================================
//	Inlude
//---------------------------------------
#include <Platform.h>


VROOM_BEGIN


//=================================================================
//	struct GraphicsHardwareException
//---------------------------------------
struct GraphicsHardwareException
{
							GraphicsHardwareException( String msg );
	String					GetMsg() const;

private:
	String					mMsg;
};





//=================================================================
//	GraphicsHardwareException::GraphicsHardwareException
//---------------------------------------
inline GraphicsHardwareException::GraphicsHardwareException( String msg ) :
	mMsg( msg )
{
}





//=================================================================
//	GraphicsHardwareException::GetMessage
//---------------------------------------
inline String GraphicsHardwareException::GetMsg() const
{
	return mMsg;
}


VROOM_END


#endif