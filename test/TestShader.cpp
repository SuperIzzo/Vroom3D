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
#include <Shader.h>
#include "GraphicsFixture.h"

#include <UnitTest++.h>
#include <MoreUnitTest++.h>
#include <iostream>


using namespace Vroom;


const String WORKING_VertexShader =  
"	void main() {														\n"
"		gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;			\n"
"   }																	\n";

const String WORKING_FragmentShader =  
"	void main() {														\n"
"		gl_FragColor = vec4 (0.0, 1.0, 0.0, 1.0);						\n"
"   }																	\n";


const String BROKEN_VertexShader =  
"	void main() 	&*%^&												\n"
"		gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;			\n"
"   }																	\n";

const String BROKEN_FragmentShader =  
"	void main() 	&*%^&												\n"
"		gl_FragColor = vec4 (0.0, 1.0, 0.0, 1.0);						\n"
"   }																	\n";




SUITE( Shader )
{
	TEST_FIXTURE( GraphicsFixture, TEST_shader_should_initialize_to_invalid )
	{
		Shader theShader;

		CHECK_NOT( theShader.IsCompiled() );
	}


	TEST_FIXTURE( GraphicsFixture, TEST_compiling_shader_code_validates_the_shader )
	{
		// VERTEX SHADER
		if( Shader::IsSupported(Shader::ST_VERTEX) )
		{			
			Shader theShader;
			bool compiles = false;

			compiles = theShader.CompileString( Shader::ST_VERTEX, WORKING_VertexShader );

			CHECK( compiles );
			CHECK( theShader.IsCompiled() );
		}
		else
		{			
			std::cout << "Vertex shaders not supported. Skipping in \"" << m_details.testName << "\"" << std::endl;
		}

		// FRAGMENT SHADER
		if( Shader::IsSupported(Shader::ST_FRAGMENT) )
		{			
			Shader theShader;
			bool compiles = false;

			compiles = theShader.CompileString( Shader::ST_FRAGMENT, WORKING_FragmentShader );

			CHECK( compiles );
			CHECK( theShader.IsCompiled() );
		}
		else
		{			
			std::cout << "Fragment shaders not supported. Skipping in \"" << m_details.testName << "\"" << std::endl;
		}
	}


	TEST_FIXTURE( GraphicsFixture, TEST_compiling_broken_vertex_shader_code_fails_to_validates_the_shader )
	{
		// VERTEX SHADER
		if( Shader::IsSupported(Shader::ST_VERTEX) )
		{
			Shader theShader;
			bool compiles = false;

			compiles = theShader.CompileString( Shader::ST_VERTEX, BROKEN_VertexShader );

			CHECK_NOT( compiles );
			CHECK_NOT( theShader.IsCompiled() );
		}
		else
		{			
			std::cout << "Vertex shaders not supported. Skipping in \"" << m_details.testName << "\"" << std::endl;
		}

		// FRAGMENT SHADER
		if( Shader::IsSupported(Shader::ST_FRAGMENT) )
		{
			Shader theShader;
			bool compiles = false;

			compiles = theShader.CompileString( Shader::ST_FRAGMENT, BROKEN_FragmentShader );

			CHECK_NOT( compiles );
			CHECK_NOT( theShader.IsCompiled() );
		}
		else
		{			
			std::cout << "Fragment shaders not supported. Skipping in \"" << m_details.testName << "\"" << std::endl;
		}
	}


	TEST_FIXTURE( GraphicsFixture, TEST_destroying_a_valid_shader_shout_invalidate_it )
	{
		// VERTEX SHADER
		if( Shader::IsSupported(Shader::ST_VERTEX) )
		{
			Shader theShader;
			bool compiles = false;

			compiles = theShader.CompileString( Shader::ST_VERTEX, WORKING_VertexShader );
			theShader.Destroy();

			CHECK( compiles );
			CHECK_NOT( theShader.IsCompiled() );
		}
		else
		{			
			std::cout << "Vertex shaders not supported. Skipping in \"" << m_details.testName << "\"" << std::endl;
		}

		// FRAGMENT SHADER
		if( Shader::IsSupported(Shader::ST_FRAGMENT) )
		{
			Shader theShader;
			bool compiles = false;

			compiles = theShader.CompileString( Shader::ST_FRAGMENT, WORKING_FragmentShader );
			theShader.Destroy();

			CHECK( compiles );
			CHECK_NOT( theShader.IsCompiled() );
		}
		else
		{			
			std::cout << "Vertex shaders not supported. Skipping in \"" << m_details.testName << "\"" << std::endl;
		}
	}
}