//=================================================================
//	Inlude
//---------------------------------------
#include "TexMapVolumeRendererNode.h"
#include "Texture3D.h"
#include "VolumeData.h"

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
	int vertCount = poly.GetVertexCount();

	if( vertCount > 0 )
	{		
		glBegin( GL_TRIANGLE_FAN );

		for( int i=0; i< vertCount; i++ )
		{
			Vector3 point = poly.GetVertex( i );

			glTexCoord3f( point.x(), point.y(),	point.z() );
			glVertex3f(   point.x(), point.y(),	point.z() );
		}

		glEnd();
	}
}





//=================================================================
//	NormalMapKernel : utility function generate normal of a voxel
//---------------------------------------
static Vector3 NormalMapKernel(const VolumeData &vol, UInt32 x, UInt32 y, UInt32 z)
{
	const UInt8 alphaTeshold = 60;
	Vector3 direction(0,0,0);

	Color vox = vol.GetVoxel( x, y, z );

	if( vox.alpha < alphaTeshold )
		return direction;

	for(int xx= x-1; xx<=x+1; xx++)
	if( xx >= 0 && xx < vol.GetWidth() )
	{
		for(int yy=y-1; yy<=y+1; yy++)
		if( yy >= 0 && yy < vol.GetHeight() )
		{
			for(int zz=z-1; zz<=z+1; zz++)
			if( zz >= 0 && zz < vol.GetDepth() )
			{
				vox = vol.GetVoxel( xx, yy, zz );
				if( vox.alpha > alphaTeshold )
				{
					Vector3 voxDir( xx-(int)x, yy-(int)y, zz-(int)z );

					float norm = voxDir.norm();
					if( norm > 0.8 )
						voxDir/= norm;

					direction += voxDir;
				}
			}
		}
	}
	if( direction.nonZeros() )
		direction.normalize();

	return -direction;
}





//=================================================================
//	GenerateNormalMap : utility function generate normal map
//---------------------------------------
static void GenerateNormalMap( const VolumeData &vol, VolumeData &normMap )
{
	normMap.Create( vol.GetWidth(), vol.GetHeight(), vol.GetDepth());

	for( UInt32 x = 0; x< vol.GetWidth(); x++)
	{
		for( UInt32 y = 0; y< vol.GetHeight(); y++)
		{
			for( UInt32 z = 0; z< vol.GetDepth(); z++)
			{
				Vector3 dir = NormalMapKernel( vol, x,y,z );

				Color col;
				col.red =	(UInt8) (dir.x()*127) + 127;
				col.green =	(UInt8) (dir.y()*127) + 127;
				col.blue =	(UInt8) (dir.z()*127) + 127;
				col.alpha = vol.GetVoxel(x,y,z).alpha;

				normMap.SetVoxel(x,y,z, col);
			}
		}
	}
}





//=================================================================
//	TexMapVolumeRendererNode::TexMapVolumeRendererNode
//---------------------------------------
TexMapVolumeRendererNode::TexMapVolumeRendererNode() :
	mTexture( 0 ),
	mNumSlices( 100 ),
	mSpacingExponent( 1 ),
	mDebugFlags( 0 ),
	mNormalMap( 0 ),
	mLighting( 0 )
{
}





//=================================================================
//	TexMapVolumeRendererNode::BindTexture
//---------------------------------------
void TexMapVolumeRendererNode::BindTexture()
{
	if( !mTexture )
	{
		VolumeData * theVolume = GetVolumeData();

		if( theVolume )
		{
			mTexture = new Texture3D( *theVolume );
		}
	}

	if( mTexture )
	{
		mTexture->Bind(0);
	}
}





//=================================================================
//	TexMapVolumeRendererNode::SetNumberOfSlices
//---------------------------------------
void TexMapVolumeRendererNode::SetNumberOfSlices( UInt32 numSlices )
{
	mNumSlices = numSlices;
}





//=================================================================
//	TexMapVolumeRendererNode::GetNumberOfSlices
//---------------------------------------
UInt32 TexMapVolumeRendererNode::GetNumberOfSlices( )
{
	return mNumSlices;
}






