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
#include "NormalMapGenerator.h"
#include "MathCommon.h"
#include "GraphicsCommon.h"

#include "ShaderProgram.h"


VROOM_BEGIN


//=================================================================
//	NormalMapKernel : utility function generate normal of a voxel
//---------------------------------------
static Vector3 NormalMapPlusKernel(const VolumeData &vol, UInt32 x, UInt32 y, UInt32 z)
{
	Color voxel = vol.GetVoxel( x, y, z );

	Vector3 normalDir = Vector3(0,0,0);

	if( voxel.alpha > 10 )
	{
		for(int i= -1; i<=1; i+= 2)
		{
			if( x+i > 0 &&	x+i< vol.GetWidth()-1 )
				normalDir.x() += i * vol.GetVoxel( x+i, y, z ).alpha;

			if( y+i > 0 &&	y+i< vol.GetHeight()-1 )
				normalDir.y() += i * vol.GetVoxel( x, y+i, z ).alpha;

			if( z+i > 0 &&	z+i< vol.GetWidth()-1 )
				normalDir.z() += i * vol.GetVoxel( x, y, z+i ).alpha;
		}

		float normLen = normalDir.norm();
		if( normLen > 0.0 )
		{
			normalDir /= normLen;
		}
	}

	return normalDir;	
}





//=================================================================
//	NormalMapKernel : utility function generate normal of a voxel
//---------------------------------------
static Vector3 NormalMapCubeKernel(const VolumeData &vol, UInt32 x, UInt32 y, UInt32 z)
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

	return direction;
}





//=================================================================
//	NormalMapGenerator::Generate
//---------------------------------------
Texture3DPtr NormalMapGenerator::Generate( Texture3D &texture, UInt32 flags )
{
	Texture3DPtr normalMapTexture = 0;

	NMQualityEnum quality = (NMQualityEnum) (flags & NM_QUALITY_GOOD);

	if( flags & NM_HARDWARE )
	{
		if( flags & NM_TRANSPARENT )
		{
			// DO NOTHING
		}
		else
		{
			normalMapTexture = GenerateHWOpaque(texture, quality);
		}
	}

	if( !normalMapTexture ) 
	{
		if( flags & NM_TRANSPARENT )
		{
			// DO NOTHING
		}
		else
		{			
			// Move the memory from VRAM to RAM
			VolumeData volumeData;			
			texture.GetVolumeData( volumeData );

			// Generate the normal
			VolumeDataPtr normalMapVolume = 0;
			normalMapVolume = GenerateSWOpaque( volumeData, quality );

			// Return memory back to VRAM
			normalMapTexture = new Texture3D(*normalMapVolume);
		}
	}

	return normalMapTexture;
}





//=================================================================
//	NormalMapGenerator::GenerateSWOpaque
//---------------------------------------
VolumeDataPtr NormalMapGenerator::GenerateSWOpaque( VolumeData &volume,
													NMQualityEnum quality )
{
	// Create the normal map
	VolumeDataPtr normalMapVolume = new VolumeData();
	normalMapVolume->Create( 
		volume.GetWidth(), 
		volume.GetHeight(), 
		volume.GetDepth() 
	);

	// Fill the normal map
	for( UInt32 x = 0; x<volume.GetWidth(); x++)
	{
		for( UInt32 y = 0; y<volume.GetHeight(); y++)
		{
			for( UInt32 z = 0; z<volume.GetDepth(); z++)
			{
				Vector3 direction(0,0,0);

				switch( quality )
				{					
					case NM_QUALITY_GOOD :
							direction = NormalMapCubeKernel( volume, x,y,z );
							break;

					default :	
							direction = NormalMapPlusKernel( volume, x,y,z );
				}

				Color color;
				color.red =		(UInt8) (direction.x()*127) + 127;
				color.green =	(UInt8) (direction.y()*127) + 127;
				color.blue =	(UInt8) (direction.z()*127) + 127;
				color.alpha =	volume.GetVoxel(x,y,z).alpha;

				normalMapVolume->SetVoxel(x,y,z, color);
			}
		}
	}

	return normalMapVolume;
}



//=================================================================
//	NormalMapGenerator::GenerateHWOpaque
//---------------------------------------
Texture3DPtr NormalMapGenerator::GenerateHWOpaque(	Texture3D &texture,
													NMQualityEnum quality )
{
	// Sany check - are framebuffers supported
	if( !(glGenFramebuffers && glFramebufferTextureLayer) )
	{
		return 0;
	}


	Texture3DPtr normalMapTex = new Texture3D();
	normalMapTex->Create(
		texture.GetWidth(),
		texture.GetHeight(), 
		texture.GetDepth()
	);	
	
	GLuint theFBO = 0;
	glGenFramebuffers(1, &theFBO);

	extern ShaderProgram myNormalShader;
	myNormalShader.Use();
	myNormalShader.GetUniform("texture1").SetInt(0);
	myNormalShader.GetUniform("res").SetVec3Float(
		1.0f/texture.GetWidth(),
		1.0f/texture.GetHeight(),
		1.0f/texture.GetDepth()
	);


	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glViewport( 0, 0, normalMapTex->GetWidth(), normalMapTex->GetHeight() );

	glBindFramebuffer( GL_FRAMEBUFFER, theFBO );
	

	float normalTextureDepth = normalMapTex->GetDepth();

	texture.Bind();

	for(int layer=0; layer < normalTextureDepth; layer++)
	{	

		glFramebufferTextureLayer(
			GL_FRAMEBUFFER,
			GL_COLOR_ATTACHMENT0,
			normalMapTex->__GetTextureID(),
			0,
			layer
		);

		float texDepth = (float) layer/normalTextureDepth;
			
		glBegin( GL_TRIANGLE_FAN );

			glTexCoord3f( 0, 0,	texDepth );
			glVertex3f( -1,-1, 0 );

			glTexCoord3f( 0, 1,	texDepth );
			glVertex3f( -1, 1, 0 );

			glTexCoord3f( 1, 1,	texDepth );
			glVertex3f( 1, 1, 0 );

			glTexCoord3f( 1, 0,	texDepth );
			glVertex3f( 1, -1, 0 );

		glEnd();
	}

	glBindFramebuffer( GL_FRAMEBUFFER, 0 );		
	glUseProgram(0);
	glViewport( 0, 0, 640, 480 );
	glDeleteFramebuffers(0, &theFBO);

	return normalMapTex;
}


VROOM_END