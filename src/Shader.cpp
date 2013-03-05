//=================================================================
//	Inlude
//---------------------------------------
#include "Shader.h"
#include "GraphicsHardwareException.h"

#include <Windows.h>
#include <gl/glew.h>
#include <gl/GL.h>
#include <gl/GLU.h>


VROOM_BEGIN


//=================================================================
//	GLShaderTypes : Converts ShaderType enum to OpenGL constants
//---------------------------------------
static GLenum GLShaderTypes( Shader::ShaderType st )
{
	static bool		init = false;
	static GLenum	ShaderType[Shader::ST_SIZE];

	if( !init )
	{
		init = true;

		ShaderType[Shader::ST_VERTEX]	= GL_VERTEX_SHADER;
		ShaderType[Shader::ST_FRAGMENT] = GL_FRAGMENT_SHADER;
	}

	return ShaderType[st];
}





//=================================================================
//	Shader::Shader
//---------------------------------------
Shader::Shader() :
	mShader(0)
{
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
	GLenum	glShaderType = GLShaderTypes( shaderType );

	Destroy();
	mShader	= glCreateShader( glShaderType );

	if( !IsValid() )
	{
		throw GraphicsHardwareException( "Unable to create shader." );
	}
};





//=================================================================
//	Shader::Destroy
//---------------------------------------
void Shader::Destroy()
{
	glDeleteShader( mShader );
	mShader = 0;
}





//=================================================================
//	Shader::CompileString
//---------------------------------------
bool Shader::CompileString(ShaderType shaderType, String text)
{
	GLint compiled			= false;
	GLint sourceLength		= text.length() + 1;
	GLcharARB *sourceText	= (GLcharARB*) text.c_str();

	CreateShader( shaderType );

	glShaderSourceARB( mShader, 1, (const GLcharARB**) &sourceText, &sourceLength );
	glCompileShaderARB( mShader );

	glGetObjectParameterivARB( mShader, GL_COMPILE_STATUS, &compiled );

	return compiled;
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
//	Shader::IsValid
//---------------------------------------
bool Shader::IsValid() const
{
	return( mShader>0 );
}


VROOM_END