//=================================================================
//	TexMapVolumeRendererNode::SetSliceSpacingExponent
//---------------------------------------
void TexMapVolumeRendererNode::SetSliceSpacingExponent( Real exponent )
{
	mSpacingExponent = exponent;
}





//=================================================================
//	TexMapVolumeRendererNode::GetSliceSpacingExponent
//---------------------------------------
Real TexMapVolumeRendererNode::GetSliceSpacingExponent( )
{
	return mSpacingExponent;
}





//=================================================================
//	TexMapVolumeRendererNode::SetDebugFlags
//---------------------------------------
void TexMapVolumeRendererNode::SetDebugFlags( UInt32 debugFlags )
{
	mDebugFlags = debugFlags;
}





//=================================================================
//	TexMapVolumeRendererNode::GetDebugFlags
//---------------------------------------
UInt32 TexMapVolumeRendererNode::GetDebugFlags( )
{
	return mDebugFlags;
}





//=================================================================
//	TexMapVolumeRendererNode::SetLighting
//---------------------------------------
void TexMapVolumeRendererNode::SetLighting( bool enable )
{
	mLighting = enable;
}





//=================================================================
//	TexMapVolumeRendererNode::GetLighting
//---------------------------------------
bool TexMapVolumeRendererNode::GetLighting( )
{
	return mLighting;
}





//=================================================================
//	TexMapVolumeRendererNode::SetTransformMatrix
//---------------------------------------
void TexMapVolumeRendererNode::SetTransformMatrix()
{
	glPushMatrix();

	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf( GetTransform().data() );
}





//=================================================================
//	TexMapVolumeRendererNode::UnsetTransformMatrix
//---------------------------------------
void TexMapVolumeRendererNode::UnsetTransformMatrix()
{
	glPopMatrix();
}





//=================================================================
//	TexMapVolumeRendererNode::SetLightingMode
//---------------------------------------
void TexMapVolumeRendererNode::SetLightingMode()
{
	if( mLighting )
	{
		if( !mNormalMap )
		{
			VolumeData * theVolume = GetVolumeData();			

			if( theVolume )
			{
				VolumeData normMapVol;
				GenerateNormalMap( *theVolume, normMapVol );

				mNormalMap = new Texture3D( normMapVol );
			}
		}

		if( mNormalMap )
		{
			mNormalMap->Bind(1);

			extern GLuint myShader;
			glUseProgram( myShader );

			GLint loc = glGetUniformLocation(myShader, "texture1");
			if (loc != -1)
				glUniform1i(loc, 0);
			else
				std::cout << "Waaaaa1" << std::endl;

			loc = glGetUniformLocation(myShader, "texture2");
			if (loc != -1)
				glUniform1i(loc, 1);
			else
				std::cout << "Waaaaa2" << std::endl;			
		}
	}
}





//=================================================================
//	TexMapVolumeRendererNode::SetLightingMode
//---------------------------------------
void TexMapVolumeRendererNode::UnsetLightingMode()
{
	if( mLighting )
	{
		mNormalMap->Unbind(1);

		glUseProgram( 0 );
	}
}





//=================================================================
//	TexMapVolumeRendererNode::Draw
//---------------------------------------
void TexMapVolumeRendererNode::Draw(const Vector3 &cameraDir)
{
	Vector3		minP(0,0,0);
	Vector3		maxP(1,1,1);
	AABB		box(minP, maxP);


	// Tranformation matrix
	SetTransformMatrix();

	if( mDebugFlags & DBG_DRAW_BBOX )
	{
		DrawBox( minP, maxP );
	}

	BindTexture();
	SetLightingMode();

	for( int i= mNumSlices; i > 0; i-- )
	{
		Real perc = (Real) i/(mNumSlices+1);
		perc = pow( perc, (Real) mSpacingExponent );


		Polygon poly = box.SliceByPercentage( cameraDir, perc );

		// Draw the polygonOutline
		if( mDebugFlags & DBG_DRAW_SLICES )
		{
			DrawPolygon( poly );
		}		

		DrawPolygonFill( poly );
	}

	UnsetLightingMode();
	mTexture->Unbind();

	UnsetTransformMatrix();
}


VROOM_END
