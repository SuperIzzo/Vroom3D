#ifndef __VROOM_TEXMAP_VOLUME_RENDERER_H__
#define __VROOM_TEXMAP_VOLUME_RENDERER_H__





//=================================================================
//	Inlude
//---------------------------------------
#include <VolumeRenderer.h>
#include <Volume.h>


VROOM_BEGIN


//=================================================================
//	Class TexMapVolumeRenderer
//---------------------------------------
class TexMapVolumeRenderer : public VolumeRenderer
{
public:
	virtual Node *			CreateNode();
};


VROOM_END


#endif
