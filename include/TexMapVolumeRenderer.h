#ifndef __VROOM_TEXMAP_VOLUME_RENDERER_H__
#define __VROOM_TEXMAP_VOLUME_RENDERER_H__





//=================================================================
//	Inlude
//---------------------------------------
#include <VolumeRenderer.h>
#include <Volume.h>
#include <list>


VROOM_BEGIN


//=================================================================
//	Forward Declarations
//---------------------------------------
class TexMapVolumeRendererNode;





//=================================================================
//	Class TexMapVolumeRenderer
//---------------------------------------
class TexMapVolumeRenderer : public VolumeRenderer
{
public:
							TexMapVolumeRenderer();
	virtual					~TexMapVolumeRenderer();

	virtual Node *			GetRootNode();
	virtual void			Render();

private:
	void					SetupRenderingState();

private:
	typedef TexMapVolumeRendererNode NodeType;

	NodeType			  * mRootNode;
};


VROOM_END


#endif
