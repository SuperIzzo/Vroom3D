#ifndef __VROOM_SHADERUNIFORM_H__
#define __VROOM_SHADERUNIFORM_H__



//=================================================================
//	Inlude
//---------------------------------------
#include <Platform.h>


VROOM_BEGIN


//=================================================================
//	Forward Declaratrions
//---------------------------------------
class ShaderProgram;





//=================================================================
//	Class ShaderUniform
//---------------------------------------
class ShaderUniform
{
public:
	void					SetInt( SInt32 value );
	bool					IsValid();

private:
							ShaderUniform( SInt32 location );

private:
	friend class ShaderProgram;

	SInt32					mLocation;
};


VROOM_END


#endif