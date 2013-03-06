//=================================================================
//	Inlude
//---------------------------------------
#include "ShaderProgram.h"
#include "GraphicsCommon.h"
#include "GraphicsHardwareException.h"

#include <algorithm>


VROOM_BEGIN


//=================================================================
//	ShaderProgram::ShaderProgram
//---------------------------------------
ShaderProgram::ShaderProgram() :
	mProgram(0)
{
	InitGraphicsCoreOnce();
}





//=================================================================
//	ShaderProgram::~ShaderProgram
//---------------------------------------
ShaderProgram::~ShaderProgram()
{
	Destroy();
}





//=================================================================
//	ShaderProgram::Destroy
//---------------------------------------
void ShaderProgram::Destroy()
{
	glDeleteProgram( mProgram );
	
	mProgram = 0;

	// Detach shaders
	mShaders.clear();
}





//=================================================================
//	ShaderProgram::CreateProgram
//---------------------------------------
void ShaderProgram::CreateProgram()
{
	Destroy();

	mProgram = glCreateProgram();
}






//=================================================================
//	ShaderProgram::IsValid
//---------------------------------------
bool ShaderProgram::IsValid() const
{
	return( mProgram>0 );
}





//=================================================================
//	ShaderProgram::Link
//---------------------------------------
void ShaderProgram::Link()
{
	if( mShaders.size()>0 )
	{
		glLinkProgram( mProgram );

		// TODO: Deal with errors, 
	}
}





//=================================================================
//	ShaderProgram::IsAttached
//---------------------------------------
bool ShaderProgram::IsAttached( ShaderPtr shader )
{
	ShaderList::iterator shaderIter = FindShader( shader );
	
	return( shaderIter != mShaders.end() );
}





//=================================================================
//	ShaderProgram::AttachShader
//---------------------------------------
void ShaderProgram::AttachShader( ShaderPtr shader )
{
	if( !IsValid() )
	{
		CreateProgram();
	}

	if( IsValid() )
	{
		if( IsAttached(shader) )
		{
			// Throw an exception
		}
		else
		{
			glAttachShader( mProgram, shader->mShader );
			// TODO: Consider and deal with error 
			//		 Don't add to the list if failed

			mShaders.push_back( shader );
		}
	}
}





//=================================================================
//	ShaderProgram::DetachShader
//---------------------------------------
void ShaderProgram::DetachShader( ShaderPtr shader )
{
	ShaderList::iterator shaderIter = FindShader( shader );
	
	if( shaderIter != mShaders.end() )
	{
		glDetachShader( mProgram, (*shaderIter)->mShader );
		// TODO: Deal with error

		mShaders.erase( shaderIter );
	}
}





//=================================================================
//	ShaderProgram::FindShader
//---------------------------------------
ShaderProgram::ShaderList::iterator
	ShaderProgram::FindShader( ShaderPtr shader )
{
	return std::find( mShaders.begin(), mShaders.end(), shader );
}


VROOM_END