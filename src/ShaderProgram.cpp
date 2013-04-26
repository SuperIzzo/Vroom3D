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
	if( mProgram )
	{
		glDeleteProgram( mProgram );	
		mProgram = 0;
	}

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
//	ShaderProgram::IsLinked
//---------------------------------------
bool ShaderProgram::IsLinked() const
{
	GLint linked = false;

	if( mProgram )
	{
		glGetObjectParameterivARB( mProgram, GL_LINK_STATUS, &linked );		
	}

	return( linked!=0 );
}





//=================================================================
//	ShaderProgram::Link
//---------------------------------------
void ShaderProgram::Link()
{
	if( mShaders.size()>0 )
	{
		glLinkProgram( mProgram );
	}
}





//=================================================================
//	ShaderProgram::Use
//---------------------------------------
void ShaderProgram::Use()
{
	if( IsLinked() )
	{
		glUseProgram( mProgram );
	}
}





//=================================================================
//	ShaderProgram::Unuse
//---------------------------------------
void ShaderProgram::Unuse()
{
	if( IsLinked() )
	{
		glUseProgram( 0 );
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
	if( !mProgram )
	{
		CreateProgram();
	}

	if( mProgram )
	{
		if( ! IsAttached(shader) )
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

		mShaders.erase( shaderIter );
	}
}





//=================================================================
//	ShaderProgram::GetUniformVar
//---------------------------------------
ShaderUniform ShaderProgram::GetUniform( String name )
{
	GLint location = glGetUniformLocation( mProgram, name.c_str() );

	return ShaderUniform( location );
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