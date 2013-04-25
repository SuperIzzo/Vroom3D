//=================================================================
//	Inlude
//---------------------------------------
#include "RenderNode.h"

#include "AABB.h"
#include "ShaderProgram.h"
#include "NormalMapGenerator.h"

#include <Windows.h>
#include <gl/glew.h>
#include <gl/GL.h>
#include <gl/GLU.h>


#include <iostream>

VROOM_BEGIN


//=================================================================
//	DrawBox : utility function to draw a wireframe AABB
//---------------------------------------
static void DrawBox( const Vector3 &min, const Vector3 &max )
{
	glBegin( GL_LINES );
		glVertex3f( min.x(), min.y(),	min.z() );
		glVertex3f( max.x(), min.y(),	min.z() );

		glVertex3f( min.x(), min.y(),	min.z() );
		glVertex3f( min.x(), max.y(),	min.z() );

		glVertex3f( min.x(), min.y(),	min.z() );
		glVertex3f( min.x(), min.y(),	max.z() );


		glVertex3f( max.x(), min.y(),	min.z() );
		glVertex3f( max.x(), max.y(),	min.z() );

		glVertex3f( max.x(), min.y(),	min.z() );
		glVertex3f( max.x(), min.y(),	max.z() );


		glVertex3f( min.x(), max.y(),	min.z() );
		glVertex3f( max.x(), max.y(),	min.z() );

		glVertex3f( min.x(), max.y(),	min.z() );
		glVertex3f( min.x(), max.y(),	max.z() );


		glVertex3f( min.x(), min.y(),	max.z() );
		glVertex3f( max.x(), min.y(),	max.z() );

		glVertex3f( min.x(), min.y(),	max.z() );
		glVertex3f( min.x(), max.y(),	max.z() );


		glVertex3f( max.x(), max.y(),	max.z() );
		glVertex3f( max.x(), max.y(),	min.z() );

		glVertex3f( max.x(), max.y(),	max.z() );
		glVertex3f( max.x(), min.y(),	max.z() );

		glVertex3f( max.x(), max.y(),	max.z() );
		glVertex3f( min.x(), max.y(),	max.z() );
	glEnd();
}





//=================================================================
//	DrawPolygon : utility function to draw a wireframe polygon
//---------------------------------------
static void DrawPolygon( const Polygon &poly )
{
	int vertCount = poly.GetVertexCount();

	if( vertCount > 0 )
	{		
		Vector3 point1 = poly.GetVertex( vertCount-1 );
		Vector3 point2;

		glBegin( GL_LINES );

		for( int i=0; i< vertCount; i++ )
		{
			point2 = poly.GetVertex( i );

			glVertex3f( point1.x(), point1.y(),	point1.z() );
			glVertex3f( point2.x(), point2.y(),	point2.z() );

			point1 = point2;
		}

		glEnd();
	}
}





//=================================================================
//	DrawPolygonFill : utility function to draw a filled polygon
//---------------------------------------
static void DrawPolygonFill( const Polygon &poly )
{
	// The following paramenters are added to reduce the bleeding effect
	// when the interpolation mode is set to linear 
	// these inset the texture, so that it the border interp does not occur
	const float BORDER_INSET = 0.01;
	const float CONTENT_SCALE = 1-BORDER_INSET*2;

	int vertCount = poly.GetVertexCount();

	if( vertCount > 0 )
	{		
		glBegin( GL_TRIANGLE_FAN );

		for( int i=0; i< vertCount; i++ )
		{
			Vector3 point = poly.GetVertex( i );

			glTexCoord3f( 
				point.x()*CONTENT_SCALE + BORDER_INSET,
				point.y()*CONTENT_SCALE + BORDER_INSET,	
				point.z()*CONTENT_SCALE + BORDER_INSET );
			glVertex3f(   point.x(), point.y(),	point.z() );
		}

		glEnd();
	}
}





//=================================================================
//	RenderNode::RenderNode
//---------------------------------------
RenderNode::RenderNode() :
	mTexture( 0 ),
	mNumSlices( 200 ),
	mSpacingExponent( 1 ),
	mDebugFlags( 0 ),
	mNormalMap( 0 ),
	mLighting( 0 )
{
	mTransform =  Matrix4::Identity();
}





//=================================================================
//	RenderNode::BindTexture
//---------------------------------------
void RenderNode::BindTexture()
{
	if( mTexture )
	{
		mTexture->Bind(0);
	}
}





//=================================================================
//	RenderNode::SetNumberOfSlices
//---------------------------------------
void RenderNode::SetNumberOfSlices( UInt32 numSlices )
{
	mNumSlices = numSlices;
}





//=================================================================
//	RenderNode::GetNumberOfSlices
//---------------------------------------
UInt32 RenderNode::GetNumberOfSlices( )
{
	return mNumSlices;
}






//=================================================================
//	RenderNode::SetSliceSpacingExponent
//---------------------------------------
void RenderNode::SetSliceSpacingExponent( Real exponent )
{
	mSpacingExponent = exponent;
}





//=================================================================
//	RenderNode::GetSliceSpacingExponent
//---------------------------------------
Real RenderNode::GetSliceSpacingExponent( )
{
	return mSpacingExponent;
}





//=================================================================
//	RenderNode::SetDebugFlags
//---------------------------------------
void RenderNode::SetDebugFlags( UInt32 debugFlags )
{
	mDebugFlags = debugFlags;
}





