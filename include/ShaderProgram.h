/*ZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZ*\
Z|                                                                           |Z
Z|  Copyright (c) 2013   Hristoz S. Stefanov                                 |Z
Z|                                                                           |Z
Z|  Permission is hereby granted, free of charge, to any person              |Z
Z|  obtaining a copy of this software and associated documentation files     |Z
Z|  (the "Software"), to deal in the Software without restriction,           |Z
Z|  including without limitation the rights to use, copy, modify, merge,     |Z
Z|  publish, distribute, sublicense, and/or sell copies of the Software,     |Z
Z|  and to permit persons to whom the Software is furnished to do so,        |Z
Z|  subject to the following conditions:                                     |Z
Z|                                                                           |Z
Z|  The above copyright notice and this permission notice shall be included  |Z
Z|  in all copies or substantial portions of the Software.                   |Z
Z|                                                                           |Z
Z|  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS  |Z
Z|  OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF               |Z
Z|  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.   |Z
Z|  IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY     |Z
Z|  CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,     |Z
Z|  TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE        |Z
Z|  SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                   |Z
Z|                                                                           |Z
\*ZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZ*/
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