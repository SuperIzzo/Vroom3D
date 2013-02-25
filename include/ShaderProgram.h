#ifndef __VROOM_SHADERPROGRAM_H__
#define __VROOM_SHADERPROGRAM_H__



//=================================================================
//	Inlude
//---------------------------------------
#include <Platform.h>
#include <SharedPointer.h>
#include <Shader.h>


VROOM_BEGIN


//=================================================================
//	Class ShaderProram
//---------------------------------------
class ShaderProram
{
public:
							ShaderProram();
							~ShaderProram();

	void					AttachShader( ShaderPtr shader );
	void					Link();

private:
	UInt32					mShaderProgram;
};





//=================================================================
//	Type ShaderProgramPtr
//---------------------------------------
typedef SharedPointer<ShaderProgram>::Type	ShaderProgramPtr;


VROOM_END


#endif