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
	enum ShaderType
	{
		ST_VERTEX = 0,
		ST_FRAGMENT,

		ST_SIZE
	};

public:
	bool	CompileString( ShaderType st, String src );

	bool	IsValid() const;

private:
	bool	CreateShader(ShaderType st);

private:
	UInt32 mShader;
};


VROOM_END


#endif