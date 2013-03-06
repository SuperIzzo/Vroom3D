#ifndef __VROOM_SHADERPROGRAM_H__
#define __VROOM_SHADERPROGRAM_H__



//=================================================================
//	Inlude
//---------------------------------------
#include <Platform.h>
#include <SharedPointer.h>
#include <Shader.h>
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
	void					Destroy();
	bool					IsValid() const;

	// Shaders
	bool					IsAttached( ShaderPtr shader );
	void					AttachShader( ShaderPtr shader );
	void					DetachShader( ShaderPtr shader );

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