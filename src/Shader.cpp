//=================================================================
//	Inlude
//---------------------------------------
#include "Shader.h"

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
		// One time initialization
		init = true;

		ShaderType[Shader::ST_VERTEX]	= GL_VERTEX_SHADER;
		ShaderType[Shader::ST_FRAGMENT] = GL_FRAGMENT_SHADER;
	}

	return ShaderType[st];
}





//=================================================================
//	Shader::CreateShader
//---------------------------------------
bool Shader::CreateShader(ShaderType st)
{
	GLenum glShaderType = GLShaderTypes(st);

	mShader = glCreateShader( glShaderType );

	return IsValid();
};





//=================================================================
//	Shader::IsValid
//---------------------------------------
bool Shader::IsValid() const
{
	return( mShader>0 );
}


VROOM_END
