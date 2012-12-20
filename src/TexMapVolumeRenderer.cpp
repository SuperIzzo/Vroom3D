//=================================================================
//	Inlude
//---------------------------------------
#include "TexMapVolumeRenderer.h"
#include "TexMapVolumeRendererNode.h"


VROOM_BEGIN


//=================================================================
//	TexMapVolumeRenderer::CreateNode
//---------------------------------------
Node * TexMapVolumeRenderer::CreateNode()
{
	return new TexMapVolumeRendererNode();
}


VROOM_END

