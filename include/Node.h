#ifndef __VROOM_NODE_H__
#define __VROOM_NODE_H__





//=================================================================
//	Inlude
//---------------------------------------
#include <Platform.h>


VROOM_BEGIN


//=================================================================
//	Class Node
//---------------------------------------
class Node
{
public:
	virtual UInt32			GetTypeID() = 0;
};


VROOM_END


#endif
