/*ZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZ*\
Z|                                                                           |Z
Z|  Copyright (c) 2013   Hristoz S. Stefanov                                 |Z
Z|                                                                           |Z
Z|  Permission is hereby granted, free of charge, to any person              |Z
Z|  obtaining a copy of this software and associated documentation files     |Z
Z|  (the "Software"), to deal in the Software without restriction,           |Z
Z|  including without limitation the rights to use, copy, modify, merge,     |Z
Z|  publish, distribute, sublicense, and/or sell copies of the Software,     |Z
Z|  and to permit persons to whom the Software is furnished to do so,        |Z
Z|  subject to the following conditions:                                     |Z
Z|                                                                           |Z
Z|  The above copyright notice and this permission notice shall be included  |Z
Z|  in all copies or substantial portions of the Software.                   |Z
Z|                                                                           |Z
Z|  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS  |Z
Z|  OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF               |Z
Z|  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.   |Z
Z|  IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY     |Z
Z|  CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,     |Z
Z|  TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE        |Z
Z|  SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                   |Z
Z|                                                                           |Z
\*ZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZ*/


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
	mLightingEnabled(0)
{
	mCamera = new Camera();
}





//=================================================================
//	VolumeRenderer::~VolumeRenderer
//---------------------------------------
VolumeRenderer::~VolumeRenderer()
{

}





//=================================================================
//	VolumeRenderer::CreateNode
//---------------------------------------
RenderNodePtr VolumeRenderer::CreateNode(const String &name)
{
	RenderNodePtr newNode= 0;

	NodeMap::iterator foundNode = mNodes.find(name);
	if( foundNode == mNodes.end() )
	{
		newNode = new RenderNode();
		mNodes[name] = newNode;
	}

	return newNode;
}





//=================================================================
//	VolumeRenderer::RemoveNode
//---------------------------------------
void VolumeRenderer::RemoveNode(const String &name)
{
	NodeMap::iterator foundNode = mNodes.find(name);
	if( foundNode != mNodes.end() )
	{
		mNodes.erase(foundNode);
	}
}





//=================================================================
//	VolumeRenderer::GetNode
//---------------------------------------
RenderNodePtr VolumeRenderer::GetNode(const String &name)
{
	RenderNodePtr theNode= 0;

	NodeMap::iterator foundNode = mNodes.find(name);
	if( foundNode != mNodes.end() )
	{
		theNode = foundNode->second;
	}

	return theNode;
}





//=================================================================
//	VolumeRenderer::GetCamera
//---------------------------------------
CameraPtr VolumeRenderer::GetCamera()
{
	return mCamera;
}







//=================================================================
//	VolumeRenderer::SetShaderProgram
//---------------------------------------
void VolumeRenderer::SetShaderProgram( ShaderProgramPtr shader )
{
	mShaderProgram = shader;
}





//=================================================================
//	VolumeRenderer::GetShaderProgram
//---------------------------------------
ShaderProgramPtr VolumeRenderer::GetShaderProgram()
{
	return mShaderProgram;
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

		ShaderUniform volume = mShaderProgram->GetUniform( "volume" );

		if( volume.IsValid() )
		{
			volume.SetInt( 0 );
		}
		else
		{
			std::cerr << "Shader uniform 'volume' not found!" << std::endl;
		}


		ShaderUniform normalMap = mShaderProgram->GetUniform( "normalMap" );

		if( normalMap.IsValid() )
		{
			normalMap.SetInt( 1 );
		}
		else
		{
			std::cerr << "Shader uniform 'normalMap' not found!" << std::endl;
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
//	VolumeRenderer::DebugDrawNode
//---------------------------------------
void VolumeRenderer::DebugDrawNode( RenderNode *node )
{
	node->DrawDebugGeometry( mCamera->GetForward() );
}





//=================================================================
//	VolumeRenderer::DrawNode
//---------------------------------------
void VolumeRenderer::DrawNode( RenderNode *node )
{
	ShaderUniform shadingModel = mShaderProgram->GetUniform( "shadingModel" );
	shadingModel.SetInt( node->GetShadingModel() );

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


	mShaderProgram->Unuse();


	// Draw debug geometry
	NodeMap::iterator nodeIter = mNodes.begin();
	for( ; nodeIter != mNodes.end(); nodeIter++ )
	{
		DebugDrawNode( nodeIter->second );
	}


	// Illuminate the scene
	SetupLighting();
	

	// Draw nodes
	nodeIter = mNodes.begin();
	for( ; nodeIter != mNodes.end(); nodeIter++ )
	{		
		DrawNode( nodeIter->second );
	}
}



VROOM_END

