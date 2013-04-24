#ifndef __VROOM_TEXMAP_VOLUME_RENDERER_H__
#define __VROOM_TEXMAP_VOLUME_RENDERER_H__





//=================================================================
//	Inlude
//---------------------------------------
#include <ShaderProgram.h>
#include <Camera.h>
#include <list>


VROOM_BEGIN


//=================================================================
//	Forward Declarations
//---------------------------------------
class RenderNode;





//=================================================================
//	Class VolumeRenderer
//---------------------------------------
class VolumeRenderer
{
public:
							VolumeRenderer();
	virtual					~VolumeRenderer();

	virtual RenderNode *	GetRootNode();
	virtual void			Render();

	void					SetShaderProgram( ShaderProgramPtr shader );
	ShaderProgramPtr		GetShaderProgram();

	CameraPtr				GetCamera();					

private:
	void					SetupRenderingState();
	void					SetupLighting();
	void					SetupCamera();
	void					DrawNode( RenderNode *node );

private:	
	RenderNode			  * mRootNode;
	bool					mLightingEnabled;
	ShaderProgramPtr		mShaderProgram;
	CameraPtr				mCamera;
};


VROOM_END


#endif
