#ifndef __VROOM_VOLUME_RENDERER_H__
#define __VROOM_VOLUME_RENDERER_H__





//=================================================================
//	Inlude
//---------------------------------------
#include <Platform.h>


VROOM_BEGIN


//=================================================================
//	Forward Declarations
//---------------------------------------
class Node;




//=================================================================
//	Class VolumeRenderer
//---------------------------------------
class VolumeRenderer
{
public:
	virtual					~VolumeRenderer() {};

	virtual Node *			GetRootNode() = 0;
	virtual void			Render() = 0;
};


VROOM_END


#endif
