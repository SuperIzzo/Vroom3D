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
//	GetUnitBox - static constant
//---------------------------------------
static const AABB& GetUnitBox()
{
	static const AABB	box( Vector3(0,0,0), Vector3(1,1,1));

	return box;
}





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
	mNumSlices( 100 ),
	mSpacingExponent( 1 ),
	mDebugFlags( 0 ),
	mNormalMap( 0 ),
	mShadingMode( 0 )
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
//	RenderNode::SetShadingModel
//---------------------------------------
void RenderNode::SetShadingModel( UInt32 mode )
{
	mShadingMode = mode;
}





//=================================================================
//	RenderNode::GetShadingModel
//---------------------------------------
UInt32 RenderNode::GetShadingModel()
{
	return mShadingMode;
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
	if( mShadingMode )
	{
		Texture3DPtr normalMap = GetNormalMap(true);

		if( normalMap )
		{
			normalMap->Bind(1);
		}
	}
}





//=================================================================
//	RenderNode::SetLightingMode
//---------------------------------------
void RenderNode::UnsetLightingMode()
{
	if( mShadingMode )
	{
		mNormalMap->Unbind(1);

		glUseProgram( 0 );
	}
}





//=================================================================
//	RenderNode::SetVolumeData
//---------------------------------------
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
//	RenderNode::DrawDebugGeometry
//---------------------------------------
void RenderNode::DrawDebugGeometry(const Vector3 &cameraDir)
{
	static const Vector3 minP(0,0,0);
	static const Vector3 maxP(1,1,1);


	// Tranformation matrix
	SetTransformMatrix();

	// Initialize rendering state
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
			const AABB &box = GetUnitBox();

			Real perc = (Real) slice/(mNumSlices+1);
			perc = pow( perc, (Real) mSpacingExponent );

			Polygon poly = box.SliceByPercentage( cameraDir, perc );
			DrawPolygon( poly );
		}
	}
}





//=================================================================
//	RenderNode::Draw
//---------------------------------------
void RenderNode::Draw(const Vector3 &cameraDir)
{
	// Tranformation matrix
	SetTransformMatrix();

	// Setup rendering state
	BindTexture();
	SetLightingMode(cameraDir);

	// Use normal map instead of color
	if( mDebugFlags & DBG_DRAW_NORMALS )
	{
		Texture3DPtr normalMap = GetNormalMap(true);
		normalMap->Bind();
	}
	

	// Render Volume
	for( int slice= mNumSlices; slice > 0; slice-- )
	{
		const AABB &box = GetUnitBox();

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
