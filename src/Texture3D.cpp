//=================================================================
//	Inlude
//---------------------------------------
#include "Texture3D.h"

#include <Windows.h>
#include <gl/glew.h>
#include <gl/GL.h>
#include <gl/GLU.h>


VROOM_BEGIN

GLint TexUnits[4] = {GL_TEXTURE0, GL_TEXTURE1, GL_TEXTURE2, GL_TEXTURE3};


//=================================================================
//	GetTex3DFunction [internal]
//---------------------------------------
static PFNGLTEXIMAGE3DPROC GetTex3DFunction()
{
	static PFNGLTEXIMAGE3DPROC glTexImage3D = 0;

	if( !glTexImage3D )
	{
		glEnable( GL_TEXTURE_3D );
		glTexImage3D = (PFNGLTEXIMAGE3DPROC) wglGetProcAddress("glTexImage3D");
	}

	return glTexImage3D;
}





//=================================================================
//	Texture3D::Texture3D
//---------------------------------------
Texture3D::Texture3D() :
	mTextureID( 0 )
{
};





//=================================================================
//	Texture3D::Texture3D
//---------------------------------------
Texture3D::Texture3D( const Volume &volume ) :
	mTextureID( 0 )
{
	CreateFromVolume(volume);
}





//=================================================================
//	Texture3D::SetScalingFilter
//---------------------------------------
void Texture3D::SetScalingFilter( ScalingFilter filter )
{
	SetScalingFilter( filter, filter );
}





//=================================================================
//	Texture3D::SetScalingFilter
//---------------------------------------
void Texture3D::SetScalingFilter( ScalingFilter mag, ScalingFilter min )
{
	if( Bind() )
	{
		GLint glMagFilter = GL_NEAREST;
		GLint glMinFilter = GL_NEAREST;

		if( mag == SF_LINEAR )
		{
			glMagFilter = GL_LINEAR;
		}

		if( min == SF_LINEAR )
		{
			glMinFilter = GL_LINEAR;
		}

		glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, glMagFilter );
		glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, glMinFilter );
	}
}





//=================================================================
//	Texture3D::SetWrapFunction
//---------------------------------------
void Texture3D::SetWrapFunction( int func )
{
	if( Bind() )
	{
		glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, func);
		glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, func);
		glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, func);
	}
}





//=================================================================
//	Texture3D::Destroy
//---------------------------------------
void Texture3D::Destroy()
{
	const GLsizei NUMBER_OF_TEXTURES = 1;

	glDeleteTextures( NUMBER_OF_TEXTURES, &mTextureID );
	mTextureID = 0;
}





//=================================================================
//	Texture3D::CreateFromVolume
//---------------------------------------
void Texture3D::CreateFromVolume( const Volume &volume )
{
	const GLsizei NUMBER_OF_TEXTURES = 1;
	const GLint   MIP_MAP_LEVEL_0	 = 0;
	const GLint   BORDER_SIZE_0		 = 0;

	// Reset our texture
	Destroy();

	PFNGLTEXIMAGE3DPROC glTexImage3D = GetTex3DFunction();

	if( glTexImage3D )
	{
		glGenTextures(NUMBER_OF_TEXTURES, &mTextureID);		
		
		SetScalingFilter( SF_LINEAR );
		SetWrapFunction( GL_CLAMP );		
				
		glTexImage3D(
			GL_TEXTURE_3D, 
			MIP_MAP_LEVEL_0, 
			GL_RGBA8,

			volume.GetWidth(), 
			volume.GetHeight(),
			volume.GetDepth(), 

			BORDER_SIZE_0,

			GL_RGBA, 
			GL_UNSIGNED_BYTE, 
			(GLvoid*) volume.GetData()
		);
	}
	else
	{
		//throw GraphicsHardwareException( "Unable to obtain glTexImage3D." );
	}
}





//=================================================================
//	Texture3D::Bind
//---------------------------------------
bool Texture3D::Bind( UInt8 unit )
{
	GLenum theTextureUnit = TexUnits[unit];

	glActiveTexture( theTextureUnit );
	glBindTexture(GL_TEXTURE_3D, mTextureID);

	return( mTextureID>0 );
}





//=================================================================
//	Texture3D::Unbind
//---------------------------------------
bool Texture3D::Unbind( UInt8 unit )
{
	GLenum theTextureUnit = TexUnits[unit];

	glActiveTexture( theTextureUnit );
	glBindTexture(GL_TEXTURE_3D, 0);

	return true;
}


VROOM_END