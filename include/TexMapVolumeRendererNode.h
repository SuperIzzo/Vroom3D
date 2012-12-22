#ifndef __VROOM_TEXMAP_VOLUME_RENDERER_NODE_H__
#define __VROOM_TEXMAP_VOLUME_RENDERER_NODE_H__





//=================================================================
//	Inlude
//---------------------------------------
#include <Node.h>
#include <Polygon.h>
#include <vector>


VROOM_BEGIN


//=================================================================
//	Class TexMapVolumeRendererNode
//---------------------------------------
class TexMapVolumeRendererNode : public Node
{
public:

private:
	std::vector<Polygon>	mSlices;
};


VROOM_END


#endif