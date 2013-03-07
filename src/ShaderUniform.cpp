#include "ShaderUniform.h"
#include "GraphicsCommon.h"


VROOM_BEGIN


//=================================================================
//	ShaderProgram::Destroy
//---------------------------------------
ShaderUniform::ShaderUniform( SInt32 location )
{
	mLocation = location;
}





//=================================================================
//	ShaderProgram::IsValid
//---------------------------------------
bool ShaderUniform::IsValid()
{
	return( mLocation!=-1 );
}





//=================================================================
//	ShaderProgram::SetInt
//---------------------------------------
void ShaderUniform::SetInt( SInt32 value )
{
	if( IsValid() )
	{
		glUniform1i(mLocation, value);
	}
}


VROOM_END