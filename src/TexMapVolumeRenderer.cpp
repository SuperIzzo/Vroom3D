//=================================================================
//	Inlude
//---------------------------------------
#include "TexMapVolumeRenderer.h"
#include "TexMapVolumeRendererNode.h"
#include "GraphicsCommon.h"
#include "AABB.h"

#include <iostream>


VROOM_BEGIN


//=================================================================
//	TexMapVolumeRenderer::TexMapVolumeRenderer
//---------------------------------------
TexMapVolumeRenderer::TexMapVolumeRenderer() :
	mRootNode(0),
	mLightingEnabled(0)
{
	mCamera = new Camera();
}





//=================================================================
//	TexMapVolumeRenderer::~TexMapVolumeRenderer
//---------------------------------------
TexMapVolumeRenderer::~TexMapVolumeRenderer()
{
	delete mRootNode;
}





//=================================================================
//	TexMapVolumeRenderer::GetRootNode
//---------------------------------------
Node * TexMapVolumeRenderer::GetRootNode()
{
	if( !mRootNode )
	{
		mRootNode = new TexMapVolumeRendererNode();
	}

	return mRootNode;
}





//=================================================================
//	TexMapVolumeRenderer::GetCamera
//---------------------------------------
CameraPtr TexMapVolumeRenderer::GetCamera()
{
	return mCamera;
}





//=================================================================
//	TexMapVolumeRenderer::SetupRenderingState
//---------------------------------------
void TexMapVolumeRenderer::SetupRenderingState()
{
	glEnable( GL_BLEND );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
	
	glEnable( GL_DEPTH_TEST );
}






//=================================================================
//	TexMapVolumeRenderer::SetupLighting
//---------------------------------------
void TexMapVolumeRenderer::SetupLighting()
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
//	TexMapVolumeRenderer::SetupCamera
//---------------------------------------
void TexMapVolumeRenderer::SetupCamera()
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
//	TexMapVolumeRenderer::RenderNode
//---------------------------------------
void TexMapVolumeRenderer::RenderNode( NodeType *node )
{
	node->Draw( mCamera->GetForward() );
}





//=================================================================
//	TexMapVolumeRenderer::Render
//---------------------------------------
void TexMapVolumeRenderer::Render()
{
	// Setup the rendering state
	SetupRenderingState();

	// Setup camera
	SetupCamera();

	// Illuminate the scene
	SetupLighting();

	// Draw nodes
	RenderNode( mRootNode );	
}



VROOM_END

