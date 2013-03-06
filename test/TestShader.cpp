#include <Shader.h>
#include "GraphicsFixture.h"

#include <UnitTest++.h>
#include <MoreUnitTest++.h>
#include <iostream>


using namespace Vroom;


const String simpleVertexShader =  
"	void main() {														\n"
"		gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;			\n"
"   }																	\n";


SUITE( Shader )
{
	TEST_FIXTURE( GraphicsFixture, TEST_shader_should_initialize_to_invalid )
	{
		Shader theShader;

		CHECK_NOT( theShader.IsValid() );
	}

	TEST_FIXTURE( GraphicsFixture, TEST_compiling_vertex_shader_code_validates_the_shader )
	{
		if( Shader::IsSupported(Shader::ST_VERTEX) )
		{
			Shader theShader;

			theShader.CompileString( Shader::ST_VERTEX, simpleVertexShader );

			CHECK( theShader.IsValid() );
		}
		else
		{			
			std::cout << "Vertex shaders not supported. Skipping test \"" << m_details.testName << "\"" << std::endl;
				// TODO: cout is not the right way to do it, but it is the easiest
		}
	}
}