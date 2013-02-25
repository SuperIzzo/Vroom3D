#ifndef __VROOM_SHADER_H__
#define __VROOM_SHADER_H__



//=================================================================
//	Inlude
//---------------------------------------
#include <Platform.h>


VROOM_BEGIN


//=================================================================
//	Class Shader
//---------------------------------------
class Shader
{
public:
	//-------------------------------------------------------------
	// Enum ShaderType
	//-----------------------------------
	enum ShaderType
	{
		ST_VERTEX = 0,
		ST_FRAGMENT,
		ST_SIZE
	};


public:
							Shader();
							~Shader();

	void					CompileString( ShaderType shaderType, String source );
	void					Destroy();

	String					GetInfoLog() const;
	bool					IsValid() const;

private:
	void					CreateShader(ShaderType st);

private:
	UInt32					mShader;
};


VROOM_END


#endif