//=================================================================
//	RenderNode::GetDebugFlags
//---------------------------------------
UInt32 RenderNode::GetDebugFlags( )
{
	return mDebugFlags;
}





//=================================================================
//	RenderNode::SetLighting
//---------------------------------------
void RenderNode::SetLighting( bool enable )
{
	mLighting = enable;
}





//=================================================================
//	RenderNode::GetLighting
//---------------------------------------
bool RenderNode::GetLighting()
{
	return mLighting;
}





//=================================================================
//	RenderNode::SetTransformMatrix
//---------------------------------------
void RenderNode::SetTransformMatrix()
{
//	glPushMatrix();

//	glMatrixMode(GL_MODELVIEW);
//	glLoadMatrixf( GetTransform().data() );
}





//=================================================================
//	RenderNode::UnsetTransformMatrix
//---------------------------------------
void RenderNode::UnsetTransformMatrix()
{
//	glPopMatrix();
}



//=================================================================
//	RenderNode::SetLightingMode
//---------------------------------------
void RenderNode::SetLightingMode(const Vector3 &cameraDir)
{
	if( mLighting )
	{
		if( !mNormalMap )
		{
			mNormalMap = NormalMapGenerator::Generate( *mTexture, NM_HARDWARE | NM_QUALITY_POOR );
		}

		if( mNormalMap )
		{
			mNormalMap->Bind(1);

			extern ShaderProgram myShader;
			
			myShader.Use();

			ShaderUniform tex1 = myShader.GetUniform( "texture1" );

			if( tex1.IsValid() )
			{
				tex1.SetInt( 0 );
			}
			else
			{
				std::cerr << "Shader uniform 'texture1' not found!" << std::endl;
			}


			ShaderUniform tex2 = myShader.GetUniform( "texture2" );

			if( tex2.IsValid() )
			{
				tex2.SetInt( 1 );
			}
			else
			{
				std::cerr << "Shader uniform 'texture2' not found!" << std::endl;
			}

			ShaderUniform lm = myShader.GetUniform( "lightModel" );
			lm.SetInt(mLighting);

			extern Eigen::Vector4f lightPos;
			ShaderUniform l = myShader.GetUniform( "l" );
			l.SetVec3Float( lightPos.x(), lightPos.y(), lightPos.z() );

			ShaderUniform h = myShader.GetUniform( "h" );
			h.SetVec3Float( cameraDir.x(), cameraDir.y(), cameraDir.z() );
		}
	}
}





//=================================================================
//	RenderNode::SetLightingMode
//---------------------------------------
void RenderNode::UnsetLightingMode()
{
	if( mLighting )
	{
		mNormalMap->Unbind(1);

		glUseProgram( 0 );
	}
}



void RenderNode::SetVolumeData( VolumeData &volume )
{
	mTexture = new Texture3D( volume );
	mNormalMap = 0L;	
}





//=================================================================
//	RenderNode::GetNormalMap
//---------------------------------------
Texture3DPtr RenderNode::GetNormalMap( bool generate )
{
	if( generate && !mNormalMap && mTexture )
	{
		mNormalMap = NormalMapGenerator::Generate( *mTexture, NM_HARDWARE );

		if( !mNormalMap )
		{
			NormalMapGenerator::Generate( *mTexture, NM_SOFTWARE );
		}
	}

	return mNormalMap;
}





//=================================================================
//	RenderNode::GetTransform
//---------------------------------------
Matrix4 RenderNode::GetTransform() const
{
	return mTransform;
}





//=================================================================
//	RenderNode::SetTransform
//---------------------------------------
void RenderNode::SetTransform( const Matrix4 &transform )
{
	mTransform = transform;
}





//=================================================================
//	RenderNode::Draw
//---------------------------------------
void RenderNode::Draw(const Vector3 &cameraDir)
{
	Vector3		minP(0,0,0);
	Vector3		maxP(1,1,1);
	AABB		box(minP, maxP);

	// Tranformation matrix
	SetTransformMatrix();

	// Initialize rendering state
	glUseProgram( 0 );
	glBindTexture( GL_TEXTURE_3D, 0 );

	// Draw the volume bounding box
	if( mDebugFlags & DBG_DRAW_BBOX )
	{
		DrawBox( minP, maxP );
	}

	// Draw the polygonOutline
	if( mDebugFlags & DBG_DRAW_SLICES )
	{	
		for( int slice= mNumSlices; slice > 0; slice-- )
		{
			Real perc = (Real) slice/(mNumSlices+1);
			perc = pow( perc, (Real) mSpacingExponent );

			Polygon poly = box.SliceByPercentage( cameraDir, perc );
			DrawPolygon( poly );
		}
	}

	// Setup rendering state
	BindTexture();
	SetLightingMode(cameraDir);

	// Use normal map instead of color
	if( showNorm%3 == 1 && mNormalMap)
	{
		mNormalMap->Bind();
	}
	

	// Render Volume
	for( int slice= mNumSlices; slice > 0; slice-- )
	{
		Real perc = (Real) slice/(mNumSlices+1);
		perc = pow( perc, (Real) mSpacingExponent );

		Polygon poly = box.SliceByPercentage( cameraDir, perc );
		DrawPolygonFill( poly );
	}

	// Unset rendering state
	UnsetLightingMode();
	mTexture->Unbind();

	UnsetTransformMatrix();
}


VROOM_END
