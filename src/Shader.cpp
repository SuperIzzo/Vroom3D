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
