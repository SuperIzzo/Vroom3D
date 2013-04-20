#ifndef __VROOM_TEXMAP_VOLUME_RENDERER_H__
#define __VROOM_TEXMAP_VOLUME_RENDERER_H__





//=================================================================
//	Inlude
//---------------------------------------
#include <VolumeRenderer.h>
#include <ShaderProgram.h>
#include <Camera.h>
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

	void					SetShaderProgram( ShaderProgramPtr shader );
	ShaderProgramPtr		GetShaderProgram();

	CameraPtr				GetCamera();					

private:
	typedef TexMapVolumeRendererNode NodeType;

	void					SetupRenderingState();
	void					SetupLighting();
	void					SetupCamera();
	void					RenderNode( NodeType *node );

private:	
	NodeType			  * mRootNode;
	bool					mLightingEnabled;
	ShaderProgramPtr		mShaderProgram;
	CameraPtr				mCamera;
};


VROOM_END


#endif
