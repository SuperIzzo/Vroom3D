#ifndef __VROOM_SHAREDPOINTER_H__
#define __VROOM_SHAREDPOINTER_H__





//=================================================================
// Include
//---------------------------------------
#include <yasper.h>


VROOM_BEGIN


//=================================================================
// Class SharedPointer<T> : A generic definition of a shared pointer type
//---------------------------------------
template <typename T>
struct SharedPointer
{
	typedef yasper::ptr<T>		Type;
};


VROOM_END


#endif