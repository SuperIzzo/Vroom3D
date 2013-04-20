#ifndef __VROOM_TEXMAP_VOLUME_RENDERER_NODE_H__
#define __VROOM_TEXMAP_VOLUME_RENDERER_NODE_H__



//=================================================================
//	Inlude
//---------------------------------------
#include <Node.h>
#include <Texture3D.h>

#include <vector>


VROOM_BEGIN


//=================================================================
//	Class TexMapVolumeRendererNode
//---------------------------------------
class TexMapVolumeRendererNode : public Node
{
public:
	friend class TexMapVolumeRenderer;

	enum DebugFlags {
			DBG_DRAW_BBOX		= 0x0001,
			DBG_DRAW_SLICES		= 0x0002
	};

public:
	void					SetNumberOfSlices( UInt32 numSlices );
	UInt32					GetNumberOfSlices();

	void					SetSliceSpacingExponent( Real exponent ); 
	Real					GetSliceSpacingExponent();

	void					SetDebugFlags(UInt32 debugFlags);
	UInt32					GetDebugFlags();

	void					SetLighting( bool enable );
	bool					GetLighting();

	void					SetVolumeData( VolumeData *volume );

	Texture3DPtr			GetNormalMap( bool generate = false );

	char					showNorm;

protected:
							TexMapVolumeRendererNode();
	void					Draw(const Vector3 &cameraDir);

private:
	void					BindTexture();

	void					SetTransformMatrix();
	void					UnsetTransformMatrix();

	void					SetLightingMode(const Vector3 &cameraDir);
	void					UnsetLightingMode();

private:
	UInt32					mDebugFlags;
	Texture3D			  *	mTexture;
	Texture3DPtr			mNormalMap;

	UInt32					mNumSlices;
	Real					mSpacingExponent;

	bool					mLighting;
};


VROOM_END


#endif