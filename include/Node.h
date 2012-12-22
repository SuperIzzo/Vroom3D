#ifndef __VROOM_NODE_H__
#define __VROOM_NODE_H__





//=================================================================
//	Inlude
//---------------------------------------
#include <AABB.h>
#include <Volume.h>


VROOM_BEGIN


//=================================================================
//	Class Node
//---------------------------------------
class Node
{
public:
							Node();

	virtual void			SetVolume( Volume *volume );
	virtual Volume		  *	GetVolume();

private:
	Volume				  * mVolume;
};


VROOM_END


#endif
