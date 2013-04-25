/*ZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZ*\
Z|                                                                           |Z
Z|  The MIT License (MIT)                                                    |Z
Z|                                                                           |Z
Z|  Copyright (c) 2013 Hristoz Stefanov                                      |Z
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
#include "Shader.h"
#include "GraphicsCommon.h"
#include "GraphicsHardwareException.h"
#include "InvalidArgumentException.h"


VROOM_BEGIN


//=================================================================
//	GLShaderTypes : Converts ShaderType enum to OpenGL constants
//---------------------------------------
static GLenum GLShaderTypes( Shader::ShaderType shaderType )
{
	GLenum glShaderType;

	switch( shaderType )
	{
		case Shader::ST_VERTEX: 
			glShaderType = GL_VERTEX_SHADER;
			break;

		case Shader::ST_FRAGMENT: 
			glShaderType = GL_FRAGMENT_SHADER;
			break;

		default:
			throw InvalidArgumentException();
	}
	
	return glShaderType;
}





//=================================================================
//	Shader::Shader
//---------------------------------------
Shader::Shader() :
	mShader(0)
{
	InitGraphicsCoreOnce();
}





//=================================================================
//	Shader::~Shader
//---------------------------------------
Shader::~Shader()
{
	Destroy();
}





//=================================================================
//	Shader::CreateShader
//---------------------------------------
void Shader::CreateShader(ShaderType shaderType)
{
	// Sanity check
	if( !glCreateShader )
	{
		throw GraphicsHardwareException( "Shaders not supported." );
	}
	
	// Reset
	Destroy();

	// Create a new shader
	GLenum	glShaderType = GLShaderTypes( shaderType );
	mShader	= glCreateShader( glShaderType );

	if( !mShader )
	{
		throw GraphicsHardwareException( "Unable to create shader." );
	}
};





//=================================================================
//	Shader::Destroy
//---------------------------------------
void Shader::Destroy()
{
	if( mShader )
	{
		glDeleteShader( mShader );
		mShader = 0;
	}
}





//=================================================================
//	Shader::IsCompiled
//---------------------------------------
bool Shader::IsCompiled() const
{
	GLint compiled = false;

	if( mShader )
	{
		glGetObjectParameterivARB( mShader, GL_COMPILE_STATUS, &compiled );
	}
	
	return( compiled!=0 );
}





//=================================================================
//	Shader::CompileString
//---------------------------------------
bool Shader::CompileString(ShaderType shaderType, String text)
{
	GLint sourceLength		= text.length() + 1;
	GLcharARB *sourceText	= (GLcharARB*) text.c_str();

	// Ensure we have a shader
	CreateShader( shaderType );

	// Compile
	glShaderSourceARB( mShader, 1, (const GLcharARB**) &sourceText, &sourceLength );
	glCompileShaderARB( mShader );

	return IsCompiled();
}





//=================================================================
//	Shader::GetInfoLog
//---------------------------------------
String Shader::GetInfoLog() const
{
	String theResult = "";
	GLint maxLogLength = 0;

	glGetShaderiv( mShader, GL_INFO_LOG_LENGTH , &maxLogLength );
	if( maxLogLength )
	{
		GLchar* logString = new GLchar[maxLogLength];

		glGetInfoLogARB( mShader, maxLogLength, 0, logString );
		theResult = logString;

		delete[] logString;
	}

	return theResult;
}





//=================================================================
//	Shader::IsSupported
//---------------------------------------
bool Shader::IsSupported( ShaderType shaderType )
{
	bool theResult;

	switch( shaderType )
	{
		case ST_VERTEX: 
			theResult =		GLEW_ARB_vertex_program != 0;
			break;

		case ST_FRAGMENT: 
			theResult =		GLEW_ARB_fragment_program != 0;
			break;

		default:
			throw InvalidArgumentException();
	}

	return theResult;
}


VROOM_END
