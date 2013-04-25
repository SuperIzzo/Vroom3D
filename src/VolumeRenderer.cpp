//=================================================================
//	Inlude
//---------------------------------------
#include "VolumeRenderer.h"
#include "RenderNode.h"
#include "GraphicsCommon.h"
#include "AABB.h"

#include <iostream>


VROOM_BEGIN


//=================================================================
//	VolumeRenderer::VolumeRenderer
//---------------------------------------
VolumeRenderer::VolumeRenderer() :
	mRootNode(0),
	mLightingEnabled(0)
{
	mCamera = new Camera();
}





//=================================================================
//	VolumeRenderer::~VolumeRenderer
//---------------------------------------
VolumeRenderer::~VolumeRenderer()
{
	delete mRootNode;
}





//=================================================================
//	VolumeRenderer::GetRootNode
//---------------------------------------
RenderNode * VolumeRenderer::GetRootNode()
{
	if( !mRootNode )
	{
		mRootNode = new RenderNode();
	}

	return mRootNode;
}





//=================================================================
//	VolumeRenderer::GetCamera
//---------------------------------------
CameraPtr VolumeRenderer::GetCamera()
{
	return mCamera;
}





//=================================================================
//	VolumeRenderer::SetupRenderingState
//---------------------------------------
void VolumeRenderer::SetupRenderingState()
{
	glEnable( GL_BLEND );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
	
	glEnable( GL_DEPTH_TEST );
}






//=================================================================
//	VolumeRenderer::SetupLighting
//---------------------------------------
void VolumeRenderer::SetupLighting()
{
	if( mShaderProgram )
	{		
		mShaderProgram->Use();

		ShaderUniform tex1 = mShaderProgram->GetUniform( "texture1" );

		if( tex1.IsValid() )
		{
			tex1.SetInt( 0 );
		}
		else
		{
			std::cerr << "Shader uniform 'texture1' not found!" << std::endl;
		}


		ShaderUniform tex2 = mShaderProgram->GetUniform( "texture2" );

		if( tex2.IsValid() )
		{
			tex2.SetInt( 1 );
		}
		else
		{
			std::cerr << "Shader uniform 'texture2' not found!" << std::endl;
		}

		extern Eigen::Vector4f lightPos;


		ShaderUniform l = mShaderProgram->GetUniform( "l" );
		l.SetVec3Float( lightPos.x(), lightPos.y(), lightPos.z() );


		Vector3 cameraDir = mCamera->GetForward();

		ShaderUniform h = mShaderProgram->GetUniform( "h" );
		h.SetVec3Float( cameraDir.x(), cameraDir.y(), cameraDir.z() );		
	}
}





//=================================================================
//	VolumeRenderer::SetupCamera
//---------------------------------------
void VolumeRenderer::SetupCamera()
{
	ProjectiveTransform proj = mCamera->GetProjection();
	AffineTransform		view = mCamera->GetView();



	// Do view transformations here...
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf( proj.data() );


	// Set the view matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf( view.data() );
}





//=================================================================
//	VolumeRenderer::DrawNode
//---------------------------------------
void VolumeRenderer::DrawNode( RenderNode *node )
{
	node->Draw( mCamera->GetForward() );
}





//=================================================================
//	VolumeRenderer::Render
//---------------------------------------
void VolumeRenderer::Render()
{
	// Setup the rendering state
	SetupRenderingState();

	// Setup camera
	SetupCamera();

	// Illuminate the scene
	SetupLighting();

	// Draw nodes
	DrawNode( mRootNode );	
}



VROOM_END

