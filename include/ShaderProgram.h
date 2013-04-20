#ifndef __VROOM_SHADERPROGRAM_H__
#define __VROOM_SHADERPROGRAM_H__



//=================================================================
//	Inlude
//---------------------------------------
#include <Shader.h>
#include <ShaderUniform.h>
#include <list>


VROOM_BEGIN


//=================================================================
//	Class ShaderProgram
//---------------------------------------
class ShaderProgram
{
public:
							ShaderProgram();
							~ShaderProgram();

	// Shader program
	void					Link();
	bool					IsLinked() const;
	void					Use();
	void					Destroy();

	// Shaders
	bool					IsAttached( ShaderPtr shader );
	void					AttachShader( ShaderPtr shader );
	void					DetachShader( ShaderPtr shader );

	// Uniform variables
	ShaderUniform			GetUniform( String name );

private:
	typedef std::list<ShaderPtr> ShaderList;

	void					CreateProgram();
	ShaderList::iterator	FindShader( ShaderPtr shader );

private:
	ShaderList				mShaders;
	UInt32					mProgram;
};





//=================================================================
//	Type ShaderProgramPtr
//---------------------------------------
typedef SharedPointer<ShaderProgram>::Type	ShaderProgramPtr;


VROOM_END


#endif