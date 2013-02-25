#ifndef __VROOM_SHADER_H__
#define __VROOM_SHADER_H__



//=================================================================
//	Inlude
//---------------------------------------
#include <Platform.h>
#include <SharedPointer.h>


VROOM_BEGIN


//=================================================================
//	Forward Declarations
//---------------------------------------
class ShaderProgram;





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

	friend class ShaderProgram;

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





//=================================================================
//	Type ShaderPtr
//---------------------------------------
typedef SharedPointer<Shader>::Type			ShaderPtr;


VROOM_END


#endif