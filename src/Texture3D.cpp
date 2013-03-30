//=================================================================
//	Inlude
//---------------------------------------
#include "Texture3D.h"
#include "GraphicsCommon.h"


VROOM_BEGIN


//=================================================================
//	Local constants
//---------------------------------------
static const GLint   MIP_MAP_LEVEL_0	 = 0;





//=================================================================
//	TexUnits: GL_TEXTURE remap
//---------------------------------------
GLint TexUnits[4] = 
{
	GL_TEXTURE0, GL_TEXTURE1, GL_TEXTURE2, GL_TEXTURE3
};





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
	InitGraphicsCoreOnce();
};





//=================================================================
//	Texture3D::Texture3D
//---------------------------------------
Texture3D::Texture3D( const VolumeData &volume ) :
	mTextureID( 0 )
{
	Create(volume);
}





//=================================================================
//	Texture3D::SetSmooth
//---------------------------------------
void Texture3D::SetSmooth( bool smooth )
{
	if( Bind() )
	{
		GLint glMagFilter = GL_NEAREST;
		GLint glMinFilter = GL_NEAREST;

		if( smooth ) 
		{
			glMagFilter = GL_LINEAR;
			glMinFilter = GL_LINEAR;
		}

		glTexParameteri( GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, glMagFilter );
		glTexParameteri( GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, glMinFilter );
	}
}





//=================================================================
//	Texture3D::IsSmooth
//---------------------------------------
bool Texture3D::IsSmooth() const
{
	GLint glMagFilter;

	glGetTexParameteriv( GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, &glMagFilter );

	return (glMagFilter != GL_NEAREST);
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
//	Texture3D::Create
//---------------------------------------
void Texture3D::Create( const VolumeData &volume )
{
	CreateFromData( volume.GetWidth(),
					volume.GetHeight(),
					volume.GetDepth(),
					(void*) volume.GetData() );
}





//=================================================================
//	Texture3D::Create
//---------------------------------------
void Texture3D::Create( UInt32 width, UInt32 height, UInt32 depth )
{
	CreateFromData( width, height, depth, NULL );
}





//=================================================================
//	Texture3D::CreateFromData
//---------------------------------------
void Texture3D::CreateFromData( UInt32 width, UInt32 height, UInt32 depth, void *data)
{
	const GLsizei NUMBER_OF_TEXTURES = 1;
	const GLint   BORDER_SIZE_0		 = 0;

	// Reset our texture
	Destroy();

	PFNGLTEXIMAGE3DPROC glTexImage3D = GetTex3DFunction();

	if( glTexImage3D )
	{
		glGenTextures(NUMBER_OF_TEXTURES, &mTextureID);		
		
		SetSmooth( true );
		SetWrapFunction( GL_REPEAT );		
				
		glTexImage3D(
			GL_TEXTURE_3D, 
			MIP_MAP_LEVEL_0, 
			GL_RGBA8,

			width, 
			height,
			depth, 

			BORDER_SIZE_0,

			GL_RGBA, 
			GL_UNSIGNED_BYTE, 
			(GLvoid*) data
		);
	}
	else
	{
		throw GraphicsHardwareException( "Unable to obtain glTexImage3D." );
	}
}





//=================================================================
//	Texture3D::Bind
//---------------------------------------
bool Texture3D::Bind( UInt8 unit ) const
{
	GLenum theTextureUnit = TexUnits[unit];

	glActiveTexture( theTextureUnit );
	glBindTexture(GL_TEXTURE_3D, mTextureID);

	return IsValid();
}





//=================================================================
//	Texture3D::Unbind
//---------------------------------------
bool Texture3D::Unbind( UInt8 unit ) const
{
	GLenum theTextureUnit = TexUnits[unit];

	glActiveTexture( theTextureUnit );
	glBindTexture(GL_TEXTURE_3D, 0);

	return true;
}





//=================================================================
//	Texture3D::IsValid
//---------------------------------------
bool Texture3D::IsValid() const
{
	return( mTextureID>0 );
}





//=================================================================
//	Texture3D::IsValid
//---------------------------------------
UInt32 Texture3D::__GetTextureID() const
{
	return mTextureID;
}





//=================================================================
//	Texture3D::GetWidth
//---------------------------------------
UInt32 Texture3D::GetWidth() const
{
	GLint theWidth = 0;

	if( Bind() )
	{
		glGetTexLevelParameteriv( 
			GL_TEXTURE_3D, 
			MIP_MAP_LEVEL_0, 
			GL_TEXTURE_WIDTH, 
			&theWidth 
		);
	}
	
	return theWidth;
}





//=================================================================
//	Texture3D::GetHeight
//---------------------------------------
UInt32 Texture3D::GetHeight() const
{
	GLint theHeight = 0;

	if( Bind() )
	{
		glGetTexLevelParameteriv( 
			GL_TEXTURE_3D, 
			MIP_MAP_LEVEL_0, 
			GL_TEXTURE_HEIGHT, 
			&theHeight 
		);
	}
	
	return theHeight;
}





//=================================================================
//	Texture3D::GetDepth
//---------------------------------------
UInt32 Texture3D::GetDepth() const
{
	GLint theDepth = 0;

	if( Bind() )
	{
		glGetTexLevelParameteriv( 
			GL_TEXTURE_3D, 
			MIP_MAP_LEVEL_0, 
			GL_TEXTURE_DEPTH, 
			&theDepth 
		);
	}
	
	return theDepth;
}





//=================================================================
//	Texture3D::GetVolumeData
//---------------------------------------
void Texture3D::GetVolumeData(VolumeData &volume) const
{
	if( Bind() )
	{
		// Make sure our volume has correct data size
		// we may have to recreate it
		UInt32 ownWidth = GetWidth();
		UInt32 ownHeight = GetHeight();
		UInt32 ownDepth = GetWidth();

		if( ownWidth != volume.GetWidth()
			|| ownHeight != volume.GetHeight()
			|| ownDepth != volume.GetDepth() )
		{
			volume.Create( ownWidth, ownHeight, ownDepth );
		}


		UInt8 *volumeData = volume.GetData();

		glGetTexImage( 
			GL_TEXTURE_3D, 
			MIP_MAP_LEVEL_0,
			GL_RGBA,
			GL_UNSIGNED_BYTE,
			(GLvoid*) volumeData 
		);
	}
	else
	{
		throw InvalidStateException();
	}
}


VROOM_END